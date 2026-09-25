#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/BytesTypes.h"
#include "BytesPlayerController.generated.h"

UCLASS()
class PROJECTBYTES_API ABytesPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void ClientWasKicked_Implementation(const FText& KickReason) override;

	/** Dev cheat (ignored in Shipping): award standing/money through the real server -> backend path. */
	UFUNCTION(Server, Reliable)
	void ServerDevAwardProgress(int32 StandingDelta, int32 MoneyDelta);

	/** Dev cheat (ignored in Shipping). */
	UFUNCTION(Server, Reliable)
	void ServerDevSetThreat(EBytesThreat Threat);

	/** Dev (ignored in Shipping): switch movement feel on the server and locally so prediction stays in sync. */
	UFUNCTION(Server, Reliable)
	void ServerDevSetMovementFeel(uint8 Feel);
};
