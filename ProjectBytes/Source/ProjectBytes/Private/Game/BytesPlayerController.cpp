#include "Game/BytesPlayerController.h"
#include "Client/BytesAccountSubsystem.h"
#include "Game/BytesCharacter.h"
#include "Game/BytesDistrictGameMode.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

void ABytesPlayerController::ClientWasKicked_Implementation(const FText& KickReason)
{
	Super::ClientWasKicked_Implementation(KickReason);
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UBytesAccountSubsystem* Account = GameInstance->GetSubsystem<UBytesAccountSubsystem>())
		{
			Account->NotifyKicked(KickReason.ToString());
		}
	}
}

void ABytesPlayerController::ServerDevAwardProgress_Implementation(int32 StandingDelta, int32 MoneyDelta)
{
#if !UE_BUILD_SHIPPING
	if (ABytesDistrictGameMode* GameMode = GetWorld()->GetAuthGameMode<ABytesDistrictGameMode>())
	{
		GameMode->AwardProgress(this, StandingDelta, MoneyDelta);
	}
#endif
}

void ABytesPlayerController::ServerDevSetThreat_Implementation(EBytesThreat Threat)
{
#if !UE_BUILD_SHIPPING
	if (ABytesDistrictGameMode* GameMode = GetWorld()->GetAuthGameMode<ABytesDistrictGameMode>())
	{
		GameMode->SetThreat(this, Threat);
	}
#endif
}

void ABytesPlayerController::ServerDevSetMovementFeel_Implementation(uint8 Feel)
{
#if !UE_BUILD_SHIPPING
	ABytesCharacter* BytesCharacter = GetPawn<ABytesCharacter>();
	if (BytesCharacter && Feel <= static_cast<uint8>(EBytesMovementFeel::Realistic))
	{
		BytesCharacter->SetMovementFeel(static_cast<EBytesMovementFeel>(Feel));
	}
#endif
}
