#include "Client/BytesAccountSubsystem.h"
#include "Core/BytesBackendHttp.h"
#include "Core/BytesSettings.h"
#include "ProjectBytes.h"
#include "Containers/Ticker.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "UObject/UObjectGlobals.h"

namespace
{
	void Complete(const FBytesDone& Done, bool bSuccess, const FString& Error)
	{
		if (Done)
		{
			Done(bSuccess, Error);
		}
	}

	FBytesDone Wrap(const FBytesOnResult& OnComplete)
	{
		return [OnComplete](bool bSuccess, const FString& Error) { OnComplete.ExecuteIfBound(bSuccess, Error); };
	}

	TSharedPtr<FJsonObject> MakeBody()
	{
		return MakeShared<FJsonObject>();
	}
}

bool UBytesAccountSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UBytesAccountSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (GEngine)
	{
		NetworkFailureHandle = GEngine->OnNetworkFailure().AddUObject(this, &ThisClass::HandleNetworkFailure);
		TravelFailureHandle = GEngine->OnTravelFailure().AddUObject(this, &ThisClass::HandleTravelFailure);
	}
	PostLoadMapHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::HandlePostLoadMap);

	RunAutoLoginFromCommandLine();
}

void UBytesAccountSubsystem::Deinitialize()
{
	if (GEngine)
	{
		GEngine->OnNetworkFailure().Remove(NetworkFailureHandle);
		GEngine->OnTravelFailure().Remove(TravelFailureHandle);
	}
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(PostLoadMapHandle);
	Super::Deinitialize();
}

// ---- Account ------------------------------------------------------------------------------------

void UBytesAccountSubsystem::Register(const FString& Username, const FString& Password, FBytesDone Done)
{
	const TSharedPtr<FJsonObject> Body = MakeBody();
	Body->SetStringField(TEXT("username"), Username);
	Body->SetStringField(TEXT("password"), Password);

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/auth/register"), Body, TMap<FString, FString>(),
		[WeakThis, Username, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			if (!Result.bOk)
			{
				This->SetError(Result.Error, Result.Reasons);
			}
			else
			{
				UE_LOG(LogBytes, Display, TEXT("Registered account '%s'"), *Username);
			}
			Complete(Done, Result.bOk, Result.Describe());
		});
}

void UBytesAccountSubsystem::Login(const FString& Username, const FString& Password, FBytesDone Done)
{
	SetState(EBytesClientState::LoggingIn);

	const TSharedPtr<FJsonObject> Body = MakeBody();
	Body->SetStringField(TEXT("username"), Username);
	Body->SetStringField(TEXT("password"), Password);

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/auth/login"), Body, TMap<FString, FString>(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			FBytesLoginResponse Response;
			if (!Result.bOk || !Result.Parse(Response))
			{
				This->SetError(Result.bOk ? TEXT("Unexpected login response") : Result.Error, Result.Reasons);
				This->SetState(EBytesClientState::LoggedOut);
				Complete(Done, false, This->LastError);
				return;
			}

			This->SessionToken = Response.SessionToken;
			This->Account = Response.Account;
			This->ClearError();
			This->SetState(EBytesClientState::CharacterSelect);
			UE_LOG(LogBytes, Display, TEXT("Logged in as %s (%s)"), *This->Account.Username, *This->Account.AccountId);
			This->RefreshCharacters(Done);
		});
}

void UBytesAccountSubsystem::Logout()
{
	if (IsLoggedIn())
	{
		BytesHttp::Send(TEXT("POST"), TEXT("/v1/auth/logout"), MakeBody(), AuthHeaders(), nullptr);
	}
	const bool bWasInDistrict = State == EBytesClientState::InDistrict;
	SessionToken.Reset();
	Account = FBytesAccount();
	Characters.Reset();
	Districts.Reset();
	SelectedCharacterId.Reset();
	CurrentTicket = FBytesJoinTicket();
	SetState(EBytesClientState::LoggedOut);
	if (bWasInDistrict)
	{
		ReturnToFrontend();
	}
}

// ---- Characters ---------------------------------------------------------------------------------

void UBytesAccountSubsystem::RefreshCharacters(FBytesDone Done)
{
	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("GET"), TEXT("/v1/characters"), nullptr, AuthHeaders(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			FBytesCharacterListResponse Response;
			if (!Result.bOk || !Result.Parse(Response))
			{
				This->SetError(Result.Error, Result.Reasons);
				Complete(Done, false, Result.Describe());
				return;
			}

			This->Characters = Response.Characters;
			This->Account = Response.Account;
			if (!This->FindCharacter(This->SelectedCharacterId))
			{
				This->SelectedCharacterId = This->Characters.Num() > 0 ? This->Characters[0].CharacterId : FString();
			}
			This->Broadcast();
			This->RefreshDistricts();
			Complete(Done, true, FString());
		});
}

void UBytesAccountSubsystem::CreateCharacter(const FString& Name, EBytesFaction Faction, const FString& Appearance, FBytesDone Done)
{
	const TSharedPtr<FJsonObject> Body = MakeBody();
	Body->SetStringField(TEXT("name"), Name);
	Body->SetStringField(TEXT("faction"), BytesEnums::ToString(Faction));
	Body->SetStringField(TEXT("appearance"), Appearance);

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/characters"), Body, AuthHeaders(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			FBytesCharacterResponse Response;
			if (!Result.bOk || !Result.Parse(Response))
			{
				This->SetError(Result.Error, Result.Reasons);
				Complete(Done, false, Result.Describe());
				return;
			}
			UE_LOG(LogBytes, Display, TEXT("Created %s %s"), *BytesEnums::ToString(Response.Character.Faction), *Response.Character.Name);
			This->Characters.Add(Response.Character);
			This->ClearError();
			This->SelectCharacter(Response.Character.CharacterId);
			Complete(Done, true, FString());
		});
}

void UBytesAccountSubsystem::DeleteCharacter(const FString& CharacterIdOrName, FBytesDone Done)
{
	const FBytesCharacter* Character = FindCharacter(CharacterIdOrName);
	if (!Character)
	{
		Complete(Done, false, FString::Printf(TEXT("No character '%s' on this account"), *CharacterIdOrName));
		return;
	}

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("DELETE"), TEXT("/v1/characters/") + Character->CharacterId, nullptr, AuthHeaders(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			if (!Result.bOk)
			{
				This->SetError(Result.Error, Result.Reasons);
				Complete(Done, false, Result.Describe());
				return;
			}
			This->RefreshCharacters(Done);
		});
}

bool UBytesAccountSubsystem::SelectCharacter(const FString& CharacterIdOrName)
{
	const FBytesCharacter* Character = FindCharacter(CharacterIdOrName);
	if (!Character)
	{
		return false;
	}
	SelectedCharacterId = Character->CharacterId;
	Broadcast();
	RefreshDistricts();
	return true;
}

const FBytesCharacter* UBytesAccountSubsystem::FindCharacter(const FString& CharacterIdOrName) const
{
	if (CharacterIdOrName.IsEmpty())
	{
		return nullptr;
	}
	// FString == is case-insensitive, which is what we want for names.
	return Characters.FindByPredicate([&CharacterIdOrName](const FBytesCharacter& C)
	{
		return C.CharacterId == CharacterIdOrName || C.Name == CharacterIdOrName;
	});
}

bool UBytesAccountSubsystem::GetSelectedCharacter(FBytesCharacter& OutCharacter) const
{
	if (const FBytesCharacter* Character = GetSelectedCharacterPtr())
	{
		OutCharacter = *Character;
		return true;
	}
	return false;
}

// ---- Districts ----------------------------------------------------------------------------------

void UBytesAccountSubsystem::RefreshDistricts(FBytesDone Done)
{
	if (!IsLoggedIn())
	{
		Complete(Done, false, TEXT("Not logged in"));
		return;
	}

	FString Path = TEXT("/v1/districts");
	if (!SelectedCharacterId.IsEmpty())
	{
		Path += TEXT("?characterId=") + FGenericPlatformHttp::UrlEncode(SelectedCharacterId);
	}

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("GET"), Path, nullptr, AuthHeaders(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			FBytesDistrictListResponse Response;
			if (!Result.bOk || !Result.Parse(Response))
			{
				This->SetError(Result.Error, Result.Reasons);
				Complete(Done, false, Result.Describe());
				return;
			}
			This->Districts = Response.Districts;
			This->Broadcast();
			Complete(Done, true, FString());
		});
}

const FBytesDistrict* UBytesAccountSubsystem::FindDistrict(const FString& DistrictId) const
{
	return Districts.FindByPredicate([&DistrictId](const FBytesDistrict& D) { return D.DistrictId == DistrictId; });
}

void UBytesAccountSubsystem::JoinDistrict(const FString& DistrictId, const FString& InstanceId, FBytesDone Done)
{
	const FBytesCharacter* Character = GetSelectedCharacterPtr();
	if (!IsLoggedIn() || !Character)
	{
		SetError(IsLoggedIn() ? TEXT("Select or create a character first") : TEXT("Log in first"));
		Complete(Done, false, LastError);
		return;
	}

	const EBytesClientState PreviousState = State;
	SetState(EBytesClientState::Joining);

	const TSharedPtr<FJsonObject> Body = MakeBody();
	Body->SetStringField(TEXT("characterId"), Character->CharacterId);
	Body->SetStringField(TEXT("districtId"), DistrictId);
	if (!InstanceId.IsEmpty())
	{
		Body->SetStringField(TEXT("instanceId"), InstanceId);
	}

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/districts/join"), Body, AuthHeaders(),
		[WeakThis, Done, PreviousState](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			This->LastJoinStatus = Result.Status;
			FBytesJoinTicket Ticket;
			if (!Result.bOk || !Result.Parse(Ticket))
			{
				This->SetError(Result.Error, Result.Reasons);
				This->SetState(PreviousState);
				Complete(Done, false, Result.Describe());
				return;
			}

			This->CurrentTicket = Ticket;
			This->ClearError();
			UE_LOG(LogBytes, Display, TEXT("Joining %s at %s"), *Ticket.DisplayName, *Ticket.Address);
			// Leaving the current district (if any) is implicit: travelling disconnects from it.
			This->TravelTo(FString::Printf(TEXT("%s?ticket=%s"), *Ticket.Address, *Ticket.Ticket));
			Complete(Done, true, FString());
		});
}

void UBytesAccountSubsystem::ReturnToFrontend()
{
	CurrentTicket = FBytesJoinTicket();
	SetState(IsLoggedIn() ? EBytesClientState::CharacterSelect : EBytesClientState::LoggedOut);
	TravelTo(UBytesSettings::Get()->FrontendMap);
}

void UBytesAccountSubsystem::DevSetStats(int32 Rank, const FString& Threat, FBytesDone Done)
{
	const FBytesCharacter* Character = GetSelectedCharacterPtr();
	if (!Character)
	{
		Complete(Done, false, TEXT("No character selected"));
		return;
	}

	const TSharedPtr<FJsonObject> Body = MakeBody();
	Body->SetStringField(TEXT("characterId"), Character->CharacterId);
	if (Rank > 0)
	{
		Body->SetNumberField(TEXT("rank"), Rank);
	}
	if (!Threat.IsEmpty())
	{
		Body->SetStringField(TEXT("threat"), Threat);
	}

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/dev/characters/set"), Body, AuthHeaders(),
		[WeakThis, Done](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			FBytesCharacterResponse Response;
			if (!Result.bOk || !Result.Parse(Response))
			{
				This->SetError(Result.Error, Result.Reasons);
				Complete(Done, false, Result.Describe());
				return;
			}
			if (FBytesCharacter* Existing = This->Characters.FindByPredicate(
				[&Response](const FBytesCharacter& C) { return C.CharacterId == Response.Character.CharacterId; }))
			{
				*Existing = Response.Character;
			}
			This->Broadcast();
			This->RefreshDistricts();
			Complete(Done, true, FString());
		});
}

// ---- Blueprint wrappers -------------------------------------------------------------------------

void UBytesAccountSubsystem::K2_Register(const FString& Username, const FString& Password, FBytesOnResult OnComplete)
{
	Register(Username, Password, Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_Login(const FString& Username, const FString& Password, FBytesOnResult OnComplete)
{
	Login(Username, Password, Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_RefreshCharacters(FBytesOnResult OnComplete)
{
	RefreshCharacters(Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_CreateCharacter(const FString& Name, EBytesFaction Faction, const FString& Appearance, FBytesOnResult OnComplete)
{
	CreateCharacter(Name, Faction, Appearance, Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_DeleteCharacter(const FString& CharacterId, FBytesOnResult OnComplete)
{
	DeleteCharacter(CharacterId, Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_RefreshDistricts(FBytesOnResult OnComplete)
{
	RefreshDistricts(Wrap(OnComplete));
}

void UBytesAccountSubsystem::K2_JoinDistrict(const FString& DistrictId, const FString& InstanceId, FBytesOnResult OnComplete)
{
	JoinDistrict(DistrictId, InstanceId, Wrap(OnComplete));
}

// ---- Internals ----------------------------------------------------------------------------------

TMap<FString, FString> UBytesAccountSubsystem::AuthHeaders() const
{
	TMap<FString, FString> Headers;
	if (!SessionToken.IsEmpty())
	{
		Headers.Add(TEXT("Authorization"), TEXT("Bearer ") + SessionToken);
	}
	return Headers;
}

void UBytesAccountSubsystem::SetState(EBytesClientState NewState)
{
	if (State != NewState)
	{
		State = NewState;
		Broadcast();
	}
}

void UBytesAccountSubsystem::SetError(const FString& Error, const TArray<FString>& Reasons)
{
	LastError = Error;
	LastErrorReasons = Reasons;
	UE_LOG(LogBytes, Warning, TEXT("%s%s%s"), *Error, Reasons.Num() > 0 ? TEXT(": ") : TEXT(""), *FString::Join(Reasons, TEXT("; ")));
	Broadcast();
}

void UBytesAccountSubsystem::ClearError()
{
	LastError.Reset();
	LastErrorReasons.Reset();
}

void UBytesAccountSubsystem::Broadcast()
{
	OnStateChanged.Broadcast();
}

void UBytesAccountSubsystem::TravelTo(const FString& Url)
{
	UGameInstance* GameInstance = GetGameInstance();
	UWorld* World = GameInstance ? GameInstance->GetWorld() : nullptr;
	if (!World)
	{
		SetError(TEXT("No world to travel from"));
		return;
	}
	if (APlayerController* PC = GameInstance->GetFirstLocalPlayerController(World))
	{
		PC->ClientTravel(Url, TRAVEL_Absolute);
	}
	else if (GEngine)
	{
		GEngine->SetClientTravel(World, *Url, TRAVEL_Absolute);
	}
}

void UBytesAccountSubsystem::NotifyKicked(const FString& Reason)
{
	SetError(FString::Printf(TEXT("Removed from district: %s"), *Reason));
}

bool UBytesAccountSubsystem::IsOurWorld(const UWorld* World) const
{
	// Engine delegates are global; in multi-client PIE, only react to our own game instance.
	return World == nullptr || World->GetGameInstance() == GetGameInstance();
}

void UBytesAccountSubsystem::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	if (!IsOurWorld(World))
	{
		return;
	}
	// Don't overwrite a more specific kick reason we already received.
	if (LastError.IsEmpty() || State == EBytesClientState::Joining)
	{
		SetError(ErrorString.IsEmpty() ? FString(ENetworkFailure::ToString(FailureType)) : ErrorString);
	}
}

void UBytesAccountSubsystem::HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString)
{
	if (IsOurWorld(World))
	{
		SetError(FString::Printf(TEXT("%s %s"), ETravelFailure::ToString(FailureType), *ErrorString));
	}
}

void UBytesAccountSubsystem::HandlePostLoadMap(UWorld* World)
{
	if (!World || !IsOurWorld(World))
	{
		return;
	}
	if (World->GetNetMode() == NM_Client)
	{
		SetState(EBytesClientState::InDistrict);
		ClearError();
		Broadcast();
		return;
	}

	// Back on a local map: frontend / character select.
	if (State == EBytesClientState::InDistrict || State == EBytesClientState::Joining)
	{
		CurrentTicket = FBytesJoinTicket();
		SetState(IsLoggedIn() ? EBytesClientState::CharacterSelect : EBytesClientState::LoggedOut);
	}
	if (IsLoggedIn())
	{
		RefreshCharacters(); // rank/money may have changed while we were in the district
	}
}

// ---- Command-line auto login (playtest clients) -------------------------------------------------

void UBytesAccountSubsystem::RunAutoLoginFromCommandLine()
{
	if (GIsEditor)
	{
		return; // PIE instances share the editor command line; use the console commands there instead.
	}

	const TCHAR* CmdLine = FCommandLine::Get();
	FString User;
	if (!FParse::Value(CmdLine, TEXT("BytesUser="), User) || User.IsEmpty())
	{
		return;
	}
	FString Pass = TEXT("playtest");
	FString CharacterName = User;
	FString FactionName;
	FString DistrictId;
	FParse::Value(CmdLine, TEXT("BytesPass="), Pass);
	FParse::Value(CmdLine, TEXT("BytesCharacter="), CharacterName);
	FParse::Value(CmdLine, TEXT("BytesFaction="), FactionName);
	FParse::Value(CmdLine, TEXT("BytesDistrict="), DistrictId);
	const bool bAutoRegister = FParse::Param(CmdLine, TEXT("BytesAutoRegister"));

	EBytesFaction Faction = EBytesFaction::Enforcer;
	BytesEnums::FromString(FactionName, Faction);

	UE_LOG(LogBytes, Display, TEXT("Auto login: user=%s character=%s district=%s"), *User, *CharacterName,
		DistrictId.IsEmpty() ? TEXT("(none)") : *DistrictId);

	TWeakObjectPtr<ThisClass> WeakThis(this);

	const FBytesDone AfterLogin = [WeakThis, CharacterName, Faction, DistrictId](bool bSuccess, const FString&)
	{
		ThisClass* This = WeakThis.Get();
		if (!This || !bSuccess)
		{
			return;
		}
		const auto JoinIfRequested = [WeakThis, DistrictId](bool bReady, const FString&)
		{
			if (ThisClass* Self = WeakThis.Get(); Self && bReady && !DistrictId.IsEmpty())
			{
				Self->AutoJoin(DistrictId, 40);
			}
		};
		if (This->SelectCharacter(CharacterName))
		{
			JoinIfRequested(true, FString());
		}
		else
		{
			This->CreateCharacter(CharacterName, Faction, FString(), JoinIfRequested);
		}
	};

	Login(User, Pass, [WeakThis, User, Pass, bAutoRegister, AfterLogin](bool bSuccess, const FString& Error)
	{
		ThisClass* This = WeakThis.Get();
		if (!This)
		{
			return;
		}
		if (bSuccess || !bAutoRegister)
		{
			AfterLogin(bSuccess, Error);
			return;
		}
		This->Register(User, Pass, [WeakThis, User, Pass, AfterLogin](bool, const FString&)
		{
			if (ThisClass* Self = WeakThis.Get())
			{
				Self->Login(User, Pass, AfterLogin);
			}
		});
	});
}

void UBytesAccountSubsystem::AutoJoin(const FString& DistrictId, int32 AttemptsLeft)
{
	TWeakObjectPtr<ThisClass> WeakThis(this);
	JoinDistrict(DistrictId, FString(), [WeakThis, DistrictId, AttemptsLeft](bool bSuccess, const FString& Error)
	{
		ThisClass* This = WeakThis.Get();
		// 503 = no server for that district yet (they take a while to boot when launched together). Keep trying.
		if (!This || bSuccess || This->LastJoinStatus != 503 || AttemptsLeft <= 1)
		{
			return;
		}
		UE_LOG(LogBytes, Display, TEXT("Waiting for a %s server... (%s)"), *DistrictId, *Error);
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(This, [WeakThis, DistrictId, AttemptsLeft](float)
		{
			if (ThisClass* Self = WeakThis.Get())
			{
				Self->AutoJoin(DistrictId, AttemptsLeft - 1);
			}
			return false;
		}), 3.f);
	});
}
