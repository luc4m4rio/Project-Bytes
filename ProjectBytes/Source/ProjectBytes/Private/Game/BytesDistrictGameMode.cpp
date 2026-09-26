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
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/OutputDevice.h"
#include "Misc/OutputDeviceRedirector.h"
#include "Misc/ScopeLock.h"
#include "TimerManager.h"

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

UClass* ABytesDistrictGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	// Project Settings > Game > Project Bytes Online > District Pawn Class, if set; else the game mode default.
	if (UClass* PawnClass = UBytesSettings::Get()->DistrictPawnClass.LoadSynchronous())
	{
		return PawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

// ---- Staff commands (root cockpit) --------------------------------------------------------------

namespace
{
	/**
	 * Captures console output of an exec command so the cockpit sees it. Many commands print through GLog rather
	 * than the passed device, so this is also attached to GLog for the duration of the call (hence the lock).
	 */
	class FBytesCaptureOutput : public FOutputDevice
	{
	public:
		virtual void Serialize(const TCHAR* Line, ELogVerbosity::Type Verbosity, const FName& Category) override
		{
			FScopeLock Lock(&Mutex);
			if (Text.Len() < 8000)
			{
				Text += Line;
				Text += TEXT("\n");
			}
		}

		FString Get()
		{
			FScopeLock Lock(&Mutex);
			return Text;
		}

	private:
		FCriticalSection Mutex;
		FString Text;
	};
}

void ABytesDistrictGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (UBytesDistrictServerSubsystem* Server = GetServerSubsystem())
	{
		StaffCommandHandle = Server->OnCommand.AddUObject(this, &ThisClass::HandleStaffCommand);
	}
}

void ABytesDistrictGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UBytesDistrictServerSubsystem* Server = GetServerSubsystem())
	{
		Server->OnCommand.Remove(StaffCommandHandle);
	}
	Super::EndPlay(EndPlayReason);
}

APlayerController* ABytesDistrictGameMode::FindPlayerByCharacter(const FString& CharacterId) const
{
	const TWeakObjectPtr<APlayerController>* Found = CharacterControllers.Find(CharacterId);
	return Found ? Found->Get() : nullptr;
}

void ABytesDistrictGameMode::StaffMessageAll(const FString& Message, const FString& Style)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (ABytesPlayerController* PC = Cast<ABytesPlayerController>(It->Get()))
		{
			PC->ClientStaffMessage(Message, Style);
		}
	}
}

void ABytesDistrictGameMode::HandleStaffCommand(const FBytesServerCommand& Command)
{
	UBytesDistrictServerSubsystem* Server = GetServerSubsystem();
	if (!Server)
	{
		return;
	}
	const FString& Id = Command.CommandId;

	if (Command.Type == TEXT("broadcast"))
	{
		StaffMessageAll(Command.Message, Command.Style);
		Server->AckCommand(Id, true, FString::Printf(TEXT("Shown to %d player(s)"), GetNumPlayers()));
		return;
	}
	if (Command.Type == TEXT("shutdown"))
	{
		const int32 Delay = FMath::Clamp(Command.DelaySeconds, 0, 600);
		StaffMessageAll(FString::Printf(TEXT("%s (closing in %d s)"), *Command.Message, Delay), TEXT("warning"));
		// A newer shutdown command replaces an older countdown completely.
		GetWorldTimerManager().ClearTimer(ShutdownWarningTimer);
		if (Delay > 15)
		{
			GetWorldTimerManager().SetTimer(ShutdownWarningTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				StaffMessageAll(TEXT("District closing in 10 seconds"), TEXT("warning"));
			}), Delay - 10.f, false);
		}
		GetWorldTimerManager().SetTimer(ShutdownTimer, FTimerDelegate::CreateUObject(this, &ThisClass::FinishStaffShutdown, Command.Message),
			FMath::Max(0.1f, static_cast<float>(Delay)), false);
		Server->AckCommand(Id, true, FString::Printf(TEXT("Shutting down in %d s with %d player(s)"), Delay, GetNumPlayers()));
		return;
	}
	if (Command.Type == TEXT("exec"))
	{
		UE_LOG(LogBytes, Display, TEXT("Staff exec: %s"), *Command.ConsoleCommand);
		FBytesCaptureOutput Output;
		GLog->AddOutputDevice(&Output);
		const bool bHandled = GEngine && GEngine->Exec(GetWorld(), *Command.ConsoleCommand, Output);
		GLog->RemoveOutputDevice(&Output);
		const FString Text = Output.Get();
		Server->AckCommand(Id, bHandled, bHandled ? (Text.IsEmpty() ? FString(TEXT("OK")) : Text) : FString(TEXT("Command not recognised")));
		return;
	}

	// Everything else targets one player.
	APlayerController* Player = FindPlayerByCharacter(Command.CharacterId);
	ABytesPlayerController* BytesPlayer = Cast<ABytesPlayerController>(Player);
	if (!Player)
	{
		Server->AckCommand(Id, false, TEXT("Player is no longer on this server"));
		return;
	}
	if (Command.Type == TEXT("message"))
	{
		if (BytesPlayer)
		{
			BytesPlayer->ClientStaffMessage(Command.Message, Command.Style.IsEmpty() ? FString(TEXT("info")) : Command.Style);
		}
		Server->AckCommand(Id, BytesPlayer != nullptr, BytesPlayer ? TEXT("Delivered") : TEXT("Player can't receive messages"));
	}
	else if (Command.Type == TEXT("kick"))
	{
		const bool bKicked = GameSession && GameSession->KickPlayer(Player, FText::FromString(Command.Message));
		Server->AckCommand(Id, bKicked, bKicked ? TEXT("Kicked") : TEXT("Kick failed"));
	}
	else if (Command.Type == TEXT("refresh_character"))
	{
		TWeakObjectPtr<APlayerController> WeakPlayer(Player);
		TWeakObjectPtr<UBytesDistrictServerSubsystem> WeakServer(Server);
		Server->FetchCharacter(Command.CharacterId, [WeakPlayer, WeakServer, Id](bool bSuccess, const FBytesCharacter& Character)
		{
			APlayerController* PC = WeakPlayer.Get();
			ABytesPlayerState* State = PC ? PC->GetPlayerState<ABytesPlayerState>() : nullptr;
			if (bSuccess && State)
			{
				State->Money = Character.Money;
				State->Standing = Character.Standing;
				State->SetIdentity(FBytesPublicIdentity::FromCharacter(Character));
				if (ABytesPlayerController* BytesPC = Cast<ABytesPlayerController>(PC))
				{
					BytesPC->ClientRefreshAccount(); // wallet/inventory/mail live on the client's account view
				}
			}
			if (UBytesDistrictServerSubsystem* S = WeakServer.Get())
			{
				S->AckCommand(Id, bSuccess && State, bSuccess ? (State ? TEXT("Refreshed") : TEXT("Player left before the refresh")) : TEXT("Backend lookup failed"));
			}
		});
	}
	else
	{
		Server->AckCommand(Id, false, FString::Printf(TEXT("Unknown command type '%s'"), *Command.Type));
	}
}

void ABytesDistrictGameMode::FinishStaffShutdown(FString Message)
{
	TArray<APlayerController*> Players;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = It->Get())
		{
			Players.Add(PC);
		}
	}
	for (APlayerController* PC : Players)
	{
		if (GameSession)
		{
			GameSession->KickPlayer(PC, FText::FromString(Message.IsEmpty() ? FString(TEXT("Server shut down by staff")) : Message));
		}
	}
	UE_LOG(LogBytes, Display, TEXT("Shutting down by staff request"));
	// Give the reliable kick messages a second to reach clients before the process exits.
	FTimerHandle ExitTimer;
	GetWorldTimerManager().SetTimer(ExitTimer, FTimerDelegate::CreateLambda([]() { RequestEngineExit(TEXT("Root cockpit shutdown")); }), 1.f, false);
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
