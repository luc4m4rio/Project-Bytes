#include "Game/BytesCharacter.h"
#include "Appearance/BytesAppearanceComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABytesCharacter::ABytesCharacter()
{
	Appearance = CreateDefaultSubobject<UBytesAppearanceComponent>(TEXT("Appearance"));
	Appearance->BodyMeshComponentName = ACharacter::MeshComponentName;

	// Standard mannequin placement inside the capsule.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()), FRotator(0.f, -90.f, 0.f));
}
