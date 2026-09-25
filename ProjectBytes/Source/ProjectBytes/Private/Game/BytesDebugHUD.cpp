#include "Game/BytesDebugHUD.h"
#include "Appearance/BytesAppearanceSubsystem.h"
#include "Appearance/BytesCharacterCreator.h"
#include "Client/BytesAccountSubsystem.h"
#include "Core/BytesSettings.h"
#include "Game/BytesCharacter.h"
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
	else if (UBytesAppearanceSubsystem* Appearance = UBytesAppearanceSubsystem::Get(this); Appearance && Appearance->GetActiveCreator())
	{
		DrawCreator(Appearance->GetActiveCreator());
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
		Line(TEXT("none yet: bytes.Creator.New, or quick: bytes.CreateCharacter <name> <Enforcer|Criminal>"), Dim, 16.f);
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
	Line(TEXT("bytes.Creator.New [male|female] [Enforcer|Criminal]   bytes.Creator.Edit <name>   (character creator)"), Dim);
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
	if (const ABytesCharacter* Body = PlayerOwner ? PlayerOwner->GetPawn<ABytesCharacter>() : nullptr)
	{
		const UBytesCharacterMovementComponent* Movement = Body->GetBytesMovement();
		Line(FString::Printf(TEXT("Movement: %s  %s%s  %.0f cm/s  (feel: %s)"), *StaticEnum<EBytesGait>()->GetNameStringByValue(static_cast<int64>(Body->GetGait())),
			Body->IsAiming() ? TEXT("aiming") : TEXT("free"), Movement->IsCrouching() ? TEXT(" crouched") : TEXT(""), Body->GetVelocity().Size2D(),
			*StaticEnum<EBytesMovementFeel>()->GetNameStringByValue(static_cast<int64>(Movement->GetFeel()))), Dim);
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
	Line(TEXT("bytes.Move.Feel Snappy|Responsive|Realistic   bytes.Anim.DebugTrajectory 1   bytes.HUD 0"), Dim);
}

void ABytesDebugHUD::DrawCreator(UBytesCharacterCreator* Creator)
{
	const FBytesAppearance& Look = Creator->GetAppearanceRef();
	Line(FString::Printf(TEXT("CHARACTER CREATOR  -  %s  %s  %s  (rank %d unlocks)"), Creator->IsEditingExisting() ? TEXT("editing") : TEXT("new"),
		*Look.Body, *BytesEnums::ToString(Creator->GetFaction()), Creator->GetRank()), Title);

	TArray<FString> Morphs;
	for (const TPair<FString, float>& Pair : Look.Morphs)
	{
		if (!FMath::IsNearlyZero(Pair.Value))
		{
			Morphs.Add(FString::Printf(TEXT("%s %+.2f"), *Pair.Key, Pair.Value));
		}
	}
	Line(FString::Printf(TEXT("Morphs: %s"), Morphs.Num() > 0 ? *FString::Join(Morphs, TEXT(", ")) : TEXT("all default")), FLinearColor::White, 16.f);

	TArray<FString> Colors;
	for (const TPair<FString, FString>& Pair : Look.Colors)
	{
		Colors.Add(FString::Printf(TEXT("%s %s"), *Pair.Key, *Pair.Value));
	}
	Line(FString::Printf(TEXT("Colours: %s"), Colors.Num() > 0 ? *FString::Join(Colors, TEXT(", ")) : TEXT("defaults")), FLinearColor::White, 16.f);

	Line(TEXT("Outfit:"), FLinearColor::White, 16.f);
	for (const TPair<FString, FBytesAppearancePart>& Pair : Look.Parts)
	{
		Line(FString::Printf(TEXT("%-10s %-18s %s"), *Pair.Key, *Pair.Value.Id, *FString::Join(Pair.Value.Colors, TEXT(" "))), Dim, 32.f);
	}
	Line(FString::Printf(TEXT("Tattoos (%d):"), Look.Tattoos.Num()), FLinearColor::White, 16.f);
	for (int32 Index = 0; Index < Look.Tattoos.Num(); ++Index)
	{
		const FBytesTattooLayer& Layer = Look.Tattoos[Index];
		Line(FString::Printf(TEXT("%d. %-12s on %-14s at %.2f,%.2f  scale %.2f  rot %.0f  %s %.0f%%%s"), Index + 1, *Layer.Decal, *Layer.Region,
			Layer.X, Layer.Y, Layer.Scale, Layer.Rotation, *Layer.Color, Layer.Opacity * 100.f, Layer.Mirror ? TEXT("  mirrored") : TEXT("")), Dim, 32.f);
	}

	const TArray<FString> Errors = Creator->Validate();
	if (Errors.Num() > 0)
	{
		CursorY += 8.f;
		for (const FString& Error : Errors)
		{
			Line(Error, Bad, 16.f);
		}
	}

	CursorY += 8.f;
	Line(TEXT("bytes.Creator.Morph <id> <v>   .Color <id> #hex   .Part <slot> <id>   .PartColor <slot> <1-3> #hex   .Tattoo <decal> <region> [x y scale rot]"), Dim);
	Line(TEXT("bytes.Creator.TattooMirror <n>   .Randomize   .Undo/.Redo   .Focus Face|Body   .Rotate 45   .List morphs|parts <slot>|decals   .Save <name>"), Dim);
}
