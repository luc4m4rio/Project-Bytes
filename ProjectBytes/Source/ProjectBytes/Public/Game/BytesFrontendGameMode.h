#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BytesFrontendGameMode.generated.h"

/**
 * Local-only game mode for the frontend map (login / character select / district list).
 * Swap HUDClass for your UMG-driven HUD once you build the real frontend.
 */
UCLASS()
class PROJECTBYTES_API ABytesFrontendGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABytesFrontendGameMode();
};
