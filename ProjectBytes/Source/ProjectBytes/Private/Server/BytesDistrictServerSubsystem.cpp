#include "Server/BytesDistrictServerSubsystem.h"
#include "Core/BytesBackendHttp.h"
#include "Core/BytesSettings.h"
#include "Core/BytesTicket.h"
#include "ProjectBytes.h"
#include "Engine/GameInstance.h"
#include "Engine/NetDriver.h"
#include "Engine/World.h"
#include "HAL/PlatformTime.h"
#include "Misc/App.h"
#include "Misc/Base64.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

void UBytesDistrictServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const TCHAR* CmdLine = FCommandLine::Get();
	if (!FParse::Value(CmdLine, TEXT("District="), DistrictId) || DistrictId.IsEmpty())
	{
		return; // unmanaged: PIE / ad-hoc server
	}
	FParse::Value(CmdLine, TEXT("BytesPublicHost="), PublicHost);
	FParse::Value(CmdLine, TEXT("BytesRegion="), Region);
	FParse::Value(CmdLine, TEXT("BytesMaxPlayers="), RequestedMaxPlayers);
	FParse::Value(CmdLine, TEXT("port="), CommandLinePort);

	UE_LOG(LogBytes, Display, TEXT("Managed district server for '%s', backend %s"), *DistrictId, *UBytesSettings::GetBackendUrl());
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &ThisClass::Tick), 0.5f);
}

void UBytesDistrictServerSubsystem::Deinitialize()
{
	if (TickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
	}
	Unregister();
	Super::Deinitialize();
}

FBytesDistrictRequirements UBytesDistrictServerSubsystem::GetRequirements() const
{
	return IsManaged() ? Requirements : UBytesSettings::Get()->OfflineRequirements;
}

bool UBytesDistrictServerSubsystem::VerifyTicket(const FString& Ticket, FBytesTicketClaims& OutClaims, FString& OutError) const
{
	if (!BytesTicket::Verify(Ticket, TicketKey, OutClaims, OutError))
	{
		return false;
	}
	if (OutClaims.ServerId != ServerId)
	{
		OutError = TEXT("Ticket was issued for a different district server");
		return false;
	}
	return true;
}

// ---- Registration / heartbeat -------------------------------------------------------------------

bool UBytesDistrictServerSubsystem::Tick(float DeltaTime)
{
	const double Now = FPlatformTime::Seconds();
	if (!IsRegistered())
	{
		int32 ListenPort = 0;
		// Only advertise ourselves once clients can actually connect.
		if (!bRegisterInFlight && Now >= NextRegisterAttempt && TryGetListenPort(ListenPort))
		{
			Register(ListenPort);
		}
		return true;
	}

	if (Now - LastHeartbeat >= HeartbeatSeconds || (bPresenceDirty && Now - LastHeartbeat >= 1.0))
	{
		SendHeartbeat();
	}
	return true;
}

bool UBytesDistrictServerSubsystem::TryGetListenPort(int32& OutPort) const
{
	const UGameInstance* GameInstance = GetGameInstance();
	const UWorld* World = GameInstance ? GameInstance->GetWorld() : nullptr;
	UNetDriver* NetDriver = World ? World->GetNetDriver() : nullptr;
	if (!NetDriver)
	{
		return false;
	}
	// "0.0.0.0:7777" - the port actually bound, which can differ from -port= if it was taken.
	const FString Local = NetDriver->LowLevelGetNetworkNumber();
	FString Unused;
	FString PortText;
	if (Local.Split(TEXT(":"), &Unused, &PortText, ESearchCase::IgnoreCase, ESearchDir::FromEnd) && PortText.IsNumeric())
	{
		OutPort = FCString::Atoi(*PortText);
	}
	else
	{
		OutPort = CommandLinePort;
	}
	return true;
}

void UBytesDistrictServerSubsystem::Register(int32 ListenPort)
{
	bRegisterInFlight = true;

	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("districtId"), DistrictId);
	Body->SetStringField(TEXT("host"), PublicHost);
	Body->SetNumberField(TEXT("port"), ListenPort);
	Body->SetStringField(TEXT("region"), Region);
	Body->SetStringField(TEXT("build"), FApp::GetBuildVersion());
	if (RequestedMaxPlayers > 0)
	{
		Body->SetNumberField(TEXT("maxPlayers"), RequestedMaxPlayers);
	}

	TWeakObjectPtr<ThisClass> WeakThis(this);
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/servers/register"), Body, ServerHeaders(),
		[WeakThis, ListenPort](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (!This)
			{
				return;
			}
			This->bRegisterInFlight = false;

			FBytesServerRegisterResponse Response;
			TArray<uint8> Key;
			if (!Result.bOk || !Result.Parse(Response) || !FBase64::Decode(Response.TicketKey, Key))
			{
				UE_LOG(LogBytes, Warning, TEXT("District registration failed (%s), retrying in 5s"), *Result.Describe());
				This->NextRegisterAttempt = FPlatformTime::Seconds() + 5.0;
				return;
			}

			This->ServerId = Response.ServerId;
			This->InstanceId = Response.InstanceId;
			This->DisplayName = Response.DisplayName;
			This->MaxPlayers = Response.MaxPlayers;
			This->Requirements = Response.Requirements;
			This->TicketKey = MoveTemp(Key);
			This->HeartbeatSeconds = FMath::Max(1, Response.HeartbeatSeconds);
			This->bPresenceDirty = true; // re-announce anyone already here (backend restarted)
			This->LastHeartbeat = 0.0;
			UE_LOG(LogBytes, Display, TEXT("Registered as %s (%s) on port %d, max %d players, requirements: %s"),
				*This->DisplayName, *This->InstanceId, ListenPort, This->MaxPlayers, *This->Requirements.Describe());
		});
}

void UBytesDistrictServerSubsystem::SendHeartbeat()
{
	LastHeartbeat = FPlatformTime::Seconds();
	bPresenceDirty = false;

	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("serverId"), ServerId);
	TArray<TSharedPtr<FJsonValue>> Ids;
	for (const FString& CharacterId : OnlineCharacters)
	{
		Ids.Add(MakeShared<FJsonValueString>(CharacterId));
	}
	Body->SetArrayField(TEXT("characterIds"), Ids);

	TWeakObjectPtr<ThisClass> WeakThis(this);
	const FString SentServerId = ServerId;
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/servers/heartbeat"), Body, ServerHeaders(),
		[WeakThis, SentServerId](const FBytesHttpResult& Result)
		{
			ThisClass* This = WeakThis.Get();
			if (This && Result.Status == 404 && This->ServerId == SentServerId)
			{
				UE_LOG(LogBytes, Warning, TEXT("Backend no longer knows this server (restarted?), registering again"));
				This->ServerId.Reset();
			}
		});
}

void UBytesDistrictServerSubsystem::Unregister()
{
	if (!IsRegistered())
	{
		return;
	}
	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("serverId"), ServerId);
	// Best effort during shutdown; the backend also drops servers that stop heartbeating.
	BytesHttp::Send(TEXT("POST"), TEXT("/v1/servers/unregister"), Body, ServerHeaders(), nullptr);
	ServerId.Reset();
}

TMap<FString, FString> UBytesDistrictServerSubsystem::ServerHeaders() const
{
	TMap<FString, FString> Headers;
	Headers.Add(TEXT("X-Bytes-Server-Key"), UBytesSettings::GetServerKey());
	return Headers;
}

// ---- Players ------------------------------------------------------------------------------------

void UBytesDistrictServerSubsystem::RedeemTicket(const FString& TicketId, const FString& CharacterId,
	TFunction<void(const FBytesHttpResult& Result, const FBytesRedeemResponse& Response)> Done)
{
	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("serverId"), ServerId);
	Body->SetStringField(TEXT("ticketId"), TicketId);
	Body->SetStringField(TEXT("characterId"), CharacterId);

	BytesHttp::Send(TEXT("POST"), TEXT("/v1/servers/redeem"), Body, ServerHeaders(),
		[Done](const FBytesHttpResult& Result)
		{
			FBytesRedeemResponse Response;
			FBytesHttpResult Checked = Result;
			if (Checked.bOk && !Checked.Parse(Response))
			{
				Checked.bOk = false;
				Checked.Error = TEXT("Unexpected redeem response");
			}
			if (Done)
			{
				Done(Checked, Response);
			}
		});
}

void UBytesDistrictServerSubsystem::ReportProgress(const FString& CharacterId, int32 StandingDelta, int32 MoneyDelta,
	const FString& Threat, TFunction<void(bool bSuccess, const FBytesCharacter& Character)> Done)
{
	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("serverId"), ServerId);
	Body->SetStringField(TEXT("characterId"), CharacterId);
	Body->SetNumberField(TEXT("standingDelta"), StandingDelta);
	Body->SetNumberField(TEXT("moneyDelta"), MoneyDelta);
	if (!Threat.IsEmpty())
	{
		Body->SetStringField(TEXT("threat"), Threat);
	}

	BytesHttp::Send(TEXT("POST"), TEXT("/v1/servers/characters/update"), Body, ServerHeaders(),
		[Done, CharacterId](const FBytesHttpResult& Result)
		{
			FBytesCharacterResponse Response;
			const bool bSuccess = Result.bOk && Result.Parse(Response);
			if (!bSuccess)
			{
				UE_LOG(LogBytes, Warning, TEXT("Failed to save progress for %s: %s"), *CharacterId, *Result.Describe());
			}
			if (Done)
			{
				Done(bSuccess, Response.Character);
			}
		});
}

void UBytesDistrictServerSubsystem::AddOnlineCharacter(const FString& CharacterId)
{
	OnlineCharacters.Add(CharacterId);
	bPresenceDirty = true;
}

void UBytesDistrictServerSubsystem::RemoveOnlineCharacter(const FString& CharacterId)
{
	OnlineCharacters.Remove(CharacterId);
	bPresenceDirty = true;
}
