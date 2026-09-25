#include "Appearance/BytesCreatorPreviewActor.h"
#include "Appearance/BytesAppearanceComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABytesCreatorPreviewActor::ABytesCreatorPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	// UE character meshes are authored facing +Y; rotate so they face +X, where the camera sits.
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Appearance = CreateDefaultSubobject<UBytesAppearanceComponent>(TEXT("Appearance"));
	Appearance->bFollowPlayerState = false;
	Appearance->BodyMeshComponentName = TEXT("Mesh");

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->SetRelativeRotation(FRotator(-5.f, 180.f, 0.f)); // look back at the mannequin from +X
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	TargetFraming = BodyFraming;
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, BodyFraming.X));
	CameraBoom->TargetArmLength = BodyFraming.Y;
}

void ABytesCreatorPreviewActor::FocusCategory(const FString& Category)
{
	static const TArray<FString> FaceCategories = { TEXT("Face"), TEXT("Head"), TEXT("Nose"), TEXT("Eyes"), TEXT("Mouth") };
	TargetFraming = FaceCategories.Contains(Category) ? FaceFraming : BodyFraming;
}

void ABytesCreatorPreviewActor::RotatePreview(float DeltaYaw)
{
	Mesh->AddRelativeRotation(FRotator(0.f, DeltaYaw, 0.f));
}

void ABytesCreatorPreviewActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Ease the camera between face and body framing.
	const float Alpha = FMath::Clamp(DeltaSeconds * 6.f, 0.f, 1.f);
	FVector Location = CameraBoom->GetRelativeLocation();
	Location.Z = FMath::Lerp(Location.Z, TargetFraming.X, Alpha);
	CameraBoom->SetRelativeLocation(Location);
	CameraBoom->TargetArmLength = FMath::Lerp(CameraBoom->TargetArmLength, TargetFraming.Y, Alpha);
}
