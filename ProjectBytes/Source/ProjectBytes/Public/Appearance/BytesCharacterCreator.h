#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Appearance/BytesAppearanceTypes.h"
#include "Client/BytesAccountSubsystem.h"
#include "BytesCharacterCreator.generated.h"

class ABytesCreatorPreviewActor;
class UBytesAppearanceSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBytesOnCreatorChanged);

/** A pickable item for creator UI lists; locked items are shown greyed out with the reason (APB style). */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesCreatorOption
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Creator")
	FString Id;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Creator")
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Creator")
	bool bLocked = false;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Creator")
	FString LockReason;
};

/**
 * One character-creator session: edits a working FBytesAppearance, drives the preview mannequin, keeps undo/redo,
 * and saves either a new character or a re-edit of an existing one (validated again by the backend).
 * Get one from UBytesAppearanceSubsystem::BeginCreator. Everything is Blueprint-callable for your UMG screens;
 * bytes.Creator.* console commands drive it without UI.
 *
 * Slider drags: call RecordUndo() once when the drag starts, then SetMorph(..., bRecordUndo=false) every tick.
 */
UCLASS(BlueprintType)
class PROJECTBYTES_API UBytesCharacterCreator : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UBytesAppearanceSubsystem* InAppearance);
	void SpawnPreview(UWorld* World);
	void DestroyPreview();

	// ---- Session --------------------------------------------------------------------------------

	/** New character (rank 1 unlocks). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void StartNew(const FString& Body, EBytesFaction NewFaction);

	/** Re-edit an existing character of the logged-in account (its rank/faction decide unlocks). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	bool StartEditing(const FString& CharacterIdOrName);

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	bool IsEditingExisting() const { return !EditingCharacterId.IsEmpty(); }

	/** Only for new characters: faction decides which items are available. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void SetFaction(EBytesFaction NewFaction);

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	EBytesFaction GetFaction() const { return Faction; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	int32 GetRank() const { return Rank; }

	// ---- Editing --------------------------------------------------------------------------------

	/** Switching body keeps sliders and colours, drops parts that don't exist for the new body. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void SetBody(const FString& Body);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void SetMorph(const FString& MorphId, float Value, bool bRecordUndo = true);

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	float GetMorph(const FString& MorphId) const;

	/** Empty category = all sliders. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void ResetMorphs(const FString& Category);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void SetColor(const FString& ColorId, FLinearColor Color, bool bRecordUndo = true);

	/** "#rrggbb". Returns false if not a valid colour. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	bool SetColorHex(const FString& ColorId, const FString& Hex, bool bRecordUndo = true);

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	FLinearColor GetColor(const FString& ColorId) const;

	/** Empty PartId clears the slot (required slots fall back to their default on save). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	bool SetPart(const FString& SlotId, const FString& PartId);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void SetPartColor(const FString& SlotId, int32 Channel, FLinearColor Color, bool bRecordUndo = true);

	/** Adds a layer centred on the region; returns its index or INDEX_NONE if not allowed. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	int32 AddTattoo(const FString& DecalId, const FString& RegionId);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void UpdateTattoo(int32 Index, const FBytesTattooLayer& Layer, bool bRecordUndo = true);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void RemoveTattoo(int32 Index);

	/** Reorder layers (later layers draw on top). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void MoveTattooLayer(int32 Index, int32 NewIndex);

	/** Copies the layer onto the opposite body region (left arm -> right arm), flipped. Returns new index. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	int32 MirrorTattoo(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void Randomize(int32 Seed = -1);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void RecordUndo();

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	bool Undo();

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	bool Redo();

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	bool CanUndo() const { return UndoStack.Num() > 0; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	bool CanRedo() const { return RedoStack.Num() > 0; }

	// ---- Queries for UI -------------------------------------------------------------------------

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	FBytesAppearance GetAppearance() const { return Appearance; }

	const FBytesAppearance& GetAppearanceRef() const { return Appearance; }

	/** Reasons the current look can't be saved (locked items, bad colours...). Empty = OK. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	TArray<FString> Validate() const;

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	TArray<FBytesCreatorOption> GetPartOptions(const FString& SlotId) const;

	/** Designs allowed on the region (empty region = all designs). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	TArray<FBytesCreatorOption> GetDecalOptions(const FString& RegionId) const;

	UFUNCTION(BlueprintPure, Category = "Bytes|Creator")
	ABytesCreatorPreviewActor* GetPreview() const { return Preview; }

	UPROPERTY(BlueprintAssignable, Category = "Bytes|Creator")
	FBytesOnCreatorChanged OnChanged;

	// ---- Saving ---------------------------------------------------------------------------------

	/** New character: creates it with Name. Existing: saves the new look (Name ignored). */
	void Save(const FString& Name, FBytesDone Done);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator", meta = (DisplayName = "Save"))
	void K2_Save(const FString& Name, FBytesOnResult OnComplete);

private:
	const FBytesAppearanceCatalog& Catalog() const;
	void PushUndo(TArray<FString>& Stack);
	void Changed();

	TWeakObjectPtr<UBytesAppearanceSubsystem> AppearanceSubsystem;
	FBytesAppearance Appearance;
	EBytesFaction Faction = EBytesFaction::Enforcer;
	int32 Rank = 1;
	FString EditingCharacterId;
	TArray<FString> UndoStack;
	TArray<FString> RedoStack;

	UPROPERTY(Transient)
	TObjectPtr<ABytesCreatorPreviewActor> Preview;

	bool bSpawnedPreview = false;
	TWeakObjectPtr<AActor> PreviousViewTarget;
};
