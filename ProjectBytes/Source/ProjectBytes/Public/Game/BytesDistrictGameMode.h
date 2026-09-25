#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/BytesTypes.h"
#include "BytesDistrictGameMode.generated.h"

class ABytesPlayerState;
class UBytesDistrictServerSubsystem;

/**
 * Game mode for district servers (the GlobalDefaultServerGameMode; set it, or a Blueprint child, as the
 * GameMode Override on your district maps so PIE uses it too).
 *
 * Login pipeline:
 *   PreLogin      verify the ?ticket= signature/expiry/server, capacity, district requirements -> reject early
 *   InitNewPlayer apply the ticket's character identity to the player state
 *   PostLogin     redeem the ticket with the backend (one-time use) and refresh the character record;
 *                 kick if the backend refuses it
 *   Logout        drop presence
 *
 * Unmanaged servers (no -District=, e.g. PIE) accept ticketless players with an offline dev identity:
 *   open 127.0.0.1?BytesName=Vex?BytesFaction=Criminal?BytesRank=80?BytesThreat=Silver?BytesFlags=tester
 */
UCLASS()
class PROJECTBYTES_API ABytesDistrictGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABytesDistrictGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/** Grant standing (rank XP) and money; persisted through the backend when managed. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Bytes")
	void AwardProgress(APlayerController* Player, int32 StandingDelta, int32 MoneyDelta);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Bytes")
	void SetThreat(APlayerController* Player, EBytesThreat NewThreat);

	UFUNCTION(BlueprintPure, Category = "Bytes")
	FBytesDistrictRequirements GetActiveRequirements() const;

	/** Hook for spawning/outfitting by faction etc. Identity is already set when this fires. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Bytes")
	void OnCharacterEntered(APlayerController* Player, const FBytesPublicIdentity& Identity);

protected:
	/** Re-check requirements from the ticket on the server too (the backend already checked when issuing it). */
	UPROPERTY(EditDefaultsOnly, Category = "Bytes")
	bool bEnforceRequirementsOnServer = true;

	/** Offline dev mode only: standing per rank used to compute rank locally (backend: standingPerRank). */
	UPROPERTY(EditDefaultsOnly, Category = "Bytes")
	int32 OfflineStandingPerRank = 1000;

private:
	UBytesDistrictServerSubsystem* GetServerSubsystem() const;
	bool ResolveIdentity(const FString& Options, bool bCommit, FBytesTicketClaims& OutClaims, FString& OutError);
	bool ResolveOfflineIdentity(const FString& Options, bool bCommit, FBytesTicketClaims& OutClaims, FString& OutError);

	/** CharacterId -> controller, to prevent the same character being in the district twice. */
	TMap<FString, TWeakObjectPtr<APlayerController>> CharacterControllers;
	int32 OfflinePlayerCounter = 0;
};
