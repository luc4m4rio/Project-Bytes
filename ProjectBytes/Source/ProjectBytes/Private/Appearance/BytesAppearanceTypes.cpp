#include "Appearance/BytesAppearanceTypes.h"
#include "JsonObjectConverter.h"

namespace BytesColor
{
	bool IsValidHex(const FString& Hex)
	{
		if (Hex.Len() != 7 || Hex[0] != TEXT('#'))
		{
			return false;
		}
		for (int32 Index = 1; Index < 7; ++Index)
		{
			if (!FChar::IsHexDigit(Hex[Index]))
			{
				return false;
			}
		}
		return true;
	}

	FLinearColor FromHex(const FString& Hex, const FLinearColor& Fallback)
	{
		return IsValidHex(Hex) ? FLinearColor(FColor::FromHex(Hex)) : Fallback;
	}

	FString ToHex(const FLinearColor& Color)
	{
		const FColor Srgb = Color.ToFColor(/*bSRGB*/ true);
		return FString::Printf(TEXT("#%02x%02x%02x"), Srgb.R, Srgb.G, Srgb.B);
	}
}

// ---- Appearance JSON ----------------------------------------------------------------------------

FString FBytesAppearance::ToJson() const
{
	FString Json;
	FJsonObjectConverter::UStructToJsonObjectString(*this, Json, 0, 0, 0, nullptr, /*bPrettyPrint*/ false);
	return Json;
}

bool FBytesAppearance::FromJson(const FString& Json, FBytesAppearance& Out)
{
	if (Json.IsEmpty())
	{
		return false;
	}
	FBytesAppearance Parsed;
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Parsed))
	{
		return false;
	}
	Out = MoveTemp(Parsed);
	return true;
}

// ---- Catalog ------------------------------------------------------------------------------------

bool FBytesAppearanceCatalog::FromJson(const FString& Json, FBytesAppearanceCatalog& Out)
{
	FBytesAppearanceCatalog Parsed;
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(Json, &Parsed))
	{
		return false;
	}
	Out = MoveTemp(Parsed);
	return true;
}

FBox2D FBytesRegionDef::GetRect() const
{
	if (Uv.Num() < 4)
	{
		return FBox2D(FVector2D(0, 0), FVector2D(1, 1));
	}
	return FBox2D(FVector2D(Uv[0], Uv[1]), FVector2D(Uv[0] + Uv[2], Uv[1] + Uv[3]));
}

namespace
{
	template <typename TDef>
	const TDef* FindById(const TArray<TDef>& Defs, const FString& Id)
	{
		// Ids are case-sensitive in the backend, so compare exactly here too.
		return Defs.FindByPredicate([&Id](const TDef& Def) { return Def.Id.Equals(Id, ESearchCase::CaseSensitive); });
	}

	FString JoinFactions(const TArray<EBytesFaction>& Factions)
	{
		TArray<FString> Names;
		for (EBytesFaction Faction : Factions)
		{
			Names.Add(BytesEnums::ToString(Faction));
		}
		return FString::Join(Names, TEXT("/"));
	}

	float RoundTo(float Value, float Step)
	{
		return FMath::RoundToFloat(Value / Step) * Step;
	}
}

const FBytesBodyDef* FBytesAppearanceCatalog::FindBody(const FString& Id) const { return FindById(Bodies, Id); }
const FBytesMorphDef* FBytesAppearanceCatalog::FindMorph(const FString& Id) const { return FindById(Morphs, Id); }
const FBytesColorDef* FBytesAppearanceCatalog::FindColor(const FString& Id) const { return FindById(Colors, Id); }
const FBytesSlotDef* FBytesAppearanceCatalog::FindSlot(const FString& Id) const { return FindById(Slots, Id); }
const FBytesPartDef* FBytesAppearanceCatalog::FindPart(const FString& Id) const { return FindById(Parts, Id); }
const FBytesRegionDef* FBytesAppearanceCatalog::FindRegion(const FString& Id) const { return FindById(Regions, Id); }
const FBytesDecalDef* FBytesAppearanceCatalog::FindDecal(const FString& Id) const { return FindById(Decals, Id); }

const FBytesPartDef* FBytesAppearanceCatalog::FindDefaultPart(const FString& SlotId, const FString& BodyId) const
{
	const FBytesPartDef* First = nullptr;
	for (const FBytesPartDef& Part : Parts)
	{
		const bool bFits = Part.Slot == SlotId && (Part.Bodies.Num() == 0 || Part.Bodies.Contains(BodyId))
			&& Part.MinRank <= 0 && Part.Factions.Num() == 0;
		if (!bFits)
		{
			continue;
		}
		if (Part.Default)
		{
			return &Part;
		}
		if (!First)
		{
			First = &Part;
		}
	}
	return First;
}

TArray<FString> FBytesAppearanceCatalog::UnlockErrors(const FString& DisplayName, int32 MinRank, const TArray<EBytesFaction>& Factions, int32 Rank, EBytesFaction Faction)
{
	TArray<FString> Errors;
	if (MinRank > Rank)
	{
		Errors.Add(FString::Printf(TEXT("%s unlocks at rank %d"), *DisplayName, MinRank));
	}
	if (Factions.Num() > 0 && !Factions.Contains(Faction))
	{
		Errors.Add(FString::Printf(TEXT("%s is %s only"), *DisplayName, *JoinFactions(Factions)));
	}
	return Errors;
}

TArray<FString> FBytesAppearanceCatalog::Validate(FBytesAppearance& InOut, int32 Rank, EBytesFaction Faction) const
{
	// Keep in step with validate() in Backend/appearance.py - the backend has the final word.
	TArray<FString> Errors;
	if (InOut.Version != Version)
	{
		Errors.Add(FString::Printf(TEXT("Unsupported appearance version %d (expected %d)"), InOut.Version, Version));
	}
	const FBytesBodyDef* BodyDef = FindBody(InOut.Body);
	if (!BodyDef)
	{
		Errors.Add(FString::Printf(TEXT("Unknown body type '%s'"), *InOut.Body));
		return Errors;
	}

	TMap<FString, float> MorphValues;
	for (const TPair<FString, float>& Pair : InOut.Morphs)
	{
		if (const FBytesMorphDef* Def = FindMorph(Pair.Key))
		{
			MorphValues.Add(Pair.Key, RoundTo(FMath::Clamp(Pair.Value, Def->Min, Def->Max), 0.001f));
		}
	}
	InOut.Morphs = MoveTemp(MorphValues);

	TMap<FString, FString> ColorValues;
	for (const TPair<FString, FString>& Pair : InOut.Colors)
	{
		const FBytesColorDef* Def = FindColor(Pair.Key);
		if (!Def)
		{
			continue;
		}
		if (!BytesColor::IsValidHex(Pair.Value))
		{
			Errors.Add(FString::Printf(TEXT("%s must be a colour like #a1b2c3"), *Def->DisplayName));
			continue;
		}
		const FString Lower = Pair.Value.ToLower();
		if (Def->Palette.Num() > 0 && !Def->Palette.ContainsByPredicate([&Lower](const FString& P) { return P.ToLower() == Lower; }))
		{
			Errors.Add(FString::Printf(TEXT("%s must be one of the preset colours"), *Def->DisplayName));
			continue;
		}
		ColorValues.Add(Pair.Key, Lower);
	}
	InOut.Colors = MoveTemp(ColorValues);

	TMap<FString, FBytesAppearancePart> PartValues;
	for (const TPair<FString, FBytesAppearancePart>& Pair : InOut.Parts)
	{
		const FBytesSlotDef* SlotDef = FindSlot(Pair.Key);
		if (!SlotDef)
		{
			Errors.Add(FString::Printf(TEXT("Unknown clothing slot '%s'"), *Pair.Key));
			continue;
		}
		if (Pair.Value.Id.IsEmpty())
		{
			continue;
		}
		const FBytesPartDef* PartDef = FindPart(Pair.Value.Id);
		if (!PartDef)
		{
			Errors.Add(FString::Printf(TEXT("Unknown item '%s'"), *Pair.Value.Id));
			continue;
		}
		if (PartDef->Slot != SlotDef->Id)
		{
			Errors.Add(FString::Printf(TEXT("%s doesn't go in the %s slot"), *PartDef->DisplayName, *SlotDef->DisplayName));
			continue;
		}
		if (PartDef->Bodies.Num() > 0 && !PartDef->Bodies.Contains(InOut.Body))
		{
			Errors.Add(FString::Printf(TEXT("%s isn't available for %s"), *PartDef->DisplayName, *BodyDef->DisplayName));
			continue;
		}
		const TArray<FString> Unlock = UnlockErrors(PartDef->DisplayName, PartDef->MinRank, PartDef->Factions, Rank, Faction);
		if (Unlock.Num() > 0)
		{
			Errors.Append(Unlock);
			continue;
		}
		FBytesAppearancePart Clean;
		Clean.Id = PartDef->Id;
		for (int32 Index = 0; Index < FMath::Min(Pair.Value.Colors.Num(), SlotDef->ColorChannels); ++Index)
		{
			if (BytesColor::IsValidHex(Pair.Value.Colors[Index]))
			{
				Clean.Colors.Add(Pair.Value.Colors[Index].ToLower());
			}
			else
			{
				Errors.Add(FString::Printf(TEXT("%s colour %d must be a colour like #a1b2c3"), *PartDef->DisplayName, Index + 1));
			}
		}
		PartValues.Add(Pair.Key, Clean);
	}
	for (const FBytesSlotDef& SlotDef : Slots)
	{
		if (SlotDef.Required && !PartValues.Contains(SlotDef.Id))
		{
			if (const FBytesPartDef* Fallback = FindDefaultPart(SlotDef.Id, InOut.Body))
			{
				FBytesAppearancePart Part;
				Part.Id = Fallback->Id;
				PartValues.Add(SlotDef.Id, Part);
			}
		}
	}
	InOut.Parts = MoveTemp(PartValues);

	if (InOut.Tattoos.Num() > MaxTattoos)
	{
		Errors.Add(FString::Printf(TEXT("At most %d tattoo layers"), MaxTattoos));
		InOut.Tattoos.SetNum(MaxTattoos);
	}
	TArray<FBytesTattooLayer> Layers;
	for (int32 Index = 0; Index < InOut.Tattoos.Num(); ++Index)
	{
		FBytesTattooLayer Layer = InOut.Tattoos[Index];
		const FString What = FString::Printf(TEXT("Tattoo layer %d"), Index + 1);
		const FBytesDecalDef* DecalDef = FindDecal(Layer.Decal);
		if (!DecalDef)
		{
			Errors.Add(FString::Printf(TEXT("%s: unknown design '%s'"), *What, *Layer.Decal));
			continue;
		}
		const FBytesRegionDef* RegionDef = FindRegion(Layer.Region);
		if (!RegionDef)
		{
			Errors.Add(FString::Printf(TEXT("%s: unknown body region '%s'"), *What, *Layer.Region));
			continue;
		}
		if (DecalDef->Regions.Num() > 0 && !DecalDef->Regions.Contains(RegionDef->Id))
		{
			Errors.Add(FString::Printf(TEXT("%s can't be placed on the %s"), *DecalDef->DisplayName, *RegionDef->DisplayName));
			continue;
		}
		const TArray<FString> Unlock = UnlockErrors(DecalDef->DisplayName, DecalDef->MinRank, DecalDef->Factions, Rank, Faction);
		if (Unlock.Num() > 0)
		{
			Errors.Append(Unlock);
			continue;
		}
		if (!BytesColor::IsValidHex(Layer.Color))
		{
			Errors.Add(FString::Printf(TEXT("%s colour must be a colour like #a1b2c3"), *What));
			Layer.Color = TEXT("#101010");
		}
		Layer.Color = Layer.Color.ToLower();
		Layer.X = RoundTo(FMath::Clamp(Layer.X, 0.f, 1.f), 0.0001f);
		Layer.Y = RoundTo(FMath::Clamp(Layer.Y, 0.f, 1.f), 0.0001f);
		Layer.Scale = RoundTo(FMath::Clamp(Layer.Scale, TattooMinScale, TattooMaxScale), 0.0001f);
		Layer.Rotation = RoundTo(FMath::UnwindDegrees(Layer.Rotation), 0.01f);
		Layer.Opacity = RoundTo(FMath::Clamp(Layer.Opacity, 0.f, 1.f), 0.001f);
		Layers.Add(Layer);
	}
	InOut.Tattoos = MoveTemp(Layers);
	InOut.Version = Version;
	return Errors;
}

FBytesAppearance FBytesAppearanceCatalog::MakeDefault(const FString& BodyId) const
{
	FBytesAppearance Appearance;
	Appearance.Version = Version;
	Appearance.Body = FindBody(BodyId) ? BodyId : (Bodies.Num() > 0 ? Bodies[0].Id : BodyId);
	for (const FBytesSlotDef& SlotDef : Slots)
	{
		if (SlotDef.Required)
		{
			if (const FBytesPartDef* Part = FindDefaultPart(SlotDef.Id, Appearance.Body))
			{
				FBytesAppearancePart Value;
				Value.Id = Part->Id;
				Appearance.Parts.Add(SlotDef.Id, Value);
			}
		}
	}
	return Appearance;
}

float FBytesAppearanceCatalog::GetMorphValue(const FBytesAppearance& Appearance, const FString& MorphId) const
{
	if (const float* Value = Appearance.Morphs.Find(MorphId))
	{
		return *Value;
	}
	const FBytesMorphDef* Def = FindMorph(MorphId);
	return Def ? Def->DefaultValue : 0.f;
}

FLinearColor FBytesAppearanceCatalog::GetColorValue(const FBytesAppearance& Appearance, const FString& ColorId) const
{
	const FBytesColorDef* Def = FindColor(ColorId);
	const FLinearColor Fallback = Def ? BytesColor::FromHex(Def->DefaultValue) : FLinearColor::White;
	const FString* Value = Appearance.Colors.Find(ColorId);
	return Value ? BytesColor::FromHex(*Value, Fallback) : Fallback;
}
