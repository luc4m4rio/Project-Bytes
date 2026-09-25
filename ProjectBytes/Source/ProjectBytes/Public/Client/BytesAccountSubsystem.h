#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/EngineBaseTypes.h"
#include "Core/BytesTypes.h"
#include "BytesAccountSubsystem.generated.h"

class UNetDriver;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBytesOnResult, bool, bSuccess, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBytesOnAccountStateChanged);

using FBytesDone = TFunction<void(bool bSuccess, const FString& Error)>;

UENUM(BlueprintType)
enum class EBytesClientState : uint8
{
	LoggedOut,
	LoggingIn,
	/** Logged in, sitting in the frontend picking a character / district. */
	CharacterSelect,
	/** Ticket requested or travelling to a district server. */
	Joining,
	InDistrict,
};

/**
 * Client side of the APB-style flow:
 *
 *   Login -> list/create/select character -> list districts (with per-character eligibility)
 *         -> JoinDistrict: backend checks requirements, returns address + signed ticket -> ClientTravel
 *
 * Lives on the GameInstance, so the session survives map travel between districts and the frontend.
 * Everything is reachable from Blueprints (build your UMG frontend on top of it) and from the console
 * (bytes.* commands, see BytesConsoleCommands.cpp). Command-line auto login for playtest clients:
 *
 *   -BytesUser=tester1 [-BytesPass=playtest] [-BytesAutoRegister] [-BytesCharacter=Tester1]
 *   [-BytesFaction=Criminal] [-BytesDistrict=financial]
 */
UCLASS()
class PROJECTBYTES_API UBytesAccountSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ---- Native API --------------------------------------------------------------------------------

	void Register(const FString& Username, const FString& Password, FBytesDone Done = nullptr);
	/** Logs in, then loads characters and districts. */
	void Login(const FString& Username, const FString& Password, FBytesDone Done = nullptr);
	void Logout();
	void RefreshCharacters(FBytesDone Done = nullptr);
	void CreateCharacter(const FString& Name, EBytesFaction Faction, const FString& Appearance = FString(), FBytesDone Done = nullptr);
	void DeleteCharacter(const FString& CharacterIdOrName, FBytesDone Done = nullptr);
	void RefreshDistricts(FBytesDone Done = nullptr);
	/** Asks the backend for a ticket into DistrictId (optionally a specific instance) and travels there. */
	void JoinDistrict(const FString& DistrictId, const FString& InstanceId = FString(), FBytesDone Done = nullptr);
	/** Dev only (backend devMode): change the selected character's rank/threat to test district requirements. */
	void DevSetStats(int32 Rank, const FString& Threat, FBytesDone Done = nullptr);

	const FBytesCharacter* FindCharacter(const FString& CharacterIdOrName) const;
	const FBytesCharacter* GetSelectedCharacterPtr() const { return FindCharacter(SelectedCharacterId); }
	const FBytesDistrict* FindDistrict(const FString& DistrictId) const;
	const TArray<FBytesCharacter>& GetCharactersRef() const { return Characters; }
	const TArray<FBytesDistrict>& GetDistrictsRef() const { return Districts; }

	/** Called by ABytesPlayerController when the server kicks us, so the reason survives the map change. */
	void NotifyKicked(const FString& Reason);

	// ---- Blueprint API -----------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Bytes|Account", meta = (DisplayName = "Register Account"))
	void K2_Register(const FString& Username, const FString& Password, FBytesOnResult OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Account", meta = (DisplayName = "Login"))
	void K2_Login(const FString& Username, const FString& Password, FBytesOnResult OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Account", meta = (DisplayName = "Logout"))
	void K2_Logout() { Logout(); }

	UFUNCTION(BlueprintCallable, Category = "Bytes|Characters", meta = (DisplayName = "Refresh Characters"))
	void K2_RefreshCharacters(FBytesOnResult OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Characters", meta = (DisplayName = "Create Character"))
	void K2_CreateCharacter(const FString& Name, EBytesFaction Faction, const FString& Appearance, FBytesOnResult OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Characters", meta = (DisplayName = "Delete Character"))
	void K2_DeleteCharacter(const FString& CharacterId, FBytesOnResult OnComplete);

	/** Accepts a character id or name. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Characters")
	bool SelectCharacter(const FString& CharacterIdOrName);

	UFUNCTION(BlueprintCallable, Category = "Bytes|Districts", meta = (DisplayName = "Refresh Districts"))
	void K2_RefreshDistricts(FBytesOnResult OnComplete);

	/** Leave InstanceId empty to let the backend pick (fills the busiest instance with room). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Districts", meta = (DisplayName = "Join District"))
	void K2_JoinDistrict(const FString& DistrictId, const FString& InstanceId, FBytesOnResult OnComplete);

	/** Disconnects from the district server and loads the frontend map. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Districts")
	void ReturnToFrontend();

	UFUNCTION(BlueprintPure, Category = "Bytes|Account")
	bool IsLoggedIn() const { return !SessionToken.IsEmpty(); }

	UFUNCTION(BlueprintPure, Category = "Bytes|Account")
	EBytesClientState GetState() const { return State; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Account")
	FBytesAccount GetAccount() const { return Account; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Characters")
	TArray<FBytesCharacter> GetCharacters() const { return Characters; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Characters")
	bool GetSelectedCharacter(FBytesCharacter& OutCharacter) const;

	UFUNCTION(BlueprintPure, Category = "Bytes|Districts")
	TArray<FBytesDistrict> GetDistricts() const { return Districts; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Districts")
	FBytesJoinTicket GetCurrentDistrict() const { return CurrentTicket; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Account")
	FString GetLastError() const { return LastError; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Account")
	TArray<FString> GetLastErrorReasons() const { return LastErrorReasons; }

	/** Fires whenever anything above changes; bind your UI refresh to it. */
	UPROPERTY(BlueprintAssignable, Category = "Bytes|Account")
	FBytesOnAccountStateChanged OnStateChanged;

private:
	TMap<FString, FString> AuthHeaders() const;
	void SetState(EBytesClientState NewState);
	void SetError(const FString& Error, const TArray<FString>& Reasons = TArray<FString>());
	void ClearError();
	void Broadcast();
	void TravelTo(const FString& Url);

	void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	void HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);
	void HandlePostLoadMap(UWorld* World);
	bool IsOurWorld(const UWorld* World) const;

	void RunAutoLoginFromCommandLine();
	void AutoJoin(const FString& DistrictId, int32 AttemptsLeft);

	FString SessionToken;
	FBytesAccount Account;
	TArray<FBytesCharacter> Characters;
	FString SelectedCharacterId;
	TArray<FBytesDistrict> Districts;
	FBytesJoinTicket CurrentTicket;
	FString LastError;
	TArray<FString> LastErrorReasons;
	int32 LastJoinStatus = 0;
	EBytesClientState State = EBytesClientState::LoggedOut;

	FDelegateHandle NetworkFailureHandle;
	FDelegateHandle TravelFailureHandle;
	FDelegateHandle PostLoadMapHandle;
};
