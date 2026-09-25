#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Core/BytesTypes.h"
#include "BytesSettings.generated.h"

class APawn;

/**
 * Project Settings > Game > Project Bytes Online.
 * Most values can be overridden per-process on the command line, which is what Tools/bytes.py does.
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Project Bytes Online"))
class PROJECTBYTES_API UBytesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Backend base URL. Command line: -BytesBackend=http://host:port */
	UPROPERTY(Config, EditAnywhere, Category = "Backend")
	FString BackendUrl = TEXT("http://127.0.0.1:8080");

	UPROPERTY(Config, EditAnywhere, Category = "Backend", meta = (ClampMin = 1))
	float RequestTimeoutSeconds = 10.f;

	/** Shared secret district servers use to talk to the backend. Command line: -BytesServerKey=... */
	UPROPERTY(Config, EditAnywhere, Category = "Server")
	FString ServerKey = TEXT("dev-server-key-change-me");

	/** Map clients return to when leaving a district (character select / frontend). */
	UPROPERTY(Config, EditAnywhere, Category = "Client")
	FString FrontendMap = TEXT("/Engine/Maps/Entry");

	/**
	 * Servers that were NOT started with -District=<id> (PIE, "open" on a listen server) accept players without a
	 * backend ticket and give them a dev identity from URL options (?BytesName=&BytesRank=&BytesThreat=&BytesFaction=).
	 * Never allowed in Shipping builds.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Offline Dev")
	bool bAllowOfflineDevLogins = true;

	/** Requirements enforced on unmanaged (offline dev) servers, to test gating in PIE without the backend. */
	UPROPERTY(Config, EditAnywhere, Category = "Offline Dev")
	FBytesDistrictRequirements OfflineRequirements;

	/**
	 * Pawn players get in districts. Empty = the engine's fly-around DefaultPawn. Set it to a Blueprint child of
	 * BytesCharacter (with your mesh + motion matching AnimBP) to play on foot.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Gameplay", meta = (AllowAbstract = "false"))
	TSoftClassPtr<APawn> DistrictPawnClass;

	/**
	 * On the empty /Engine/Maps/Entry dev map, spawn a lit floor, landmarks and player starts locally on every
	 * machine so movement can be playtested before real district maps exist.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Gameplay")
	bool bSpawnTestFloorOnEntryMap = true;

	virtual FName GetCategoryName() const override { return TEXT("Game"); }

	static const UBytesSettings* Get() { return GetDefault<UBytesSettings>(); }

	/** BackendUrl with command-line override applied, without trailing slash. */
	static FString GetBackendUrl();
	static FString GetServerKey();
};
