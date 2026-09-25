#include "Appearance/BytesAppearanceComponent.h"
#include "Appearance/BytesAppearanceSubsystem.h"
#include "Game/BytesPlayerState.h"
#include "ProjectBytes.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/Canvas.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Misc/PackageName.h"

namespace
{
	bool SameLayers(const TArray<FBytesTattooLayer>& A, const TArray<FBytesTattooLayer>& B)
	{
		if (A.Num() != B.Num())
		{
			return false;
		}
		for (int32 Index = 0; Index < A.Num(); ++Index)
		{
			const FBytesTattooLayer& L = A[Index];
			const FBytesTattooLayer& R = B[Index];
			if (L.Decal != R.Decal || L.Region != R.Region || L.X != R.X || L.Y != R.Y || L.Scale != R.Scale
				|| L.Rotation != R.Rotation || L.Color != R.Color || L.Opacity != R.Opacity || L.Mirror != R.Mirror)
			{
				return false;
			}
		}
		return true;
	}

	const FBytesAppearanceCatalog* GetCatalogFor(const UObject* Context)
	{
		const UBytesAppearanceSubsystem* Appearance = UBytesAppearanceSubsystem::Get(Context);
		return Appearance && Appearance->IsCatalogLoaded() ? &Appearance->GetCatalog() : nullptr;
	}

	template <typename TObject>
	TObject* ResolveSoft(const FString& Path)
	{
		return Path.IsEmpty() ? nullptr : Cast<TObject>(FSoftObjectPath(Path).ResolveObject());
	}
}

UBytesAppearanceComponent::UBytesAppearanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickInterval = 0.2f;
}

bool UBytesAppearanceComponent::IsVisualNetMode() const
{
	const AActor* Owner = GetOwner();
	return Owner && Owner->GetNetMode() != NM_DedicatedServer;
}

USkeletalMeshComponent* UBytesAppearanceComponent::GetBodyMesh() const
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}
	TArray<USkeletalMeshComponent*> Meshes;
	Owner->GetComponents<USkeletalMeshComponent>(Meshes);
	for (USkeletalMeshComponent* Mesh : Meshes)
	{
		const bool bIsPart = PartComponents.FindKey(Mesh) != nullptr;
		if (!bIsPart && (BodyMeshComponentName.IsNone() || Mesh->GetFName() == BodyMeshComponentName))
		{
			return Mesh;
		}
	}
	return nullptr;
}

// ---- Player state binding -----------------------------------------------------------------------

void UBytesAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(bFollowPlayerState);
}

void UBytesAppearanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pawns get their player state some time after BeginPlay on clients; wait for it, then go event-driven.
	const APawn* Pawn = Cast<APawn>(GetOwner());
	ABytesPlayerState* PlayerState = Pawn ? Pawn->GetPlayerState<ABytesPlayerState>() : nullptr;
	if (!PlayerState || PlayerState == BoundPlayerState.Get())
	{
		return;
	}
	if (ABytesPlayerState* Old = BoundPlayerState.Get())
	{
		Old->OnIdentityChanged.RemoveDynamic(this, &ThisClass::HandleIdentityChanged);
	}
	BoundPlayerState = PlayerState;
	PlayerState->OnIdentityChanged.AddDynamic(this, &ThisClass::HandleIdentityChanged);
	HandleIdentityChanged(PlayerState);
}

void UBytesAppearanceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ABytesPlayerState* PlayerState = BoundPlayerState.Get())
	{
		PlayerState->OnIdentityChanged.RemoveDynamic(this, &ThisClass::HandleIdentityChanged);
	}
	if (LoadHandle.IsValid())
	{
		LoadHandle->CancelHandle();
		LoadHandle.Reset();
	}
	Super::EndPlay(EndPlayReason);
}

void UBytesAppearanceComponent::HandleIdentityChanged(ABytesPlayerState* PlayerState)
{
	if (PlayerState)
	{
		ApplyAppearanceJson(PlayerState->GetIdentity().Appearance);
	}
}

// ---- Applying -----------------------------------------------------------------------------------

void UBytesAppearanceComponent::ApplyAppearanceJson(const FString& Json)
{
	const UBytesAppearanceSubsystem* Appearance = UBytesAppearanceSubsystem::Get(this);
	if (Appearance)
	{
		ApplyAppearance(Appearance->ParseOrDefault(Json));
	}
}

void UBytesAppearanceComponent::ApplyAppearance(const FBytesAppearance& Appearance)
{
	Current = Appearance;
	if (!IsVisualNetMode())
	{
		return;
	}

	const TArray<FSoftObjectPath> Assets = GatherAssets(Current);
	const int32 Serial = ++LoadSerial;
	const bool bAllLoaded = !Assets.ContainsByPredicate([](const FSoftObjectPath& Path) { return Path.ResolveObject() == nullptr; });
	if (bAllLoaded)
	{
		// Common case while editing (slider drags, colours): everything is resident, apply this frame.
		OnAssetsLoaded(Serial);
		return;
	}

	if (LoadHandle.IsValid())
	{
		LoadHandle->CancelHandle();
	}
	LoadHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(Assets,
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnAssetsLoaded, Serial));
	if (!LoadHandle.IsValid())
	{
		OnAssetsLoaded(Serial); // nothing loadable (paths don't exist yet): apply what we can
	}
}

TArray<FSoftObjectPath> UBytesAppearanceComponent::GatherAssets(const FBytesAppearance& Appearance) const
{
	TArray<FSoftObjectPath> Paths;
	const FBytesAppearanceCatalog* Catalog = GetCatalogFor(this);
	if (!Catalog)
	{
		return Paths;
	}
	auto AddPath = [this, &Paths](const FString& Path)
	{
		if (Path.IsEmpty() || MissingPackages.Contains(Path))
		{
			return;
		}
		const FSoftObjectPath SoftPath(Path);
		if (!SoftPath.ResolveObject() && !FPackageName::DoesPackageExist(SoftPath.GetLongPackageName()))
		{
			UE_LOG(LogBytes, Warning, TEXT("Appearance: %s doesn't exist yet, skipping"), *Path);
			MissingPackages.Add(Path);
			return;
		}
		Paths.AddUnique(SoftPath);
	};
	if (const FBytesBodyDef* Body = Catalog->FindBody(Appearance.Body))
	{
		AddPath(Body->Mesh);
		AddPath(Body->AnimClass);
	}
	for (const TPair<FString, FBytesAppearancePart>& Part : Appearance.Parts)
	{
		if (const FBytesPartDef* Def = Catalog->FindPart(Part.Value.Id))
		{
			if (const FString* Mesh = Def->Mesh.Find(Appearance.Body))
			{
				AddPath(*Mesh);
			}
		}
	}
	for (const FBytesTattooLayer& Layer : Appearance.Tattoos)
	{
		if (const FBytesDecalDef* Def = Catalog->FindDecal(Layer.Decal))
		{
			AddPath(Def->Texture);
		}
	}
	return Paths;
}

void UBytesAppearanceComponent::OnAssetsLoaded(int32 Serial)
{
	if (Serial != LoadSerial)
	{
		return; // superseded by a newer ApplyAppearance
	}
	ApplyLoaded();
}

void UBytesAppearanceComponent::ApplyLoaded()
{
	USkeletalMeshComponent* Body = GetBodyMesh();
	if (!Body || !GetCatalogFor(this))
	{
		return;
	}
	ApplyBody(Body);
	ApplyParts(Body);
	ApplyMorphs(Body);
	ApplyColors();
	RedrawTattoos();
	OnAppearanceApplied.Broadcast();
}

void UBytesAppearanceComponent::ApplyBody(USkeletalMeshComponent* Body)
{
	const FBytesAppearanceCatalog& Catalog = *GetCatalogFor(this);
	const FBytesBodyDef* BodyDef = Catalog.FindBody(Current.Body);
	if (!BodyDef)
	{
		return;
	}
	if (!bBaseScaleCaptured)
	{
		BaseMeshScale = Body->GetRelativeScale3D();
		bBaseScaleCaptured = true;
	}

	const bool bBodyChanged = AppliedBody != Current.Body;
	if (bBodyChanged || BodyMaterials.Num() == 0)
	{
		if (USkeletalMesh* Mesh = ResolveSoft<USkeletalMesh>(BodyDef->Mesh))
		{
			if (Body->GetSkeletalMeshAsset() != Mesh)
			{
				Body->EmptyOverrideMaterials();
				Body->SetSkeletalMeshAsset(Mesh);
			}
		}
		else if (!BodyDef->Mesh.IsEmpty())
		{
			UE_LOG(LogBytes, Warning, TEXT("Appearance: body mesh %s not found"), *BodyDef->Mesh);
		}
		if (!BodyDef->AnimClass.IsEmpty())
		{
			if (UClass* AnimClass = Cast<UClass>(FSoftObjectPath(BodyDef->AnimClass).ResolveObject()))
			{
				Body->SetAnimInstanceClass(AnimClass);
			}
		}
		BodyMaterials.Reset();
		CollectMaterials(Body, BodyDef->SkinMaterialSlots, BodyMaterials);
		AppliedBody = Current.Body;
		bTattoosDrawn = false; // new materials need the overlay bound again
	}
}

void UBytesAppearanceComponent::ApplyParts(USkeletalMeshComponent* Body)
{
	const FBytesAppearanceCatalog& Catalog = *GetCatalogFor(this);
	AActor* Owner = GetOwner();

	// Remove slots that are now empty.
	TArray<FString> Stale;
	for (const TPair<FString, TObjectPtr<USkeletalMeshComponent>>& Pair : PartComponents)
	{
		if (!Current.Parts.Contains(Pair.Key))
		{
			Stale.Add(Pair.Key);
		}
	}
	for (const FString& Slot : Stale)
	{
		RemovePart(Slot);
	}

	for (const TPair<FString, FBytesAppearancePart>& Pair : Current.Parts)
	{
		const FBytesPartDef* PartDef = Catalog.FindPart(Pair.Value.Id);
		const FString* MeshPath = PartDef ? PartDef->Mesh.Find(Current.Body) : nullptr;
		USkeletalMesh* Mesh = MeshPath ? ResolveSoft<USkeletalMesh>(*MeshPath) : nullptr;
		if (!Mesh)
		{
			RemovePart(Pair.Key); // don't leave the previous item in this slot on screen
			continue;
		}

		TObjectPtr<USkeletalMeshComponent>& Component = PartComponents.FindOrAdd(Pair.Key);
		if (!Component)
		{
			const FName Name = MakeUniqueObjectName(Owner, USkeletalMeshComponent::StaticClass(), *FString::Printf(TEXT("Part_%s"), *Pair.Key));
			Component = NewObject<USkeletalMeshComponent>(Owner, Name);
			Component->SetupAttachment(Body);
			Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Component->CreationMethod = EComponentCreationMethod::Instance;
			Component->RegisterComponent();
			Component->SetLeaderPoseComponent(Body);
			Owner->AddInstanceComponent(Component);
		}
		if (Component->GetSkeletalMeshAsset() != Mesh)
		{
			Component->EmptyOverrideMaterials();
			Component->SetSkeletalMeshAsset(Mesh);
			FBytesMaterialList& Materials = PartMaterials.FindOrAdd(Pair.Key);
			Materials.Materials.Reset();
			CollectMaterials(Component, TArray<FString>(), Materials.Materials);
		}
	}
}

void UBytesAppearanceComponent::RemovePart(const FString& Slot)
{
	if (USkeletalMeshComponent* Component = PartComponents.FindRef(Slot))
	{
		Component->DestroyComponent();
	}
	PartComponents.Remove(Slot);
	PartMaterials.Remove(Slot);
}

void UBytesAppearanceComponent::ApplyMorphs(USkeletalMeshComponent* Body)
{
	const FBytesAppearanceCatalog& Catalog = *GetCatalogFor(this);
	TArray<USkeletalMeshComponent*> Targets = { Body };
	for (const TPair<FString, TObjectPtr<USkeletalMeshComponent>>& Pair : PartComponents)
	{
		if (Pair.Value)
		{
			Targets.Add(Pair.Value);
		}
	}

	float MeshScale = 1.f;
	for (const FBytesMorphDef& Def : Catalog.Morphs)
	{
		const float Value = Catalog.GetMorphValue(Current, Def.Id);
		// Normalize each side of the slider to a 0..1 morph weight.
		const float PosWeight = Value > 0.f && Def.Max > 0.f ? Value / Def.Max : 0.f;
		const float NegWeight = Value < 0.f && Def.Min < 0.f ? Value / Def.Min : 0.f;
		for (USkeletalMeshComponent* Target : Targets)
		{
			if (!Def.PosTarget.IsEmpty())
			{
				Target->SetMorphTarget(FName(*Def.PosTarget), PosWeight);
			}
			if (!Def.NegTarget.IsEmpty())
			{
				Target->SetMorphTarget(FName(*Def.NegTarget), NegWeight);
			}
		}
		if (Def.MeshScaleMin > 0.f && Def.MeshScaleMax > 0.f && Def.Max > Def.Min)
		{
			MeshScale *= FMath::Lerp(Def.MeshScaleMin, Def.MeshScaleMax, (Value - Def.Min) / (Def.Max - Def.Min));
		}
	}
	Body->SetRelativeScale3D(BaseMeshScale * MeshScale);
}

void UBytesAppearanceComponent::ApplyColors()
{
	const FBytesAppearanceCatalog& Catalog = *GetCatalogFor(this);
	for (const FBytesColorDef& Def : Catalog.Colors)
	{
		const FName Parameter(*Def.Parameter);
		const FLinearColor Color = Catalog.GetColorValue(Current, Def.Id);
		for (const FString& Target : Def.ApplyTo)
		{
			const TArray<TObjectPtr<UMaterialInstanceDynamic>>* Materials = Target == TEXT("body") ? &BodyMaterials
				: (PartMaterials.Contains(Target) ? &PartMaterials[Target].Materials : nullptr);
			if (!Materials)
			{
				continue;
			}
			for (UMaterialInstanceDynamic* Material : *Materials)
			{
				Material->SetVectorParameterValue(Parameter, Color);
			}
		}
	}

	for (const TPair<FString, FBytesAppearancePart>& Pair : Current.Parts)
	{
		const FBytesSlotDef* Slot = Catalog.FindSlot(Pair.Key);
		const FBytesMaterialList* Materials = PartMaterials.Find(Pair.Key);
		if (!Slot || !Materials)
		{
			continue;
		}
		for (int32 Channel = 0; Channel < FMath::Min(Slot->ColorParameters.Num(), Pair.Value.Colors.Num()); ++Channel)
		{
			const FName Parameter(*Slot->ColorParameters[Channel]);
			const FLinearColor Color = BytesColor::FromHex(Pair.Value.Colors[Channel]);
			for (UMaterialInstanceDynamic* Material : Materials->Materials)
			{
				Material->SetVectorParameterValue(Parameter, Color);
			}
		}
	}
}

void UBytesAppearanceComponent::RedrawTattoos()
{
	const FBytesAppearanceCatalog& Catalog = *GetCatalogFor(this);
	if (bTattoosDrawn && SameLayers(DrawnTattoos, Current.Tattoos))
	{
		return;
	}

	const int32 Size = FMath::Clamp(Catalog.TattooAtlasSize, 64, 4096);
	if (!TattooTarget || TattooTarget->SizeX != Size)
	{
		TattooTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, Size, Size, RTF_RGBA8, FLinearColor::Black);
	}
	if (!TattooTarget)
	{
		return;
	}
	// Canvas translucent drawing writes "inverse opacity" into alpha (dstA *= 1 - srcA). So clear to alpha 1 and
	// the skin material uses (1 - TattooOverlay.A) as the ink mask; RGB is premultiplied ink colour.
	UKismetRenderingLibrary::ClearRenderTarget2D(this, TattooTarget, FLinearColor(0.f, 0.f, 0.f, 1.f));

	if (Current.Tattoos.Num() > 0)
	{
		UCanvas* Canvas = nullptr;
		FVector2D CanvasSize;
		FDrawToRenderTargetContext Context;
		UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, TattooTarget, Canvas, CanvasSize, Context);
		if (Canvas)
		{
			for (const FBytesTattooLayer& Layer : Current.Tattoos)
			{
				const FBytesDecalDef* Decal = Catalog.FindDecal(Layer.Decal);
				const FBytesRegionDef* Region = Catalog.FindRegion(Layer.Region);
				UTexture2D* Texture = Decal ? ResolveSoft<UTexture2D>(Decal->Texture) : nullptr;
				if (!Region || !Texture)
				{
					continue;
				}
				// Drawn once and cached, so make sure we're not baking a blurry low mip.
				Texture->SetForceMipLevelsToBeResident(30.f);
				Texture->WaitForStreaming();
				const FBox2D Rect = Region->GetRect();
				const FVector2D RegionMin = Rect.Min * CanvasSize;
				const FVector2D RegionSize = Rect.GetSize() * CanvasSize;
				const float Aspect = Texture->GetSizeX() > 0 ? static_cast<float>(Texture->GetSizeY()) / Texture->GetSizeX() : 1.f;
				const FVector2D DrawSize(RegionSize.X * Layer.Scale, RegionSize.X * Layer.Scale * Aspect);
				const FVector2D Center = RegionMin + FVector2D(Layer.X, Layer.Y) * RegionSize;

				FLinearColor Tint = BytesColor::FromHex(Layer.Color, FLinearColor::Black);
				Tint.A = Layer.Opacity;
				Canvas->K2_DrawTexture(Texture, Center - DrawSize * 0.5f, DrawSize,
					FVector2D(Layer.Mirror ? 1.f : 0.f, 0.f), FVector2D(Layer.Mirror ? -1.f : 1.f, 1.f),
					Tint, BLEND_Translucent, Layer.Rotation, FVector2D(0.5f, 0.5f));
			}
		}
		UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, Context);
	}

	const FName Parameter(*Catalog.TattooTextureParameter);
	for (UMaterialInstanceDynamic* Material : BodyMaterials)
	{
		Material->SetTextureParameterValue(Parameter, TattooTarget);
	}
	DrawnTattoos = Current.Tattoos;
	bTattoosDrawn = true;
}

void UBytesAppearanceComponent::CollectMaterials(USkeletalMeshComponent* Mesh, const TArray<FString>& SlotFilter, TArray<TObjectPtr<UMaterialInstanceDynamic>>& Out) const
{
	const TArray<FName> SlotNames = Mesh->GetMaterialSlotNames();
	for (int32 Index = 0; Index < Mesh->GetNumMaterials(); ++Index)
	{
		if (SlotFilter.Num() > 0 && (!SlotNames.IsValidIndex(Index) || !SlotFilter.Contains(SlotNames[Index].ToString())))
		{
			continue;
		}
		if (UMaterialInstanceDynamic* Material = Mesh->CreateAndSetMaterialInstanceDynamic(Index))
		{
			Out.Add(Material);
		}
	}
}
