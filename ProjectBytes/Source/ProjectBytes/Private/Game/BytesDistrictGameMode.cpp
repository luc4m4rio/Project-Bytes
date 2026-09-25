#include "Game/BytesDistrictGameMode.h"
#include "Core/BytesBackendHttp.h"
#include "Game/BytesDebugHUD.h"
#include "Game/BytesPlayerController.h"
#include "Game/BytesPlayerState.h"
#include "Core/BytesSettings.h"
#include "Server/BytesDistrictServerSubsystem.h"
#include "ProjectBytes.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

ABytesDistrictGameMode::ABytesDistrictGameMode()
{
	PlayerStateClass = ABytesPlayerState::StaticClass();
	PlayerControllerClass = ABytesPlayerController::StaticClass();
	HUDClass = ABytesDebugHUD::StaticClass();
}

UBytesDistrictServerSubsystem* ABytesDistrictGameMode::GetServerSubsystem() const
{
	const UGameInstance* GameInstance = GetGameInstance();
	return GameInstance ? GameInstance->GetSubsystem<UBytesDistrictServerSubsystem>() : nullptr;
}

FBytesDistrictRequirements ABytesDistrictGameMode::GetActiveRequirements() const
{
	const UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	return Server ? Server->GetRequirements() : UBytesSettings::Get()->OfflineRequirements;
}

// ---- Login pipeline -----------------------------------------------------------------------------

void ABytesDistrictGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}

	FBytesTicketClaims Claims;
	if (!ResolveIdentity(Options, /*bCommit*/ false, Claims, ErrorMessage))
	{
		UE_LOG(LogBytes, Display, TEXT("Rejected connection from %s: %s"), *Address, *ErrorMessage);
		return;
	}

	const UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	const int32 Capacity = Server && Server->GetMaxPlayers() > 0 ? Server->GetMaxPlayers() : (GameSession ? GameSession->MaxPlayers : 0);
	if (Capacity > 0 && GetNumPlayers() >= Capacity)
	{
		ErrorMessage = TEXT("This district instance is full");
	}
}

FString ABytesDistrictGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString Error = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if (!Error.IsEmpty())
	{
		return Error;
	}

	FBytesTicketClaims Claims;
	if (!ResolveIdentity(Options, /*bCommit*/ true, Claims, Error))
	{
		return Error;
	}

	// Same character connecting again (e.g. reconnect after a crash): the newest connection wins.
	if (const TWeakObjectPtr<APlayerController>* Existing = CharacterControllers.Find(Claims.CharacterId))
	{
		if (APlayerController* OldController = Existing->Get(); OldController && OldController != NewPlayerController && GameSession)
		{
			GameSession->KickPlayer(OldController, FText::FromString(TEXT("Logged in from another location")));
		}
	}
	CharacterControllers.Add(Claims.CharacterId, NewPlayerController);

	if (ABytesPlayerState* PS = NewPlayerController->GetPlayerState<ABytesPlayerState>())
	{
		PS->AccountId = Claims.AccountId;
		PS->PendingTicketId = Claims.TicketId;
		PS->SetIdentity(FBytesPublicIdentity::FromClaims(Claims));
	}
	return FString();
}

void ABytesDistrictGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ABytesPlayerState* PS = NewPlayer ? NewPlayer->GetPlayerState<ABytesPlayerState>() : nullptr;
	UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	if (!PS || !Server)
	{
		return;
	}

	const FBytesPublicIdentity Identity = PS->GetIdentity();
	UE_LOG(LogBytes, Display, TEXT("%s entered: %s rank %d %s"), *Identity.Name, *BytesEnums::ToString(Identity.Faction),
		Identity.Rank, *BytesEnums::ToString(Identity.Threat));
	Server->AddOnlineCharacter(Identity.CharacterId);

	if (Server->IsManaged() && !PS->PendingTicketId.IsEmpty())
	{
		TWeakObjectPtr<ThisClass> WeakThis(this);
		TWeakObjectPtr<APlayerController> WeakPlayer(NewPlayer);
		Server->RedeemTicket(PS->PendingTicketId, Identity.CharacterId,
			[WeakThis, WeakPlayer](const FBytesHttpResult& Result, const FBytesRedeemResponse& Response)
			{
				ThisClass* GameMode = WeakThis.Get();
				APlayerController* Player = WeakPlayer.Get();
				ABytesPlayerState* State = Player ? Player->GetPlayerState<ABytesPlayerState>() : nullptr;
				if (!GameMode || !State)
				{
					return;
				}
				State->PendingTicketId.Reset();
				if (Result.Status == 0)
				{
					// Backend unreachable: keep the (signature-verified) player rather than kicking everyone.
					UE_LOG(LogBytes, Warning, TEXT("Could not redeem ticket for %s (backend down), keeping ticket identity"), *State->GetIdentity().Name);
					return;
				}
				if (!Result.bOk)
				{
					UE_LOG(LogBytes, Display, TEXT("Kicking %s: %s"), *State->GetIdentity().Name, *Result.Describe());
					if (GameMode->GameSession)
					{
						GameMode->GameSession->KickPlayer(Player, FText::FromString(Result.Describe()));
					}
					return;
				}
				// Authoritative, fresh record from the backend (the ticket may be up to a minute old).
				State->Money = Response.Character.Money;
				State->Standing = Response.Character.Standing;
				State->SetIdentity(FBytesPublicIdentity::FromCharacter(Response.Character));
			});
	}

	OnCharacterEntered(NewPlayer, Identity);
}

void ABytesDistrictGameMode::Logout(AController* Exiting)
{
	if (const ABytesPlayerState* PS = Exiting ? Exiting->GetPlayerState<ABytesPlayerState>() : nullptr)
	{
		const FString& CharacterId = PS->GetIdentity().CharacterId;
		const TWeakObjectPtr<APlayerController>* Registered = CharacterControllers.Find(CharacterId);
		// Only clear presence if this controller is the character's current one (not a replaced connection).
		if (Registered && (!Registered->IsValid() || Registered->Get() == Exiting))
		{
			CharacterControllers.Remove(CharacterId);
			if (UBytesDistrictServerSubsystem* Server = GetServerSubsystem())
			{
				Server->RemoveOnlineCharacter(CharacterId);
			}
			UE_LOG(LogBytes, Display, TEXT("%s left the district"), *PS->GetIdentity().Name);
		}
	}
	Super::Logout(Exiting);
}

// ---- Identity -----------------------------------------------------------------------------------

bool ABytesDistrictGameMode::ResolveIdentity(const FString& Options, bool bCommit, FBytesTicketClaims& OutClaims, FString& OutError)
{
	const UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	if (Server && Server->IsManaged())
	{
		const FString Ticket = UGameplayStatics::ParseOption(Options, TEXT("ticket"));
		if (Ticket.IsEmpty())
		{
			OutError = TEXT("This district only accepts players sent by the backend (join through the district list)");
			return false;
		}
		if (!Server->VerifyTicket(Ticket, OutClaims, OutError))
		{
			return false;
		}
	}
	else if (!ResolveOfflineIdentity(Options, bCommit, OutClaims, OutError))
	{
		return false;
	}

	if (bEnforceRequirementsOnServer)
	{
		const TArray<FString> Reasons = GetActiveRequirements().Evaluate(OutClaims.Rank, OutClaims.Threat, OutClaims.Faction, OutClaims.AccountFlags);
		if (Reasons.Num() > 0)
		{
			OutError = FString::Printf(TEXT("%s can't enter this district: %s"), *OutClaims.CharacterName, *FString::Join(Reasons, TEXT("; ")));
			return false;
		}
	}
	return true;
}

bool ABytesDistrictGameMode::ResolveOfflineIdentity(const FString& Options, bool bCommit, FBytesTicketClaims& OutClaims, FString& OutError)
{
#if UE_BUILD_SHIPPING
	OutError = TEXT("Server is not connected to a backend");
	return false;
#else
	if (!UBytesSettings::Get()->bAllowOfflineDevLogins)
	{
		OutError = TEXT("Server is not connected to a backend and offline dev logins are disabled");
		return false;
	}

	const int32 Number = OfflinePlayerCounter + 1;
	if (bCommit)
	{
		++OfflinePlayerCounter;
	}

	FString Name = UGameplayStatics::ParseOption(Options, TEXT("BytesName"));
	if (Name.IsEmpty())
	{
		Name = FString::Printf(TEXT("Dev%d"), Number);
	}
	OutClaims = FBytesTicketClaims();
	OutClaims.CharacterId = TEXT("offline-") + Name;
	OutClaims.AccountId = TEXT("offline");
	OutClaims.CharacterName = Name;
	// Alternate factions so a multi-client PIE session has both sides by default.
	OutClaims.Faction = Number % 2 == 1 ? EBytesFaction::Enforcer : EBytesFaction::Criminal;
	BytesEnums::FromString(UGameplayStatics::ParseOption(Options, TEXT("BytesFaction")), OutClaims.Faction);
	BytesEnums::FromString(UGameplayStatics::ParseOption(Options, TEXT("BytesThreat")), OutClaims.Threat);
	const FString RankOption = UGameplayStatics::ParseOption(Options, TEXT("BytesRank"));
	OutClaims.Rank = RankOption.IsNumeric() ? FMath::Max(1, FCString::Atoi(*RankOption)) : 1;
	UGameplayStatics::ParseOption(Options, TEXT("BytesFlags")).ParseIntoArray(OutClaims.AccountFlags, TEXT(","));
	return true;
#endif
}

// ---- Progression --------------------------------------------------------------------------------

void ABytesDistrictGameMode::AwardProgress(APlayerController* Player, int32 StandingDelta, int32 MoneyDelta)
{
	ABytesPlayerState* PS = Player ? Player->GetPlayerState<ABytesPlayerState>() : nullptr;
	UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	if (!PS || !Server)
	{
		return;
	}

	if (!Server->IsManaged())
	{
		PS->Standing = FMath::Max(0, PS->Standing + StandingDelta);
		PS->Money = FMath::Max(0, PS->Money + MoneyDelta);
		FBytesPublicIdentity Identity = PS->GetIdentity();
		Identity.Rank = FMath::Max(Identity.Rank, 1 + PS->Standing / FMath::Max(1, OfflineStandingPerRank));
		PS->SetIdentity(Identity);
		return;
	}

	TWeakObjectPtr<ABytesPlayerState> WeakPS(PS);
	Server->ReportProgress(PS->GetIdentity().CharacterId, StandingDelta, MoneyDelta, FString(),
		[WeakPS](bool bSuccess, const FBytesCharacter& Character)
		{
			if (ABytesPlayerState* State = WeakPS.Get(); State && bSuccess)
			{
				State->Money = Character.Money;
				State->Standing = Character.Standing;
				State->SetIdentity(FBytesPublicIdentity::FromCharacter(Character));
			}
		});
}

void ABytesDistrictGameMode::SetThreat(APlayerController* Player, EBytesThreat NewThreat)
{
	ABytesPlayerState* PS = Player ? Player->GetPlayerState<ABytesPlayerState>() : nullptr;
	UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	if (!PS || !Server)
	{
		return;
	}

	if (!Server->IsManaged())
	{
		FBytesPublicIdentity Identity = PS->GetIdentity();
		Identity.Threat = NewThreat;
		PS->SetIdentity(Identity);
		return;
	}

	TWeakObjectPtr<ABytesPlayerState> WeakPS(PS);
	Server->ReportProgress(PS->GetIdentity().CharacterId, 0, 0, BytesEnums::ToString(NewThreat),
		[WeakPS](bool bSuccess, const FBytesCharacter& Character)
		{
			if (ABytesPlayerState* State = WeakPS.Get(); State && bSuccess)
			{
				State->SetIdentity(FBytesPublicIdentity::FromCharacter(Character));
			}
		});
}
