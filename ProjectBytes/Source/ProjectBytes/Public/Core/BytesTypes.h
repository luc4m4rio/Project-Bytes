#pragma once

#include "CoreMinimal.h"
#include "BytesTypes.generated.h"

// Shared data model between client, district server and backend (Backend/server.py).
// Structs are (de)serialized with FJsonObjectConverter, which matches JSON keys to property names
// case-insensitively ("characterId" <-> CharacterId). Enums travel as their short names ("Silver").

UENUM(BlueprintType)
enum class EBytesFaction : uint8
{
	Enforcer,
	Criminal,
};

/** APB-style threat tiers, ordered lowest to highest. */
UENUM(BlueprintType)
enum class EBytesThreat : uint8
{
	Green,
	Bronze,
	Silver,
	Gold,
};

namespace BytesEnums
{
	PROJECTBYTES_API FString ToString(EBytesFaction Faction);
	PROJECTBYTES_API FString ToString(EBytesThreat Threat);
	PROJECTBYTES_API bool FromString(const FString& In, EBytesFaction& Out);
	PROJECTBYTES_API bool FromString(const FString& In, EBytesThreat& Out);
}

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesAccount
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString AccountId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Username;

	/** Free-form account flags (e.g. "tester", "premium") that districts can require. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	TArray<FString> Flags;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 MaxCharacters = 0;
};

/** A character owned by an account. Each character is its own identity: name, faction, progression. */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesCharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString CharacterId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesFaction Faction = EBytesFaction::Enforcer;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Rank = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Standing = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesThreat Threat = EBytesThreat::Green;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Money = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Clan;

	/** Opaque customization blob (JSON string) owned by your character creator. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Appearance;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString LastDistrict;

	/** Instance id the character is currently in, empty if offline. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString OnlineInstance;
};

/**
 * Optional entry requirements for a district. Every field defaults to "no requirement":
 * 0 for ranks, empty arrays for lists. Mirrors normalize/evaluate_requirements in Backend/server.py.
 */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesDistrictRequirements
{
	GENERATED_BODY()

	/** 0 = no minimum. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes", meta = (ClampMin = 0))
	int32 MinRank = 0;

	/** 0 = no maximum. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes", meta = (ClampMin = 0))
	int32 MaxRank = 0;

	/** Empty = any threat. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes")
	TArray<EBytesThreat> AllowedThreats;

	/** Empty = both factions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes")
	TArray<EBytesFaction> AllowedFactions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes")
	TArray<FString> RequiredAccountFlags;

	bool HasAny() const;

	/** Returns the reasons a character may not enter; empty means eligible. */
	TArray<FString> Evaluate(int32 Rank, EBytesThreat Threat, EBytesFaction Faction, const TArray<FString>& AccountFlags) const;

	/** Short summary like "Rank 80+, Silver". */
	FString Describe() const;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesDistrictInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString InstanceId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Region;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Population = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 MaxPlayers = 0;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesDistrict
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DistrictId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DisplayName;

	/** "Action", "Social", "FightClub", ... */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Type;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FBytesDistrictRequirements Requirements;

	/** Why the selected character can't join. Empty = eligible. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	TArray<FString> IneligibleReasons;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	TArray<FBytesDistrictInstance> Instances;

	bool IsEligible() const { return IneligibleReasons.Num() == 0; }
};

/** Returned by the backend when it lets a character into a district. */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesJoinTicket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DistrictId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString InstanceId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DisplayName;

	/** host:port of the district server. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Address;

	/** Signed ticket, passed to the server as ?ticket=... */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Ticket;
};

/** Signed contents of a join ticket, verified by the district server in PreLogin. */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesTicketClaims
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString TicketId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString AccountId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString CharacterId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString CharacterName;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesFaction Faction = EBytesFaction::Enforcer;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Rank = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesThreat Threat = EBytesThreat::Green;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Clan;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	TArray<FString> AccountFlags;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString DistrictId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString InstanceId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString ServerId;

	/** Unix seconds. */
	UPROPERTY()
	int64 ExpiresAt = 0;
};

/** The part of a character everyone in the district can see (replicated on the player state). */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesPublicIdentity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString CharacterId;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesFaction Faction = EBytesFaction::Enforcer;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	int32 Rank = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	EBytesThreat Threat = EBytesThreat::Green;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Clan;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes")
	FString Appearance;

	static FBytesPublicIdentity FromClaims(const FBytesTicketClaims& Claims);
	static FBytesPublicIdentity FromCharacter(const FBytesCharacter& Character);
};

// ---- Backend response envelopes -----------------------------------------------------------------

USTRUCT()
struct FBytesLoginResponse
{
	GENERATED_BODY()

	UPROPERTY()
	FString SessionToken;

	UPROPERTY()
	FBytesAccount Account;
};

USTRUCT()
struct FBytesCharacterListResponse
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FBytesCharacter> Characters;

	UPROPERTY()
	FBytesAccount Account;
};

USTRUCT()
struct FBytesCharacterResponse
{
	GENERATED_BODY()

	UPROPERTY()
	FBytesCharacter Character;
};

USTRUCT()
struct FBytesDistrictListResponse
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FBytesDistrict> Districts;
};

USTRUCT()
struct FBytesServerRegisterResponse
{
	GENERATED_BODY()

	UPROPERTY()
	FString ServerId;

	UPROPERTY()
	FString DistrictId;

	UPROPERTY()
	FString InstanceId;

	UPROPERTY()
	FString DisplayName;

	UPROPERTY()
	int32 MaxPlayers = 0;

	UPROPERTY()
	FBytesDistrictRequirements Requirements;

	/** Standard base64 HMAC key used to verify join tickets. */
	UPROPERTY()
	FString TicketKey;

	UPROPERTY()
	int32 HeartbeatSeconds = 5;
};

USTRUCT()
struct FBytesRedeemResponse
{
	GENERATED_BODY()

	UPROPERTY()
	FBytesCharacter Character;

	UPROPERTY()
	TArray<FString> AccountFlags;
};
