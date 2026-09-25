#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Appearance/BytesAppearanceTypes.h"
#include "BytesAppearanceSubsystem.generated.h"

class UBytesCharacterCreator;

/**
 * Loads the appearance catalog (Content/Data/AppearanceCatalog.json, override with -BytesAppearanceCatalog=<file>)
 * and owns the active character-creator session. Exists on clients and servers.
 */
UCLASS()
class PROJECTBYTES_API UBytesAppearanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	static UBytesAppearanceSubsystem* Get(const UObject* WorldContextObject);

	const FBytesAppearanceCatalog& GetCatalog() const { return Catalog; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance", meta = (DisplayName = "Get Appearance Catalog"))
	FBytesAppearanceCatalog K2_GetCatalog() const { return Catalog; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance")
	bool IsCatalogLoaded() const { return bCatalogLoaded; }

	/** Parses a stored appearance; empty/invalid -> the catalog default for DefaultBody. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	FBytesAppearance ParseOrDefault(const FString& Json, const FString& DefaultBody = TEXT("male")) const;

	/** Random look using only items unlocked at Rank for Faction. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	FBytesAppearance Randomize(const FString& Body, int32 Rank, EBytesFaction Faction, int32 Seed = -1) const;

	/** Starts (or restarts) a creator session. Spawns a preview mannequin in the current world if bSpawnPreview. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	UBytesCharacterCreator* BeginCreator(bool bSpawnPreview = true);

	UFUNCTION(BlueprintPure, Category = "Bytes|Appearance")
	UBytesCharacterCreator* GetActiveCreator() const { return ActiveCreator; }

	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	void EndCreator();

	UFUNCTION(BlueprintCallable, Category = "Bytes|Appearance")
	bool ReloadCatalog();

private:
	FBytesAppearanceCatalog Catalog;
	bool bCatalogLoaded = false;

	UPROPERTY(Transient)
	TObjectPtr<UBytesCharacterCreator> ActiveCreator;
};
