// bytes.Creator.* console commands: the whole character creator without any UI.

#include "Appearance/BytesAppearanceSubsystem.h"
#include "Appearance/BytesCharacterCreator.h"
#include "Appearance/BytesCreatorPreviewActor.h"
#include "ProjectBytes.h"
#include "Engine/World.h"
#include "HAL/IConsoleManager.h"

namespace BytesCreatorConsole
{
	UBytesAppearanceSubsystem* GetSubsystem(UWorld* World)
	{
		UBytesAppearanceSubsystem* Subsystem = UBytesAppearanceSubsystem::Get(World);
		if (!Subsystem)
		{
			UE_LOG(LogBytes, Warning, TEXT("bytes.Creator: no appearance subsystem"));
		}
		return Subsystem;
	}

	UBytesCharacterCreator* GetCreator(UWorld* World)
	{
		UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World);
		UBytesCharacterCreator* Creator = Subsystem ? Subsystem->GetActiveCreator() : nullptr;
		if (Subsystem && !Creator)
		{
			UE_LOG(LogBytes, Warning, TEXT("No creator open: bytes.Creator.New [male|female] [Enforcer|Criminal] or bytes.Creator.Edit <character>"));
		}
		return Creator;
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

	float ArgFloat(const TArray<FString>& Args, int32 Index, float Default)
	{
		return Args.IsValidIndex(Index) ? FCString::Atof(*Args[Index]) : Default;
	}

	void ReportErrors(UBytesCharacterCreator* Creator)
	{
		for (const FString& Error : Creator->Validate())
		{
			UE_LOG(LogBytes, Warning, TEXT("  ! %s"), *Error);
		}
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

	FCommand CmdNew(TEXT("bytes.Creator.New"), TEXT("bytes.Creator.New [male|female] [Enforcer|Criminal] - start creating a character"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World))
			{
				EBytesFaction Faction = EBytesFaction::Enforcer;
				if (Args.Num() > 1)
				{
					BytesEnums::FromString(Args[1], Faction);
				}
				Subsystem->BeginCreator(true)->StartNew(Args.Num() > 0 ? Args[0] : TEXT("male"), Faction);
			}
		});

	FCommand CmdEdit(TEXT("bytes.Creator.Edit"), TEXT("bytes.Creator.Edit <character> - change an existing character's look"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World);
			if (Subsystem && NeedArgs(Args, 1, TEXT("bytes.Creator.Edit <character>")) && !Subsystem->BeginCreator(true)->StartEditing(Args[0]))
			{
				UE_LOG(LogBytes, Warning, TEXT("No character '%s' on this account (bytes.Characters)"), *Args[0]);
				Subsystem->EndCreator();
			}
		});

	FCommand CmdClose(TEXT("bytes.Creator.Close"), TEXT("Close the creator without saving"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World))
			{
				Subsystem->EndCreator();
			}
		});

	FCommand CmdBody(TEXT("bytes.Creator.Body"), TEXT("bytes.Creator.Body <male|female>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 1, TEXT("bytes.Creator.Body <id>")))
			{
				Creator->SetBody(Args[0]);
			}
		});

	FCommand CmdFaction(TEXT("bytes.Creator.Faction"), TEXT("bytes.Creator.Faction <Enforcer|Criminal> (new characters only)"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			EBytesFaction Value = EBytesFaction::Enforcer;
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 1, TEXT("bytes.Creator.Faction <faction>"))
				&& BytesEnums::FromString(Args[0], Value))
			{
				Creator->SetFaction(Value);
			}
		});

	FCommand CmdMorph(TEXT("bytes.Creator.Morph"), TEXT("bytes.Creator.Morph <id> <value> - e.g. bytes.Creator.Morph noseWidth -0.4"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 2, TEXT("bytes.Creator.Morph <id> <value>")))
			{
				Creator->SetMorph(Args[0], ArgFloat(Args, 1, 0.f));
				const UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World);
				const FBytesMorphDef* Def = Subsystem ? Subsystem->GetCatalog().FindMorph(Args[0]) : nullptr;
				if (Def && Creator->GetPreview())
				{
					Creator->GetPreview()->FocusCategory(Def->Category); // frame the face for face sliders
				}
			}
		});

	FCommand CmdResetMorphs(TEXT("bytes.Creator.ResetMorphs"), TEXT("bytes.Creator.ResetMorphs [category]"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World))
			{
				Creator->ResetMorphs(Args.Num() > 0 ? Args[0] : FString());
			}
		});

	FCommand CmdColor(TEXT("bytes.Creator.Color"), TEXT("bytes.Creator.Color <id> <#rrggbb> - skin, eyes, hair, lips, makeup"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 2, TEXT("bytes.Creator.Color <id> <#rrggbb>"))
				&& !Creator->SetColorHex(Args[0], Args[1]))
			{
				UE_LOG(LogBytes, Warning, TEXT("Unknown colour id or bad hex (use #rrggbb)"));
			}
		});

	FCommand CmdPart(TEXT("bytes.Creator.Part"), TEXT("bytes.Creator.Part <slot> [partId] - no part id clears the slot"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 1, TEXT("bytes.Creator.Part <slot> [partId]"))
				&& !Creator->SetPart(Args[0], Args.Num() > 1 ? Args[1] : FString()))
			{
				UE_LOG(LogBytes, Warning, TEXT("Can't put that in slot '%s' (bytes.Creator.List parts %s)"), *Args[0], *Args[0]);
			}
		});

	FCommand CmdPartColor(TEXT("bytes.Creator.PartColor"), TEXT("bytes.Creator.PartColor <slot> <channel 1-3> <#rrggbb>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 3, TEXT("bytes.Creator.PartColor <slot> <channel> <#rrggbb>")))
			{
				Creator->SetPartColor(Args[0], FCString::Atoi(*Args[1]) - 1, BytesColor::FromHex(Args[2]));
			}
		});

	FCommand CmdTattoo(TEXT("bytes.Creator.Tattoo"), TEXT("bytes.Creator.Tattoo <decal> <region> [x y scale rotation #color opacity]"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesCharacterCreator* Creator = GetCreator(World);
			if (!Creator || !NeedArgs(Args, 2, TEXT("bytes.Creator.Tattoo <decal> <region> [x y scale rotation #color opacity]")))
			{
				return;
			}
			const int32 Index = Creator->AddTattoo(Args[0], Args[1]);
			if (Index == INDEX_NONE)
			{
				UE_LOG(LogBytes, Warning, TEXT("Can't place '%s' on '%s' (unknown, wrong region, or layer limit)"), *Args[0], *Args[1]);
				return;
			}
			if (Args.Num() > 2)
			{
				FBytesTattooLayer Layer = Creator->GetAppearanceRef().Tattoos[Index];
				Layer.X = ArgFloat(Args, 2, Layer.X);
				Layer.Y = ArgFloat(Args, 3, Layer.Y);
				Layer.Scale = ArgFloat(Args, 4, Layer.Scale);
				Layer.Rotation = ArgFloat(Args, 5, Layer.Rotation);
				if (Args.IsValidIndex(6) && BytesColor::IsValidHex(Args[6]))
				{
					Layer.Color = Args[6];
				}
				Layer.Opacity = ArgFloat(Args, 7, Layer.Opacity);
				Creator->UpdateTattoo(Index, Layer, /*bRecordUndo*/ false);
			}
			UE_LOG(LogBytes, Display, TEXT("Tattoo layer %d added"), Index + 1);
			ReportErrors(Creator);
		});

	FCommand CmdTattooMove(TEXT("bytes.Creator.TattooMove"), TEXT("bytes.Creator.TattooMove <layer> <x> <y> [scale] [rotation]"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesCharacterCreator* Creator = GetCreator(World);
			if (!Creator || !NeedArgs(Args, 3, TEXT("bytes.Creator.TattooMove <layer> <x> <y> [scale] [rotation]")))
			{
				return;
			}
			const int32 Index = FCString::Atoi(*Args[0]) - 1;
			if (!Creator->GetAppearanceRef().Tattoos.IsValidIndex(Index))
			{
				UE_LOG(LogBytes, Warning, TEXT("No tattoo layer %s"), *Args[0]);
				return;
			}
			FBytesTattooLayer Layer = Creator->GetAppearanceRef().Tattoos[Index];
			Layer.X = ArgFloat(Args, 1, Layer.X);
			Layer.Y = ArgFloat(Args, 2, Layer.Y);
			Layer.Scale = ArgFloat(Args, 3, Layer.Scale);
			Layer.Rotation = ArgFloat(Args, 4, Layer.Rotation);
			Creator->UpdateTattoo(Index, Layer);
		});

	FCommand CmdTattooRemove(TEXT("bytes.Creator.TattooRemove"), TEXT("bytes.Creator.TattooRemove <layer>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 1, TEXT("bytes.Creator.TattooRemove <layer>")))
			{
				Creator->RemoveTattoo(FCString::Atoi(*Args[0]) - 1);
			}
		});

	FCommand CmdTattooMirror(TEXT("bytes.Creator.TattooMirror"), TEXT("bytes.Creator.TattooMirror <layer> - copy onto the opposite limb"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World); Creator && NeedArgs(Args, 1, TEXT("bytes.Creator.TattooMirror <layer>"))
				&& Creator->MirrorTattoo(FCString::Atoi(*Args[0]) - 1) == INDEX_NONE)
			{
				UE_LOG(LogBytes, Warning, TEXT("Can't mirror that layer"));
			}
		});

	FCommand CmdRandomize(TEXT("bytes.Creator.Randomize"), TEXT("bytes.Creator.Randomize [seed] - random face, body, colours and clothes"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World))
			{
				Creator->Randomize(Args.Num() > 0 ? FCString::Atoi(*Args[0]) : -1);
			}
		});

	FCommand CmdUndo(TEXT("bytes.Creator.Undo"), TEXT("Undo the last creator change"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World))
			{
				Creator->Undo();
			}
		});

	FCommand CmdRedo(TEXT("bytes.Creator.Redo"), TEXT("Redo"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World))
			{
				Creator->Redo();
			}
		});

	FCommand CmdFocus(TEXT("bytes.Creator.Focus"), TEXT("bytes.Creator.Focus <Face|Body> - camera framing"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesCharacterCreator* Creator = GetCreator(World);
			if (Creator && Creator->GetPreview())
			{
				Creator->GetPreview()->FocusCategory(Args.Num() > 0 ? Args[0] : TEXT("Body"));
			}
		});

	FCommand CmdRotate(TEXT("bytes.Creator.Rotate"), TEXT("bytes.Creator.Rotate <degrees>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesCharacterCreator* Creator = GetCreator(World);
			if (Creator && Creator->GetPreview())
			{
				Creator->GetPreview()->RotatePreview(ArgFloat(Args, 0, 45.f));
			}
		});

	FCommand CmdList(TEXT("bytes.Creator.List"), TEXT("bytes.Creator.List <morphs|colors|slots|parts <slot>|decals [region]|regions>"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesAppearanceSubsystem* Subsystem = GetSubsystem(World);
			if (!Subsystem || !NeedArgs(Args, 1, TEXT("bytes.Creator.List <morphs|colors|slots|parts <slot>|decals [region]|regions>")))
			{
				return;
			}
			const FBytesAppearanceCatalog& Catalog = Subsystem->GetCatalog();
			UBytesCharacterCreator* Creator = Subsystem->GetActiveCreator();
			const FString What = Args[0].ToLower();
			if (What == TEXT("morphs"))
			{
				for (const FBytesMorphDef& Def : Catalog.Morphs)
				{
					UE_LOG(LogBytes, Display, TEXT("  %-12s %-14s %-16s %.2f..%.2f%s"), *Def.Category, *Def.Id, *Def.DisplayName, Def.Min, Def.Max,
						Creator ? *FString::Printf(TEXT("  = %.2f"), Creator->GetMorph(Def.Id)) : TEXT(""));
				}
			}
			else if (What == TEXT("colors"))
			{
				for (const FBytesColorDef& Def : Catalog.Colors)
				{
					UE_LOG(LogBytes, Display, TEXT("  %-8s %-12s default %s%s"), *Def.Id, *Def.DisplayName, *Def.DefaultValue,
						Def.Palette.Num() > 0 ? *FString::Printf(TEXT("  palette: %s"), *FString::Join(Def.Palette, TEXT(" "))) : TEXT(""));
				}
			}
			else if (What == TEXT("slots"))
			{
				for (const FBytesSlotDef& Def : Catalog.Slots)
				{
					UE_LOG(LogBytes, Display, TEXT("  %-10s %-12s %d colour channel(s)%s"), *Def.Id, *Def.DisplayName, Def.ColorChannels, Def.Required ? TEXT(", required") : TEXT(""));
				}
			}
			else if (What == TEXT("parts") && Creator && Args.Num() > 1)
			{
				for (const FBytesCreatorOption& Option : Creator->GetPartOptions(Args[1]))
				{
					UE_LOG(LogBytes, Display, TEXT("  %s %-18s %s %s"), Option.bLocked ? TEXT("[locked]") : TEXT("        "), *Option.Id, *Option.DisplayName, *Option.LockReason);
				}
			}
			else if (What == TEXT("decals") && Creator)
			{
				for (const FBytesCreatorOption& Option : Creator->GetDecalOptions(Args.Num() > 1 ? Args[1] : FString()))
				{
					UE_LOG(LogBytes, Display, TEXT("  %s %-14s %s %s"), Option.bLocked ? TEXT("[locked]") : TEXT("        "), *Option.Id, *Option.DisplayName, *Option.LockReason);
				}
			}
			else if (What == TEXT("regions"))
			{
				for (const FBytesRegionDef& Def : Catalog.Regions)
				{
					UE_LOG(LogBytes, Display, TEXT("  %-14s %s%s"), *Def.Id, *Def.DisplayName,
						Def.MirrorRegion.IsEmpty() ? TEXT("") : *FString::Printf(TEXT("  (mirror: %s)"), *Def.MirrorRegion));
				}
			}
			else
			{
				UE_LOG(LogBytes, Warning, TEXT("parts/decals need an open creator; parts needs a slot id"));
			}
		});

	FCommand CmdShow(TEXT("bytes.Creator.Show"), TEXT("Print the current appearance JSON and anything blocking save"),
		[](const TArray<FString>&, UWorld* World)
		{
			if (UBytesCharacterCreator* Creator = GetCreator(World))
			{
				UE_LOG(LogBytes, Display, TEXT("%s"), *Creator->GetAppearanceRef().ToJson());
				ReportErrors(Creator);
			}
		});

	FCommand CmdSave(TEXT("bytes.Creator.Save"), TEXT("bytes.Creator.Save [name] - create the character (name required) or save the edited look"),
		[](const TArray<FString>& Args, UWorld* World)
		{
			UBytesCharacterCreator* Creator = GetCreator(World);
			if (!Creator)
			{
				return;
			}
			if (!Creator->IsEditingExisting() && !NeedArgs(Args, 1, TEXT("bytes.Creator.Save <name>")))
			{
				return;
			}
			TWeakObjectPtr<UBytesAppearanceSubsystem> Subsystem(GetSubsystem(World));
			Creator->Save(Args.Num() > 0 ? Args[0] : FString(), [Subsystem](bool bSuccess, const FString& Error)
			{
				if (!bSuccess)
				{
					UE_LOG(LogBytes, Warning, TEXT("Save failed: %s"), *Error);
					return;
				}
				UE_LOG(LogBytes, Display, TEXT("Character saved"));
				if (UBytesAppearanceSubsystem* Self = Subsystem.Get())
				{
					Self->EndCreator();
				}
			});
		});
}
