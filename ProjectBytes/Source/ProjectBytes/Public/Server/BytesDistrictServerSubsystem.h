#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/Ticker.h"
#include "Core/BytesTypes.h"
#include "BytesDistrictServerSubsystem.generated.h"

struct FBytesHttpResult;

/**
 * Server side of the district model. A server becomes "managed" when launched with -District=<id>:
 *
 *   - waits until the net driver is listening, then registers with the backend (district id, host, port)
 *   - receives its instance id (e.g. financial-2), the district requirements and the ticket-signing key
 *   - heartbeats the list of online characters (presence + population for the district list)
 *   - verifies join tickets offline, redeems them once, and writes progression back
 *
 * Command line:
 *   -District=financial -port=7777 [-BytesBackend=http://127.0.0.1:8080] [-BytesServerKey=...]
 *   [-BytesPublicHost=127.0.0.1] [-BytesRegion=EU] [-BytesMaxPlayers=80]
 *
 * Without -District (PIE, ad-hoc listen servers) the server is "unmanaged": ABytesDistrictGameMode then
 * hands out offline dev identities instead of requiring tickets.
 */
UCLASS()
class PROJECTBYTES_API UBytesDistrictServerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Bytes|Server")
	bool IsManaged() const { return !DistrictId.IsEmpty(); }

	UFUNCTION(BlueprintPure, Category = "Bytes|Server")
	bool IsRegistered() const { return !ServerId.IsEmpty(); }

	UFUNCTION(BlueprintPure, Category = "Bytes|Server")
	FString GetDistrictId() const { return DistrictId; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Server")
	FString GetInstanceId() const { return InstanceId; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Server")
	FString GetInstanceDisplayName() const { return DisplayName; }

	const FString& GetServerId() const { return ServerId; }

	/** 0 when unknown (unmanaged): fall back to GameSession->MaxPlayers. */
	int32 GetMaxPlayers() const { return MaxPlayers; }

	/** Backend requirements when managed, UBytesSettings::OfflineRequirements otherwise. */
	FBytesDistrictRequirements GetRequirements() const;

	bool VerifyTicket(const FString& Ticket, FBytesTicketClaims& OutClaims, FString& OutError) const;

	/** One-time redemption. Result.Status == 0 means the backend was unreachable. */
	void RedeemTicket(const FString& TicketId, const FString& CharacterId,
		TFunction<void(const FBytesHttpResult& Result, const FBytesRedeemResponse& Response)> Done);

	/** Persist progression. Threat empty = unchanged. */
	void ReportProgress(const FString& CharacterId, int32 StandingDelta, int32 MoneyDelta, const FString& Threat,
		TFunction<void(bool bSuccess, const FBytesCharacter& Character)> Done);

	void AddOnlineCharacter(const FString& CharacterId);
	void RemoveOnlineCharacter(const FString& CharacterId);

private:
	bool Tick(float DeltaTime);
	bool TryGetListenPort(int32& OutPort) const;
	void Register(int32 ListenPort);
	void SendHeartbeat();
	void Unregister();
	TMap<FString, FString> ServerHeaders() const;

	// From the command line
	FString DistrictId;
	FString PublicHost = TEXT("127.0.0.1");
	FString Region;
	int32 CommandLinePort = 7777;
	int32 RequestedMaxPlayers = 0;

	// From the backend
	FString ServerId;
	FString InstanceId;
	FString DisplayName;
	int32 MaxPlayers = 0;
	FBytesDistrictRequirements Requirements;
	TArray<uint8> TicketKey;
	int32 HeartbeatSeconds = 5;

	TSet<FString> OnlineCharacters;
	bool bRegisterInFlight = false;
	bool bPresenceDirty = false;
	double NextRegisterAttempt = 0.0;
	double LastHeartbeat = 0.0;
	FTSTicker::FDelegateHandle TickHandle;
};
