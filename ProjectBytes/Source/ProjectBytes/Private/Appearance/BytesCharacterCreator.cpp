#include "Appearance/BytesCharacterCreator.h"
#include "Appearance/BytesAppearanceComponent.h"
#include "Appearance/BytesAppearanceSubsystem.h"
#include "Appearance/BytesCreatorPreviewActor.h"
#include "ProjectBytes.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"

namespace
{
	constexpr int32 MaxUndo = 64;
}

void UBytesCharacterCreator::Initialize(UBytesAppearanceSubsystem* InAppearance)
{
	AppearanceSubsystem = InAppearance;
	Appearance = Catalog().MakeDefault(TEXT("male"));
}

const FBytesAppearanceCatalog& UBytesCharacterCreator::Catalog() const
{
	static const FBytesAppearanceCatalog Empty;
	const UBytesAppearanceSubsystem* Subsystem = AppearanceSubsystem.Get();
	return Subsystem ? Subsystem->GetCatalog() : Empty;
}

// ---- Preview ------------------------------------------------------------------------------------

void UBytesCharacterCreator::SpawnPreview(UWorld* World)
{
	if (!World || World->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}
	// Reuse a mannequin placed in the frontend map, otherwise spawn one at the origin.
	for (TActorIterator<ABytesCreatorPreviewActor> It(World); It; ++It)
	{
		Preview = *It;
		break;
	}
	if (!Preview)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Preview = World->SpawnActor<ABytesCreatorPreviewActor>(FVector::ZeroVector, FRotator::ZeroRotator, Params);
		bSpawnedPreview = Preview != nullptr;
	}
	if (APlayerController* PC = World->GetGameInstance() ? World->GetGameInstance()->GetFirstLocalPlayerController(World) : nullptr)
	{
		PreviousViewTarget = PC->GetViewTarget();
		PC->SetViewTargetWithBlend(Preview, 0.35f);
	}
	Changed();
}

void UBytesCharacterCreator::DestroyPreview()
{
	if (Preview)
	{
		UWorld* World = Preview->GetWorld();
		APlayerController* PC = World && World->GetGameInstance() ? World->GetGameInstance()->GetFirstLocalPlayerController(World) : nullptr;
		if (PC && PC->GetViewTarget() == Preview.Get())
		{
			AActor* Back = PreviousViewTarget.IsValid() && PreviousViewTarget.Get() != Preview.Get() ? PreviousViewTarget.Get() : PC->GetPawn();
			if (Back)
			{
				PC->SetViewTargetWithBlend(Back, 0.35f);
			}
		}
		if (bSpawnedPreview)
		{
			Preview->Destroy();
		}
	}
	Preview = nullptr;
	bSpawnedPreview = false;
}

// ---- Session ------------------------------------------------------------------------------------

void UBytesCharacterCreator::StartNew(const FString& Body, EBytesFaction NewFaction)
{
	EditingCharacterId.Reset();
	Rank = 1;
	Faction = NewFaction;
	Appearance = Catalog().MakeDefault(Body);
	UndoStack.Reset();
	RedoStack.Reset();
	Changed();
}

bool UBytesCharacterCreator::StartEditing(const FString& CharacterIdOrName)
{
	const UBytesAppearanceSubsystem* Subsystem = AppearanceSubsystem.Get();
	const UGameInstance* GameInstance = Subsystem ? Subsystem->GetGameInstance() : nullptr;
	const UBytesAccountSubsystem* Account = GameInstance ? GameInstance->GetSubsystem<UBytesAccountSubsystem>() : nullptr;
	const FBytesCharacter* Character = Account ? Account->FindCharacter(CharacterIdOrName) : nullptr;
	if (!Character)
	{
		return false;
	}
	EditingCharacterId = Character->CharacterId;
	Rank = Character->Rank;
	Faction = Character->Faction;
	Appearance = Subsystem->ParseOrDefault(Character->Appearance);
	UndoStack.Reset();
	RedoStack.Reset();
	Changed();
	return true;
}

void UBytesCharacterCreator::SetFaction(EBytesFaction NewFaction)
{
	if (!IsEditingExisting() && Faction != NewFaction)
	{
		Faction = NewFaction;
		Changed();
	}
}

// ---- Editing ------------------------------------------------------------------------------------

void UBytesCharacterCreator::SetBody(const FString& Body)
{
	if (!Catalog().FindBody(Body) || Body == Appearance.Body)
	{
		return;
	}
	RecordUndo();
	Appearance.Body = Body;
	for (auto It = Appearance.Parts.CreateIterator(); It; ++It)
	{
		const FBytesPartDef* Part = Catalog().FindPart(It->Value.Id);
		if (!Part || (Part->Bodies.Num() > 0 && !Part->Bodies.Contains(Body)))
		{
			It.RemoveCurrent();
		}
	}
	const FBytesAppearance Defaults = Catalog().MakeDefault(Body);
	for (const TPair<FString, FBytesAppearancePart>& Pair : Defaults.Parts)
	{
		if (!Appearance.Parts.Contains(Pair.Key))
		{
			Appearance.Parts.Add(Pair.Key, Pair.Value);
		}
	}
	Changed();
}

void UBytesCharacterCreator::SetMorph(const FString& MorphId, float Value, bool bRecordUndo)
{
	const FBytesMorphDef* Def = Catalog().FindMorph(MorphId);
	if (!Def)
	{
		return;
	}
	if (bRecordUndo)
	{
		RecordUndo();
	}
	Appearance.Morphs.Add(MorphId, FMath::Clamp(Value, Def->Min, Def->Max));
	Changed();
}

float UBytesCharacterCreator::GetMorph(const FString& MorphId) const
{
	return Catalog().GetMorphValue(Appearance, MorphId);
}

void UBytesCharacterCreator::ResetMorphs(const FString& Category)
{
	RecordUndo();
	for (const FBytesMorphDef& Def : Catalog().Morphs)
	{
		if (Category.IsEmpty() || Def.Category == Category)
		{
			Appearance.Morphs.Remove(Def.Id);
		}
	}
	Changed();
}

void UBytesCharacterCreator::SetColor(const FString& ColorId, FLinearColor Color, bool bRecordUndo)
{
	SetColorHex(ColorId, BytesColor::ToHex(Color), bRecordUndo);
}

bool UBytesCharacterCreator::SetColorHex(const FString& ColorId, const FString& Hex, bool bRecordUndo)
{
	if (!Catalog().FindColor(ColorId) || !BytesColor::IsValidHex(Hex))
	{
		return false;
	}
	if (bRecordUndo)
	{
		RecordUndo();
	}
	Appearance.Colors.Add(ColorId, Hex.ToLower());
	Changed();
	return true;
}

FLinearColor UBytesCharacterCreator::GetColor(const FString& ColorId) const
{
	return Catalog().GetColorValue(Appearance, ColorId);
}

bool UBytesCharacterCreator::SetPart(const FString& SlotId, const FString& PartId)
{
	const FBytesSlotDef* Slot = Catalog().FindSlot(SlotId);
	if (!Slot)
	{
		return false;
	}
	if (PartId.IsEmpty())
	{
		RecordUndo();
		Appearance.Parts.Remove(SlotId);
		Changed();
		return true;
	}
	const FBytesPartDef* Part = Catalog().FindPart(PartId);
	if (!Part || Part->Slot != SlotId || (Part->Bodies.Num() > 0 && !Part->Bodies.Contains(Appearance.Body)))
	{
		return false;
	}
	RecordUndo();
	FBytesAppearancePart& Value = Appearance.Parts.FindOrAdd(SlotId);
	Value.Id = PartId; // keep the previous colours: swapping a jacket shouldn't lose your colour scheme
	Value.Colors.SetNum(FMath::Min(Value.Colors.Num(), Slot->ColorChannels));
	Changed();
	return true;
}

void UBytesCharacterCreator::SetPartColor(const FString& SlotId, int32 Channel, FLinearColor Color, bool bRecordUndo)
{
	const FBytesSlotDef* Slot = Catalog().FindSlot(SlotId);
	FBytesAppearancePart* Part = Appearance.Parts.Find(SlotId);
	if (!Slot || !Part || Channel < 0 || Channel >= Slot->ColorChannels)
	{
		return;
	}
	if (bRecordUndo)
	{
		RecordUndo();
	}
	while (Part->Colors.Num() <= Channel)
	{
		Part->Colors.Add(TEXT("#808080"));
	}
	Part->Colors[Channel] = BytesColor::ToHex(Color);
	Changed();
}

int32 UBytesCharacterCreator::AddTattoo(const FString& DecalId, const FString& RegionId)
{
	const FBytesDecalDef* Decal = Catalog().FindDecal(DecalId);
	if (!Decal || !Catalog().FindRegion(RegionId) || Appearance.Tattoos.Num() >= Catalog().MaxTattoos
		|| (Decal->Regions.Num() > 0 && !Decal->Regions.Contains(RegionId)))
	{
		return INDEX_NONE;
	}
	RecordUndo();
	FBytesTattooLayer Layer;
	Layer.Decal = DecalId;
	Layer.Region = RegionId;
	const int32 Index = Appearance.Tattoos.Add(Layer);
	Changed();
	return Index;
}

void UBytesCharacterCreator::UpdateTattoo(int32 Index, const FBytesTattooLayer& Layer, bool bRecordUndo)
{
	if (!Appearance.Tattoos.IsValidIndex(Index))
	{
		return;
	}
	if (bRecordUndo)
	{
		RecordUndo();
	}
	FBytesTattooLayer Clamped = Layer;
	Clamped.X = FMath::Clamp(Clamped.X, 0.f, 1.f);
	Clamped.Y = FMath::Clamp(Clamped.Y, 0.f, 1.f);
	Clamped.Scale = FMath::Clamp(Clamped.Scale, Catalog().TattooMinScale, Catalog().TattooMaxScale);
	Clamped.Rotation = FMath::UnwindDegrees(Clamped.Rotation);
	Clamped.Opacity = FMath::Clamp(Clamped.Opacity, 0.f, 1.f);
	Appearance.Tattoos[Index] = Clamped;
	Changed();
}

void UBytesCharacterCreator::RemoveTattoo(int32 Index)
{
	if (Appearance.Tattoos.IsValidIndex(Index))
	{
		RecordUndo();
		Appearance.Tattoos.RemoveAt(Index);
		Changed();
	}
}

void UBytesCharacterCreator::MoveTattooLayer(int32 Index, int32 NewIndex)
{
	if (!Appearance.Tattoos.IsValidIndex(Index) || Index == NewIndex)
	{
		return;
	}
	RecordUndo();
	const FBytesTattooLayer Layer = Appearance.Tattoos[Index];
	Appearance.Tattoos.RemoveAt(Index);
	Appearance.Tattoos.Insert(Layer, FMath::Clamp(NewIndex, 0, Appearance.Tattoos.Num()));
	Changed();
}

int32 UBytesCharacterCreator::MirrorTattoo(int32 Index)
{
	if (!Appearance.Tattoos.IsValidIndex(Index) || Appearance.Tattoos.Num() >= Catalog().MaxTattoos)
	{
		return INDEX_NONE;
	}
	const FBytesTattooLayer Source = Appearance.Tattoos[Index];
	const FBytesRegionDef* Region = Catalog().FindRegion(Source.Region);
	const FBytesDecalDef* Decal = Catalog().FindDecal(Source.Decal);
	const FString Target = Region && !Region->MirrorRegion.IsEmpty() ? Region->MirrorRegion : Source.Region;
	if (!Decal || (Decal->Regions.Num() > 0 && !Decal->Regions.Contains(Target)))
	{
		return INDEX_NONE;
	}
	RecordUndo();
	FBytesTattooLayer Copy = Source;
	Copy.Region = Target;
	Copy.X = 1.f - Source.X;
	Copy.Rotation = FMath::UnwindDegrees(-Source.Rotation);
	Copy.Mirror = !Source.Mirror;
	const int32 NewIndex = Appearance.Tattoos.Add(Copy);
	Changed();
	return NewIndex;
}

void UBytesCharacterCreator::Randomize(int32 Seed)
{
	if (const UBytesAppearanceSubsystem* Subsystem = AppearanceSubsystem.Get())
	{
		RecordUndo();
		const TArray<FBytesTattooLayer> KeepTattoos = Appearance.Tattoos;
		Appearance = Subsystem->Randomize(Appearance.Body, Rank, Faction, Seed);
		Appearance.Tattoos = KeepTattoos; // random ink is rarely what anyone wants
		Changed();
	}
}

// ---- Undo ---------------------------------------------------------------------------------------

void UBytesCharacterCreator::PushUndo(TArray<FString>& Stack)
{
	Stack.Add(Appearance.ToJson());
	if (Stack.Num() > MaxUndo)
	{
		Stack.RemoveAt(0);
	}
}

void UBytesCharacterCreator::RecordUndo()
{
	PushUndo(UndoStack);
	RedoStack.Reset();
}

bool UBytesCharacterCreator::Undo()
{
	if (UndoStack.Num() == 0)
	{
		return false;
	}
	PushUndo(RedoStack);
	FBytesAppearance::FromJson(UndoStack.Pop(), Appearance);
	Changed();
	return true;
}

bool UBytesCharacterCreator::Redo()
{
	if (RedoStack.Num() == 0)
	{
		return false;
	}
	PushUndo(UndoStack);
	FBytesAppearance::FromJson(RedoStack.Pop(), Appearance);
	Changed();
	return true;
}

// ---- Queries ------------------------------------------------------------------------------------

TArray<FString> UBytesCharacterCreator::Validate() const
{
	FBytesAppearance Copy = Appearance;
	return Catalog().Validate(Copy, Rank, Faction);
}

TArray<FBytesCreatorOption> UBytesCharacterCreator::GetPartOptions(const FString& SlotId) const
{
	TArray<FBytesCreatorOption> Options;
	for (const FBytesPartDef& Part : Catalog().Parts)
	{
		if (Part.Slot != SlotId || (Part.Bodies.Num() > 0 && !Part.Bodies.Contains(Appearance.Body)))
		{
			continue;
		}
		FBytesCreatorOption& Option = Options.AddDefaulted_GetRef();
		Option.Id = Part.Id;
		Option.DisplayName = Part.DisplayName;
		const TArray<FString> Locks = FBytesAppearanceCatalog::UnlockErrors(Part.DisplayName, Part.MinRank, Part.Factions, Rank, Faction);
		Option.bLocked = Locks.Num() > 0;
		Option.LockReason = FString::Join(Locks, TEXT("; "));
	}
	return Options;
}

TArray<FBytesCreatorOption> UBytesCharacterCreator::GetDecalOptions(const FString& RegionId) const
{
	TArray<FBytesCreatorOption> Options;
	for (const FBytesDecalDef& Decal : Catalog().Decals)
	{
		if (!RegionId.IsEmpty() && Decal.Regions.Num() > 0 && !Decal.Regions.Contains(RegionId))
		{
			continue;
		}
		FBytesCreatorOption& Option = Options.AddDefaulted_GetRef();
		Option.Id = Decal.Id;
		Option.DisplayName = Decal.DisplayName;
		const TArray<FString> Locks = FBytesAppearanceCatalog::UnlockErrors(Decal.DisplayName, Decal.MinRank, Decal.Factions, Rank, Faction);
		Option.bLocked = Locks.Num() > 0;
		Option.LockReason = FString::Join(Locks, TEXT("; "));
	}
	return Options;
}

// ---- Saving -------------------------------------------------------------------------------------

void UBytesCharacterCreator::Save(const FString& Name, FBytesDone Done)
{
	const UBytesAppearanceSubsystem* Subsystem = AppearanceSubsystem.Get();
	UGameInstance* GameInstance = Subsystem ? Subsystem->GetGameInstance() : nullptr;
	UBytesAccountSubsystem* Account = GameInstance ? GameInstance->GetSubsystem<UBytesAccountSubsystem>() : nullptr;
	if (!Account || !Account->IsLoggedIn())
	{
		if (Done)
		{
			Done(false, TEXT("Log in first"));
		}
		return;
	}

	FBytesAppearance Normalized = Appearance;
	const TArray<FString> Errors = Catalog().Validate(Normalized, Rank, Faction);
	if (Errors.Num() > 0)
	{
		if (Done)
		{
			Done(false, FString::Join(Errors, TEXT("; ")));
		}
		return;
	}

	if (IsEditingExisting())
	{
		Account->UpdateAppearance(EditingCharacterId, Normalized.ToJson(), Done);
	}
	else
	{
		Account->CreateCharacter(Name, Faction, Normalized.ToJson(), Done);
	}
}

void UBytesCharacterCreator::K2_Save(const FString& Name, FBytesOnResult OnComplete)
{
	Save(Name, [OnComplete](bool bSuccess, const FString& Error) { OnComplete.ExecuteIfBound(bSuccess, Error); });
}

void UBytesCharacterCreator::Changed()
{
	if (Preview && Preview->GetAppearance())
	{
		Preview->GetAppearance()->ApplyAppearance(Appearance);
	}
	OnChanged.Broadcast();
}
