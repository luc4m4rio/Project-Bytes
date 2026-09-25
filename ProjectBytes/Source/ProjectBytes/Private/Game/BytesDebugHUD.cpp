#include "Game/BytesDebugHUD.h"
#include "Client/BytesAccountSubsystem.h"
#include "Core/BytesSettings.h"
#include "Game/BytesPlayerState.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "HAL/IConsoleManager.h"

static TAutoConsoleVariable<int32> CVarBytesHUD(
	TEXT("bytes.HUD"), 1, TEXT("Show the Project Bytes debug HUD (0/1)."));

namespace
{
	const FLinearColor Title(1.f, 0.78f, 0.2f);
	const FLinearColor Dim(0.6f, 0.6f, 0.6f);
	const FLinearColor Good(0.35f, 0.9f, 0.4f);
	const FLinearColor Bad(1.f, 0.35f, 0.3f);

	FLinearColor FactionColor(EBytesFaction Faction)
	{
		return Faction == EBytesFaction::Enforcer ? FLinearColor(0.35f, 0.65f, 1.f) : FLinearColor(1.f, 0.45f, 0.35f);
	}

	FString ThreatTag(EBytesThreat Threat)
	{
		return FString::Printf(TEXT("[%s]"), *BytesEnums::ToString(Threat));
	}

	const TCHAR* StateName(EBytesClientState State)
	{
		switch (State)
		{
		case EBytesClientState::LoggedOut: return TEXT("Logged out");
		case EBytesClientState::LoggingIn: return TEXT("Logging in...");
		case EBytesClientState::CharacterSelect: return TEXT("Character select");
		case EBytesClientState::Joining: return TEXT("Joining district...");
		case EBytesClientState::InDistrict: return TEXT("In district");
		}
		return TEXT("?");
	}
}

void ABytesDebugHUD::Line(const FString& Text, const FLinearColor& Color, float Indent)
{
	UFont* Font = GEngine ? GEngine->GetSmallFont() : nullptr;
	DrawText(Text, Color, CursorX + Indent, CursorY, Font, 1.f);
	CursorY += 16.f;
}

void ABytesDebugHUD::DrawHUD()
{
	Super::DrawHUD();
	if (!Canvas || CVarBytesHUD.GetValueOnGameThread() == 0)
	{
		return;
	}

	CursorX = 32.f;
	CursorY = 32.f;
	UGameInstance* GameInstance = GetGameInstance();
	UBytesAccountSubsystem* Account = GameInstance ? GameInstance->GetSubsystem<UBytesAccountSubsystem>() : nullptr;

	Line(TEXT("PROJECT BYTES"), Title);
	if (GetNetMode() == NM_Client || GetNetMode() == NM_ListenServer)
	{
		DrawDistrict(Account);
	}
	else if (Account)
	{
		DrawFrontend(Account);
	}

	if (Account && !Account->GetLastError().IsEmpty())
	{
		CursorY += 8.f;
		Line(Account->GetLastError(), Bad);
		for (const FString& Reason : Account->GetLastErrorReasons())
		{
			Line(TEXT("- ") + Reason, Bad, 16.f);
		}
	}
}

void ABytesDebugHUD::DrawFrontend(UBytesAccountSubsystem* Account)
{
	Line(FString::Printf(TEXT("Backend %s  |  %s"), *UBytesSettings::GetBackendUrl(), StateName(Account->GetState())), Dim);
	CursorY += 8.f;

	if (!Account->IsLoggedIn())
	{
		Line(TEXT("Open the console (~) and type:"));
		Line(TEXT("bytes.Register <user> <password>     then     bytes.Login <user> <password>"), Dim, 16.f);
		return;
	}

	const FBytesAccount AccountInfo = Account->GetAccount();
	Line(FString::Printf(TEXT("Account: %s%s"), *AccountInfo.Username,
		AccountInfo.Flags.Num() > 0 ? *FString::Printf(TEXT("  flags: %s"), *FString::Join(AccountInfo.Flags, TEXT(", "))) : TEXT("")));

	const TArray<FBytesCharacter>& Characters = Account->GetCharactersRef();
	const FBytesCharacter* Selected = Account->GetSelectedCharacterPtr();
	Line(FString::Printf(TEXT("Characters (%d/%d)"), Characters.Num(), AccountInfo.MaxCharacters), Title);
	if (Characters.Num() == 0)
	{
		Line(TEXT("none yet: bytes.CreateCharacter <name> <Enforcer|Criminal>"), Dim, 16.f);
	}
	for (const FBytesCharacter& Character : Characters)
	{
		const bool bSelected = Selected && Selected->CharacterId == Character.CharacterId;
		Line(FString::Printf(TEXT("%s %-16s %-9s rank %-3d %-8s $%d%s"),
			bSelected ? TEXT(">") : TEXT(" "), *Character.Name, *BytesEnums::ToString(Character.Faction), Character.Rank,
			*ThreatTag(Character.Threat), Character.Money,
			Character.OnlineInstance.IsEmpty() ? TEXT("") : *FString::Printf(TEXT("  (online: %s)"), *Character.OnlineInstance)),
			FactionColor(Character.Faction), 16.f);
	}

	CursorY += 8.f;
	Line(TEXT("Districts"), Title);
	for (const FBytesDistrict& District : Account->GetDistrictsRef())
	{
		TArray<FString> InstanceText;
		for (const FBytesDistrictInstance& Instance : District.Instances)
		{
			InstanceText.Add(FString::Printf(TEXT("%s %d/%d"), *Instance.DisplayName, Instance.Population, Instance.MaxPlayers));
		}
		const FString Instances = InstanceText.Num() > 0 ? FString::Join(InstanceText, TEXT(", ")) : TEXT("no servers");
		Line(FString::Printf(TEXT("%s %-20s %-40s %-24s %s"), District.IsEligible() ? TEXT("[ok]") : TEXT("[--]"),
			*District.DistrictId, *District.DisplayName, *District.Requirements.Describe(), *Instances),
			District.IsEligible() ? (District.Instances.Num() > 0 ? Good : Dim) : Bad, 16.f);
		for (const FString& Reason : District.IneligibleReasons)
		{
			Line(Reason, Bad, 64.f);
		}
	}

	CursorY += 8.f;
	Line(TEXT("bytes.Join <district> [instance]   bytes.Select <name>   bytes.Districts   bytes.Dev.SetRank 80   bytes.Dev.SetThreat Silver"), Dim);
}

void ABytesDebugHUD::DrawDistrict(UBytesAccountSubsystem* Account)
{
	const FBytesJoinTicket District = Account ? Account->GetCurrentDistrict() : FBytesJoinTicket();
	Line(District.DisplayName.IsEmpty() ? TEXT("Connected (offline dev server)")
		: FString::Printf(TEXT("%s  (%s)"), *District.DisplayName, *District.Address), Dim);

	const AGameStateBase* GameState = GetWorld() ? GetWorld()->GetGameState() : nullptr;
	const APlayerState* OwnState = PlayerOwner ? PlayerOwner->PlayerState.Get() : nullptr;
	if (const ABytesPlayerState* Own = Cast<ABytesPlayerState>(OwnState))
	{
		Line(FString::Printf(TEXT("You: %s  standing %d  $%d"), *Own->GetIdentity().Name, Own->Standing, Own->Money));
	}

	CursorY += 8.f;
	Line(FString::Printf(TEXT("Players (%d)"), GameState ? GameState->PlayerArray.Num() : 0), Title);
	if (GameState)
	{
		for (const APlayerState* PS : GameState->PlayerArray)
		{
			const ABytesPlayerState* BytesPS = Cast<ABytesPlayerState>(PS);
			if (!BytesPS)
			{
				continue;
			}
			const FBytesPublicIdentity& Id = BytesPS->GetIdentity();
			Line(FString::Printf(TEXT("%s %-16s %-9s rank %-3d %s%s"), PS == OwnState ? TEXT(">") : TEXT(" "), *Id.Name,
				*BytesEnums::ToString(Id.Faction), Id.Rank, *ThreatTag(Id.Threat),
				Id.Clan.IsEmpty() ? TEXT("") : *FString::Printf(TEXT("  <%s>"), *Id.Clan)),
				FactionColor(Id.Faction), 16.f);
		}
	}

	CursorY += 8.f;
	Line(TEXT("bytes.Leave   bytes.Join <district>   bytes.Dev.AwardStanding 5000   bytes.Dev.ServerThreat Gold"), Dim);
}
