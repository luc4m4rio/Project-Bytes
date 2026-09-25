#include "Appearance/BytesAppearanceSubsystem.h"
#include "Appearance/BytesCharacterCreator.h"
#include "ProjectBytes.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Math/RandomStream.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"

void UBytesAppearanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ReloadCatalog();
}

UBytesAppearanceSubsystem* UBytesAppearanceSubsystem::Get(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine ? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull) : nullptr;
	const UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	return GameInstance ? GameInstance->GetSubsystem<UBytesAppearanceSubsystem>() : nullptr;
}

bool UBytesAppearanceSubsystem::ReloadCatalog()
{
	FString Path = FPaths::ProjectContentDir() / TEXT("Data/AppearanceCatalog.json");
	FParse::Value(FCommandLine::Get(), TEXT("-BytesAppearanceCatalog="), Path);

	FString Json;
	FBytesAppearanceCatalog Loaded;
	if (!FFileHelper::LoadFileToString(Json, *Path) || !FBytesAppearanceCatalog::FromJson(Json, Loaded))
	{
		UE_LOG(LogBytes, Error, TEXT("Could not load appearance catalog %s"), *Path);
		return false;
	}
	Catalog = MoveTemp(Loaded);
	bCatalogLoaded = true;
	UE_LOG(LogBytes, Log, TEXT("Appearance catalog: %d bodies, %d morphs, %d colours, %d parts, %d decals"),
		Catalog.Bodies.Num(), Catalog.Morphs.Num(), Catalog.Colors.Num(), Catalog.Parts.Num(), Catalog.Decals.Num());
	return true;
}

FBytesAppearance UBytesAppearanceSubsystem::ParseOrDefault(const FString& Json, const FString& DefaultBody) const
{
	FBytesAppearance Appearance;
	if (FBytesAppearance::FromJson(Json, Appearance) && Catalog.FindBody(Appearance.Body))
	{
		return Appearance;
	}
	return Catalog.MakeDefault(DefaultBody);
}

FBytesAppearance UBytesAppearanceSubsystem::Randomize(const FString& Body, int32 Rank, EBytesFaction Faction, int32 Seed) const
{
	FRandomStream Random(Seed >= 0 ? Seed : FMath::Rand());
	FBytesAppearance Appearance = Catalog.MakeDefault(Body);

	for (const FBytesMorphDef& Morph : Catalog.Morphs)
	{
		// Average of two rolls keeps most faces near the middle, like real people.
		const float Alpha = (Random.FRand() + Random.FRand()) * 0.5f;
		Appearance.Morphs.Add(Morph.Id, FMath::Lerp(Morph.Min, Morph.Max, Alpha));
	}
	for (const FBytesColorDef& Color : Catalog.Colors)
	{
		if (Color.Palette.Num() > 0)
		{
			Appearance.Colors.Add(Color.Id, Color.Palette[Random.RandRange(0, Color.Palette.Num() - 1)]);
		}
		else
		{
			// Free-pick colours: stay near the designer's default so random looks aren't clown-coloured.
			FLinearColor Hsv = BytesColor::FromHex(Color.DefaultValue).LinearRGBToHSV();
			Hsv.B = FMath::Clamp(Hsv.B * Random.FRandRange(0.6f, 1.4f), 0.f, 1.f);
			Appearance.Colors.Add(Color.Id, BytesColor::ToHex(Hsv.HSVToLinearRGB()));
		}
	}
	for (const FBytesSlotDef& Slot : Catalog.Slots)
	{
		TArray<const FBytesPartDef*> Options;
		for (const FBytesPartDef& Part : Catalog.Parts)
		{
			if (Part.Slot == Slot.Id && (Part.Bodies.Num() == 0 || Part.Bodies.Contains(Appearance.Body))
				&& FBytesAppearanceCatalog::UnlockErrors(Part.DisplayName, Part.MinRank, Part.Factions, Rank, Faction).Num() == 0)
			{
				Options.Add(&Part);
			}
		}
		// Optional slots stay empty half the time.
		if (Options.Num() == 0 || (!Slot.Required && Random.FRand() < 0.5f))
		{
			continue;
		}
		FBytesAppearancePart Value;
		Value.Id = Options[Random.RandRange(0, Options.Num() - 1)]->Id;
		for (int32 Channel = 0; Channel < Slot.ColorChannels; ++Channel)
		{
			const uint8 Hue = static_cast<uint8>(Random.RandRange(0, 255));
			const uint8 Saturation = static_cast<uint8>(Random.RandRange(0, 255));
			const uint8 Value8 = static_cast<uint8>(Random.RandRange(20, 230));
			Value.Colors.Add(BytesColor::ToHex(FLinearColor::MakeFromHSV8(Hue, Saturation, Value8)));
		}
		Appearance.Parts.Add(Slot.Id, Value);
	}
	return Appearance;
}

UBytesCharacterCreator* UBytesAppearanceSubsystem::BeginCreator(bool bSpawnPreview)
{
	EndCreator();
	ActiveCreator = NewObject<UBytesCharacterCreator>(this);
	ActiveCreator->Initialize(this);
	if (bSpawnPreview)
	{
		ActiveCreator->SpawnPreview(GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr);
	}
	return ActiveCreator;
}

void UBytesAppearanceSubsystem::EndCreator()
{
	if (ActiveCreator)
	{
		ActiveCreator->DestroyPreview();
		ActiveCreator = nullptr;
	}
}
