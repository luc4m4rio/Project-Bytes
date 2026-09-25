#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Appearance/BytesAppearanceTypes.h"
#include "BytesAppearanceComponent.generated.h"

class ABytesPlayerState;
class UMaterialInstanceDynamic;
class USkeletalMeshComponent;
class UTexture2D;
class UTextureRenderTarget2D;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBytesOnAppearanceApplied);

USTRUCT()
struct FBytesMaterialList
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> Materials;
};

/**
 * Puts an FBytesAppearance on a skeletal mesh, APB style:
 *
 *   body       sets the body mesh (+ optional anim class) from the catalog
 *   morphs     slider values -> morph target weights on the body and every clothing part (so clothes follow
 *              the body shape); "height"-style sliders also scale the mesh
 *   colours    material vector parameters on the body and/or part materials (skin tone, hair colour...)
 *   parts      one follower USkeletalMeshComponent per clothing slot (leader pose = body), with
 *              primary/secondary/tertiary colour parameters
 *   tattoos    every layer is drawn into a transparent render target laid out like the skin UV atlas
 *              (regions from the catalog), which is bound to the skin materials' TattooOverlay parameter
 *
 * Assets are soft paths in the catalog and stream in asynchronously; missing ones are skipped with a warning,
 * so the system runs before any art exists. Does nothing visual on dedicated servers.
 *
 * With bFollowPlayerState (default), it applies the appearance replicated in the owning pawn's
 * ABytesPlayerState identity, so everyone in the district sees everyone's character.
 */
UCLASS(ClassGroup = (Bytes), meta = (BlueprintSpawnableComponent))
class PROJECTBYTES_API UBytesAppearanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBytesAppearanceComponent();

	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	void ApplyAppearance(const FBytesAppearance& Appearance);

	/** Empty or invalid JSON applies the catalog default look. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	void ApplyAppearanceJson(const FString& Json);

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance")
	FBytesAppearance GetAppearance() const { return Current; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance")
	UTextureRenderTarget2D* GetTattooTexture() const { return TattooTarget; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance")
	USkeletalMeshComponent* GetBodyMesh() const;

	/** Fires after meshes/materials have been updated (assets loaded). */
	UPROPERTY(BlueprintAssignable, Category = "Bytes|Appearance")
	FBytesOnAppearanceApplied OnAppearanceApplied;

	/** Apply the appearance from the owning pawn's ABytesPlayerState automatically. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	bool bFollowPlayerState = true;

	/** Component to drive. None = the first USkeletalMeshComponent on the owner (ACharacter's Mesh). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FName BodyMeshComponentName;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void HandleIdentityChanged(ABytesPlayerState* PlayerState);

	bool IsVisualNetMode() const;
	TArray<FSoftObjectPath> GatherAssets(const FBytesAppearance& Appearance) const;
	void OnAssetsLoaded(int32 Serial);
	void ApplyLoaded();
	void ApplyBody(USkeletalMeshComponent* Body);
	void ApplyParts(USkeletalMeshComponent* Body);
	void ApplyMorphs(USkeletalMeshComponent* Body);
	void ApplyColors();
	void RedrawTattoos();
	void CollectMaterials(USkeletalMeshComponent* Mesh, const TArray<FString>& SlotFilter, TArray<TObjectPtr<UMaterialInstanceDynamic>>& Out) const;

	void RemovePart(const FString& Slot);

	FBytesAppearance Current;
	/** Catalog paths whose package doesn't exist (art not made yet): skip instead of re-requesting every edit. */
	mutable TSet<FString> MissingPackages;
	FString AppliedBody;
	TArray<FBytesTattooLayer> DrawnTattoos;
	bool bTattoosDrawn = false;
	int32 LoadSerial = 0;
	TSharedPtr<FStreamableHandle> LoadHandle;
	TWeakObjectPtr<ABytesPlayerState> BoundPlayerState;
	FVector BaseMeshScale = FVector::OneVector;
	bool bBaseScaleCaptured = false;

	UPROPERTY(Transient)
	TMap<FString, TObjectPtr<USkeletalMeshComponent>> PartComponents;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> BodyMaterials;

	UPROPERTY(Transient)
	TMap<FString, FBytesMaterialList> PartMaterials;

	UPROPERTY(Transient)
	TObjectPtr<UTextureRenderTarget2D> TattooTarget;
};
