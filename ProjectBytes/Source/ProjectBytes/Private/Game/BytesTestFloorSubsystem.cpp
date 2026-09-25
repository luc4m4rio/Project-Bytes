#include "Game/BytesTestFloorSubsystem.h"
#include "Core/BytesSettings.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/DirectionalLight.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

namespace
{
	void SpawnBlock(UWorld& World, UStaticMesh* Cube, const FVector& Location, const FVector& Scale)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AStaticMeshActor* Block = World.SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator, Params);
		if (!Block)
		{
			return;
		}
		Block->SetReplicates(false);
		UStaticMeshComponent* Mesh = Block->GetStaticMeshComponent();
		Mesh->SetMobility(EComponentMobility::Movable);
		Mesh->SetStaticMesh(Cube);
		Mesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
		Block->SetActorScale3D(Scale);
	}
}

bool UBytesTestFloorSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	const UWorld* World = Cast<UWorld>(Outer);
	return Super::ShouldCreateSubsystem(Outer) && World && World->IsGameWorld();
}

void UBytesTestFloorSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	const FString MapName = UWorld::RemovePIEPrefix(InWorld.GetOutermost()->GetName());
	if (!UBytesSettings::Get()->bSpawnTestFloorOnEntryMap || MapName != TEXT("/Engine/Maps/Entry"))
	{
		return;
	}
	UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (!Cube)
	{
		return;
	}

	// 1m cube scaled to a 160m x 160m slab whose top is at Z = -100 (players spawn at the origin).
	SpawnBlock(InWorld, Cube, FVector(0.f, 0.f, -150.f), FVector(160.f, 160.f, 1.f));
	// Ring of pillars as reference points for turning, pivots and sprint runs.
	for (int32 Index = 0; Index < 8; ++Index)
	{
		const FVector Direction = FRotator(0.f, Index * 45.f, 0.f).Vector();
		SpawnBlock(InWorld, Cube, Direction * 1500.f + FVector(0.f, 0.f, 50.f), FVector(1.f, 1.f, 3.f));
	}
	// A low wall and a step to run along / jump onto.
	SpawnBlock(InWorld, Cube, FVector(600.f, -800.f, -75.f), FVector(8.f, 0.5f, 0.5f));
	SpawnBlock(InWorld, Cube, FVector(-700.f, 700.f, -80.f), FVector(4.f, 4.f, 0.4f));

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (ADirectionalLight* Sun = InWorld.SpawnActor<ADirectionalLight>(FVector(0.f, 0.f, 1000.f), FRotator(-50.f, 35.f, 0.f), Params))
	{
		Sun->SetReplicates(false);
		Sun->GetLightComponent()->SetMobility(EComponentMobility::Movable);
		Sun->GetLightComponent()->SetIntensity(6.f);
	}

	if (InWorld.GetNetMode() != NM_Client)
	{
		// Spread spawns so a full district doesn't stack everyone on the origin.
		for (int32 Index = 0; Index < 16; ++Index)
		{
			const FVector Location = FRotator(0.f, Index * 22.5f, 0.f).Vector() * (300.f + 60.f * (Index % 4));
			InWorld.SpawnActor<APlayerStart>(Location, FRotator(0.f, Index * 22.5f + 180.f, 0.f), Params);
		}
	}
}
