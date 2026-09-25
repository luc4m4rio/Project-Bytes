#include "Core/BytesTypes.h"

namespace BytesEnums
{
	template <typename TEnum>
	static FString EnumToString(TEnum Value)
	{
		return StaticEnum<TEnum>()->GetNameStringByValue(static_cast<int64>(Value));
	}

	template <typename TEnum>
	static bool EnumFromString(const FString& In, TEnum& Out)
	{
		const UEnum* Enum = StaticEnum<TEnum>();
		for (int32 Index = 0; Index < Enum->NumEnums() - 1; ++Index) // last entry is the implicit _MAX
		{
			if (Enum->GetNameStringByIndex(Index).Equals(In.TrimStartAndEnd(), ESearchCase::IgnoreCase))
			{
				Out = static_cast<TEnum>(Enum->GetValueByIndex(Index));
				return true;
			}
		}
		return false;
	}

	FString ToString(EBytesFaction Faction) { return EnumToString(Faction); }
	FString ToString(EBytesThreat Threat) { return EnumToString(Threat); }
	bool FromString(const FString& In, EBytesFaction& Out) { return EnumFromString(In, Out); }
	bool FromString(const FString& In, EBytesThreat& Out) { return EnumFromString(In, Out); }
}

template <typename TEnum>
static FString JoinEnums(const TArray<TEnum>& Values)
{
	TArray<FString> Names;
	for (TEnum Value : Values)
	{
		Names.Add(BytesEnums::ToString(Value));
	}
	return FString::Join(Names, TEXT("/"));
}

bool FBytesDistrictRequirements::HasAny() const
{
	return MinRank > 0 || MaxRank > 0 || AllowedThreats.Num() > 0 || AllowedFactions.Num() > 0 || RequiredAccountFlags.Num() > 0;
}

TArray<FString> FBytesDistrictRequirements::Evaluate(int32 Rank, EBytesThreat Threat, EBytesFaction Faction, const TArray<FString>& AccountFlags) const
{
	// Keep wording in sync with evaluate_requirements() in Backend/server.py.
	TArray<FString> Reasons;
	if (MinRank > 0 && Rank < MinRank)
	{
		Reasons.Add(FString::Printf(TEXT("Requires rank %d or higher (you are rank %d)"), MinRank, Rank));
	}
	if (MaxRank > 0 && Rank > MaxRank)
	{
		Reasons.Add(FString::Printf(TEXT("Restricted to rank %d or lower (you are rank %d)"), MaxRank, Rank));
	}
	if (AllowedThreats.Num() > 0 && !AllowedThreats.Contains(Threat))
	{
		Reasons.Add(FString::Printf(TEXT("Restricted to %s threat (you are %s)"), *JoinEnums(AllowedThreats), *BytesEnums::ToString(Threat)));
	}
	if (AllowedFactions.Num() > 0 && !AllowedFactions.Contains(Faction))
	{
		Reasons.Add(FString::Printf(TEXT("Restricted to %s (you are %s)"), *JoinEnums(AllowedFactions), *BytesEnums::ToString(Faction)));
	}
	for (const FString& Flag : RequiredAccountFlags)
	{
		// FString equality is case-insensitive, so Contains() matches the backend's lower-cased comparison.
		if (!AccountFlags.Contains(Flag))
		{
			Reasons.Add(FString::Printf(TEXT("Requires account flag '%s'"), *Flag));
		}
	}
	return Reasons;
}

FString FBytesDistrictRequirements::Describe() const
{
	TArray<FString> Parts;
	if (MinRank > 0 && MaxRank > 0)
	{
		Parts.Add(FString::Printf(TEXT("Rank %d-%d"), MinRank, MaxRank));
	}
	else if (MinRank > 0)
	{
		Parts.Add(FString::Printf(TEXT("Rank %d+"), MinRank));
	}
	else if (MaxRank > 0)
	{
		Parts.Add(FString::Printf(TEXT("Rank <=%d"), MaxRank));
	}
	if (AllowedThreats.Num() > 0)
	{
		Parts.Add(JoinEnums(AllowedThreats));
	}
	if (AllowedFactions.Num() > 0)
	{
		Parts.Add(JoinEnums(AllowedFactions));
	}
	for (const FString& Flag : RequiredAccountFlags)
	{
		Parts.Add(FString::Printf(TEXT("[%s]"), *Flag));
	}
	return Parts.Num() > 0 ? FString::Join(Parts, TEXT(", ")) : TEXT("Open");
}

FBytesPublicIdentity FBytesPublicIdentity::FromClaims(const FBytesTicketClaims& Claims)
{
	FBytesPublicIdentity Identity;
	Identity.CharacterId = Claims.CharacterId;
	Identity.Name = Claims.CharacterName;
	Identity.Faction = Claims.Faction;
	Identity.Rank = Claims.Rank;
	Identity.Threat = Claims.Threat;
	Identity.Clan = Claims.Clan;
	return Identity;
}

FBytesPublicIdentity FBytesPublicIdentity::FromCharacter(const FBytesCharacter& Character)
{
	FBytesPublicIdentity Identity;
	Identity.CharacterId = Character.CharacterId;
	Identity.Name = Character.Name;
	Identity.Faction = Character.Faction;
	Identity.Rank = Character.Rank;
	Identity.Threat = Character.Threat;
	Identity.Clan = Character.Clan;
	Identity.Appearance = Character.Appearance;
	return Identity;
}
