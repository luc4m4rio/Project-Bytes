#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BytesTestFloorSubsystem.generated.h"

/**
 * Makes the empty /Engine/Maps/Entry dev map playable on foot: spawns a floor, a few landmark pillars (so
 * starts/stops/pivots are visible), a sun, and player starts (server only). Spawned locally and identically on
 * every machine, so client-side movement prediction has the same collision as the server.
 * Disable with UBytesSettings::bSpawnTestFloorOnEntryMap.
 */
UCLASS()
class PROJECTBYTES_API UBytesTestFloorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
