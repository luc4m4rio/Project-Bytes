// bytes.* console commands: drive the whole account/character/district flow without any UI.

#include "Client/BytesAccountSubsystem.h"
#include "Core/BytesSettings.h"
#include "Game/BytesCharacter.h"
#include "Game/BytesPlayerController.h"
#include "ProjectBytes.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "HAL/IConsoleManager.h"

namespace BytesConsole
{
	UBytesAccountSubsystem* GetAccount(UWorld* World)
	{
		UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
		UBytesAccountSubsystem* Account = GameInstance ? GameInstance->GetSubsystem<UBytesAccountSubsystem>() : nullptr;
		if (!Account)
		{
			UE_LOG(LogBytes, Warning, TEXT("bytes.*: no account subsystem here (dedicated server?)"));
		}
		return Account;
	}

	FBytesDone Report(const FString& What)
	{
		return [What](bool bSuccess, const FString& Error)
		{
			if (bSuccess)
			{
				UE_LOG(LogBytes, Display, TEXT("%s: ok"), *What);
			}
			else
			{
				UE_LOG(LogBytes, Warning, TEXT("%s failed: %s"), *What, *Error);
			}
		};
	}

	bool NeedArgs(const TArray<FString>& Args, int32 Count, const TCHAR* Usage)
	{
		if (Args.Num() < Count)
		{
			UE_LOG(LogBytes, Warning, TEXT("Usage: %s"), Usage);
			return false;
		}
		return true;
	}

	void PrintCharacters(UBytesAccountSubsystem* Account)
	{
		const FBytesCharacter* Selected = Account->GetSelectedCharacterPtr();
		for (const FBytesCharacter& C : Account->GetCharactersRef())
		{
			UE_LOG(LogBytes, Display, TEXT("%s %s  %s  rank %d  %s  $%d  (%s)"), Selected && Selected->CharacterId == C.CharacterId ? TEXT(">") : TEXT(" "),
				*C.Name, *BytesEnums::ToString(C.Faction), C.Rank, *BytesEnums::ToString(C.Threat), C.Money, *C.CharacterId);
		}
	}

	void PrintDistricts(UBytesAccountSubsystem* Account)
	{
		for (const FBytesDistrict& D : Account->GetDistrictsRef())
		{
			UE_LOG(LogBytes, Display, TEXT("%s %s - %s [%s] %d instance(s)%s%s"), D.IsEligible() ? TEXT("[ok]") : TEXT("[--]"), *D.DistrictId,
				*D.DisplayName, *D.Requirements.Describe(), D.Instances.Num(), D.IsEligible() ? TEXT("") : TEXT(": "),
				*FString::Join(D.IneligibleReasons, TEXT("; ")));
		}
	}

	ABytesPlayerController* GetLocalController(UWorld* World)
	{
		UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
		ABytesPlayerController* PC = GameInstance ? Cast<ABytesPlayerController>(GameInstance->GetFirstLocalPlayerController(World)) : nullptr;
		if (!PC)
		{
			UE_LOG(LogBytes, Warning, TEXT("Not in a district"));
		}
		return PC;
	}

	using FHandler = void (*)(const TArray<FString>&, UWorld*);

	struct FCommand
	{
		FCommand(const TCHAR* Name, const TCHAR* Help, FHandler Handler)
			: Command(Name, Help, FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(Handler))
		{
		}
		FAutoConsoleCommandWithWorldAndArgs Command;
	};

	FCommand CmdRegister(TEXT("bytes.Register"), TEXT("bytes.Register <user> <password> - create an account"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 2, TEXT("bytes.Register <user> <password>")))
			{
				Account->Register(Args[0], Args[1], Report(TEXT("Register")));
			}
		});

	FCommand CmdLogin(TEXT("bytes.Login"), TEXT("bytes.Login <user> <password>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 2, TEXT("bytes.Login <user> <password>")))
			{
				Account->Login(Args[0], Args[1], Report(TEXT("Login")));
			}
		});

	FCommand CmdLogout(TEXT("bytes.Logout"), TEXT("Log out (and leave the district)"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World))
			{
				Account->Logout();
			}
		});

	FCommand CmdCharacters(TEXT("bytes.Characters"), TEXT("List this account's characters"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World))
			{
				TWeakObjectPtr<UBytesAccountSubsystem> Weak(Account);
				Account->RefreshCharacters([Weak](bool bSuccess, const FString& Error)
				{
					if (UBytesAccountSubsystem* Self = Weak.Get(); Self && bSuccess)
					{
						PrintCharacters(Self);
					}
				});
			}
		});

	FCommand CmdCreateCharacter(TEXT("bytes.CreateCharacter"), TEXT("bytes.CreateCharacter <name> <Enforcer|Criminal>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesAccountSubsystem* Account = GetAccount(World);
			EBytesFaction Faction = EBytesFaction::Enforcer;
			if (Account && NeedArgs(Args, 2, TEXT("bytes.CreateCharacter <name> <Enforcer|Criminal>")))
			{
				if (!BytesEnums::FromString(Args[1], Faction))
				{
					UE_LOG(LogBytes, Warning, TEXT("Faction must be Enforcer or Criminal"));
					return;
				}
				Account->CreateCharacter(Args[0], Faction, FString(), Report(TEXT("CreateCharacter")));
			}
		});

	FCommand CmdDeleteCharacter(TEXT("bytes.DeleteCharacter"), TEXT("bytes.DeleteCharacter <name>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 1, TEXT("bytes.DeleteCharacter <name>")))
			{
				Account->DeleteCharacter(Args[0], Report(TEXT("DeleteCharacter")));
			}
		});

	FCommand CmdSelect(TEXT("bytes.Select"), TEXT("bytes.Select <name> - pick the character to play"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 1, TEXT("bytes.Select <name>")))
			{
				if (!Account->SelectCharacter(Args[0]))
				{
					UE_LOG(LogBytes, Warning, TEXT("No character '%s' on this account"), *Args[0]);
				}
			}
		});

	FCommand CmdDistricts(TEXT("bytes.Districts"), TEXT("List districts and whether the selected character may enter"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World))
			{
				TWeakObjectPtr<UBytesAccountSubsystem> Weak(Account);
				Account->RefreshDistricts([Weak](bool bSuccess, const FString&)
				{
					if (UBytesAccountSubsystem* Self = Weak.Get(); Self && bSuccess)
					{
						PrintDistricts(Self);
					}
				});
			}
		});

	FCommand CmdJoin(TEXT("bytes.Join"), TEXT("bytes.Join <district> [instance] - e.g. bytes.Join financial"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 1, TEXT("bytes.Join <district> [instance]")))
			{
				Account->JoinDistrict(Args[0], Args.Num() > 1 ? Args[1] : FString(), Report(TEXT("Join")));
			}
		});

	FCommand CmdLeave(TEXT("bytes.Leave"), TEXT("Leave the district and return to character select"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World))
			{
				Account->ReturnToFrontend();
			}
		});

	FCommand CmdStatus(TEXT("bytes.Status"), TEXT("Print account, characters and districts"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World))
			{
				UE_LOG(LogBytes, Display, TEXT("Backend %s, logged in: %s (%s)"), *UBytesSettings::GetBackendUrl(),
					Account->IsLoggedIn() ? TEXT("yes") : TEXT("no"), *Account->GetAccount().Username);
				PrintCharacters(Account);
				PrintDistricts(Account);
			}
		});

	FCommand CmdDevSetRank(TEXT("bytes.Dev.SetRank"), TEXT("bytes.Dev.SetRank <rank> - backend devMode: set the selected character's rank"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 1, TEXT("bytes.Dev.SetRank <rank>")))
			{
				Account->DevSetStats(FCString::Atoi(*Args[0]), FString(), Report(TEXT("SetRank")));
			}
		});

	FCommand CmdDevSetThreat(TEXT("bytes.Dev.SetThreat"), TEXT("bytes.Dev.SetThreat <Green|Bronze|Silver|Gold> - backend devMode"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAccountSubsystem* Account = GetAccount(World); Account && NeedArgs(Args, 1, TEXT("bytes.Dev.SetThreat <Green|Bronze|Silver|Gold>")))
			{
				Account->DevSetStats(0, Args[0], Report(TEXT("SetThreat")));
			}
		});

	FCommand CmdDevAwardStanding(TEXT("bytes.Dev.AwardStanding"), TEXT("bytes.Dev.AwardStanding <standing> [money] - in a district, via the server"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (ABytesPlayerController* PC = GetLocalController(World); PC && NeedArgs(Args, 1, TEXT("bytes.Dev.AwardStanding <standing> [money]")))
			{
				PC->ServerDevAwardProgress(FCString::Atoi(*Args[0]), Args.Num() > 1 ? FCString::Atoi(*Args[1]) : 0);
			}
		});

	FCommand CmdDevServerThreat(TEXT("bytes.Dev.ServerThreat"), TEXT("bytes.Dev.ServerThreat <threat> - in a district, via the server"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			EBytesThreat Threat = EBytesThreat::Green;
			if (ABytesPlayerController* PC = GetLocalController(World); PC && NeedArgs(Args, 1, TEXT("bytes.Dev.ServerThreat <threat>")))
			{
				if (BytesEnums::FromString(Args[0], Threat))
				{
					PC->ServerDevSetThreat(Threat);
				}
			}
		});

	FCommand CmdMoveFeel(TEXT("bytes.Move.Feel"), TEXT("bytes.Move.Feel <Snappy|Responsive|Realistic> - compare movement feels live (dev)"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			ABytesPlayerController* PC = GetLocalController(World);
			ABytesCharacter* BytesCharacter = PC ? PC->GetPawn<ABytesCharacter>() : nullptr;
			if (!BytesCharacter || !NeedArgs(Args, 1, TEXT("bytes.Move.Feel <Snappy|Responsive|Realistic>")))
			{
				return;
			}
			const UEnum* Enum = StaticEnum<EBytesMovementFeel>();
			int64 Value = INDEX_NONE;
			for (int32 Index = 0; Index < Enum->NumEnums() - 1; ++Index)
			{
				if (Enum->GetNameStringByIndex(Index).Equals(Args[0], ESearchCase::IgnoreCase))
				{
					Value = Enum->GetValueByIndex(Index);
				}
			}
			if (Value == INDEX_NONE)
			{
				UE_LOG(LogBytes, Warning, TEXT("Unknown feel '%s'"), *Args[0]);
				return;
			}
			// Same numbers on both sides, or the server would correct every predicted move.
			BytesCharacter->GetBytesMovement()->ApplyFeel(static_cast<EBytesMovementFeel>(Value));
			PC->ServerDevSetMovementFeel(static_cast<uint8>(Value));
			UE_LOG(LogBytes, Display, TEXT("Movement feel: %s"), *Args[0]);
		});
}
