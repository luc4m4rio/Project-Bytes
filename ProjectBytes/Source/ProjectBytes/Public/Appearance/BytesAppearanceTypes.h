#pragma once

#include "CoreMinimal.h"
#include "Core/BytesTypes.h"
#include "BytesAppearanceTypes.generated.h"

// APB-style character appearance: body type, morph sliders, material colours, clothing parts with colour
// channels, and tattoo/decal layers placed on body regions.
//
// Stored as JSON in FBytesCharacter::Appearance. The same rules are enforced by Backend/appearance.py
// (authoritative for unlocks) and FBytesAppearanceCatalog::Validate (instant feedback in the creator).
// What exists is described by Content/Data/AppearanceCatalog.json, shared by game and backend.

// ---- The appearance document --------------------------------------------------------------------

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesAppearancePart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FString Id;

	/** "#rrggbb" per colour channel of the slot (primary, secondary, tertiary). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	TArray<FString> Colors;
};

/** One tattoo / decal layer. Position and scale are relative to the body region's rectangle. */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesTattooLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FString Decal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FString Region;

	/** 0..1 across the region. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	float X = 0.5f;

	/** 0..1 down the region. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	float Y = 0.5f;

	/** Fraction of the region width. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	float Scale = 0.3f;

	/** Degrees, -180..180. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	float Rotation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FString Color = TEXT("#101010");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	float Opacity = 1.f;

	/** Flip the design horizontally. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	bool Mirror = false;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesAppearance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	int32 Version = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	FString Body = TEXT("male");

	/** Morph id -> slider value (range from the catalog). Missing = the morph's default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	TMap<FString, float> Morphs;

	/** Colour id (skin, eyes, hair...) -> "#rrggbb". Missing = the colour's default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	TMap<FString, FString> Colors;

	/** Slot id (hair, top, legs...) -> part. Missing = empty slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	TMap<FString, FBytesAppearancePart> Parts;

	/** Drawn in order: later layers on top. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Appearance")
	TArray<FBytesTattooLayer> Tattoos;

	FString ToJson() const;
	/** Empty string -> false (caller uses the catalog's default look). */
	static bool FromJson(const FString& Json, FBytesAppearance& Out);
};

// ---- The catalog (Content/Data/AppearanceCatalog.json) -------------------------------------------

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesBodyDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** Soft object path of the body USkeletalMesh. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Mesh;
	/** Optional soft class path of the AnimInstance. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString AnimClass;
	/** Material slot names that receive skin colours + tattoo overlay. Empty = all slots. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> SkinMaterialSlots;
};

/** A slider. Negative values drive NegTarget, positive values drive PosTarget (morph target names). */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesMorphDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** UI grouping: Body, Head, Nose, Eyes, Mouth... */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Category;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float Min = -1.f;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float Max = 1.f;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float DefaultValue = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString NegTarget;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString PosTarget;
	/** If set (non-zero), the slider also scales the whole mesh: Min maps to MeshScaleMin, Max to MeshScaleMax. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float MeshScaleMin = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float MeshScaleMax = 0.f;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesColorDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** Material vector parameter name. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Parameter;
	/** "body" and/or slot ids whose materials receive the parameter. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> ApplyTo;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DefaultValue;
	/** If non-empty, only these colours are allowed. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> Palette;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesSlotDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** Required slots get the default part if left empty. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") bool Required = false;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 ColorChannels = 0;
	/** Material vector parameter per colour channel. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> ColorParameters;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesPartDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Slot;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** Body ids this part exists for. Empty = all. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> Bodies;
	/** Body id -> soft object path of the USkeletalMesh. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TMap<FString, FString> Mesh;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 MinRank = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<EBytesFaction> Factions;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") bool Default = false;
};

/** A rectangle of the skin texture atlas that tattoos can be placed in. */
USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesRegionDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** [x, y, width, height] in 0..1 atlas UV space. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<float> Uv;
	/** Region on the other side of the body, for "mirror to other arm". */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString MirrorRegion;

	FBox2D GetRect() const;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesDecalDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Id;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString DisplayName;
	/** Soft object path of the UTexture2D (white/alpha design, tinted by the layer colour). */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString Texture;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 MinRank = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<EBytesFaction> Factions;
	/** Allowed regions. Empty = anywhere. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FString> Regions;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesAppearanceCatalog
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 Version = 1;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 MaxTattoos = 16;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") int32 TattooAtlasSize = 2048;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float TattooMinScale = 0.05f;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") float TattooMaxScale = 1.f;
	/** Texture parameter on the skin material that receives the composited tattoo render target. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") FString TattooTextureParameter = TEXT("TattooOverlay");
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesBodyDef> Bodies;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesMorphDef> Morphs;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesColorDef> Colors;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesSlotDef> Slots;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesPartDef> Parts;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesRegionDef> Regions;
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Appearance") TArray<FBytesDecalDef> Decals;

	static bool FromJson(const FString& Json, FBytesAppearanceCatalog& Out);

	const FBytesBodyDef* FindBody(const FString& Id) const;
	const FBytesMorphDef* FindMorph(const FString& Id) const;
	const FBytesColorDef* FindColor(const FString& Id) const;
	const FBytesSlotDef* FindSlot(const FString& Id) const;
	const FBytesPartDef* FindPart(const FString& Id) const;
	const FBytesRegionDef* FindRegion(const FString& Id) const;
	const FBytesDecalDef* FindDecal(const FString& Id) const;
	/** Default (else first) unrestricted part for a slot + body. Mirrors Catalog.default_part in Python. */
	const FBytesPartDef* FindDefaultPart(const FString& SlotId, const FString& BodyId) const;

	/** Empty = unlocked. Wording mirrors _unlock_errors in Backend/appearance.py. */
	static TArray<FString> UnlockErrors(const FString& DisplayName, int32 MinRank, const TArray<EBytesFaction>& Factions, int32 Rank, EBytesFaction Faction);

	/**
	 * Normalizes InOut in place (clamps numbers, drops unknown morphs/colours, fills required slots) and
	 * returns the reasons it isn't allowed. Mirrors validate() in Backend/appearance.py.
	 */
	TArray<FString> Validate(FBytesAppearance& InOut, int32 Rank, EBytesFaction Faction) const;

	/** Body + required default parts, everything else at defaults. */
	FBytesAppearance MakeDefault(const FString& BodyId) const;

	float GetMorphValue(const FBytesAppearance& Appearance, const FString& MorphId) const;
	FLinearColor GetColorValue(const FBytesAppearance& Appearance, const FString& ColorId) const;
};

namespace BytesColor
{
	/** "#rrggbb" (sRGB) -> linear colour. */
	PROJECTBYTES_API FLinearColor FromHex(const FString& Hex, const FLinearColor& Fallback = FLinearColor::White);
	PROJECTBYTES_API FString ToHex(const FLinearColor& Color);
	PROJECTBYTES_API bool IsValidHex(const FString& Hex);
}
