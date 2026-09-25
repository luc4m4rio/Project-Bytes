#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BytesCreatorPreviewActor.generated.h"

class UBytesAppearanceComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USpringArmComponent;

/**
 * The mannequin you look at in the character creator: a body mesh driven by UBytesAppearanceComponent and an
 * orbit camera that frames the face or the full body depending on what is being edited.
 * Spawned by UBytesCharacterCreator::SpawnPreview, or place a Blueprint child in your frontend map (a placed
 * one is reused).
 */
UCLASS()
class PROJECTBYTES_API ABytesCreatorPreviewActor : public AActor
{
	GENERATED_BODY()

public:
	ABytesCreatorPreviewActor();

	/** "Face"/"Head"/"Nose"/"Eyes"/"Mouth" zoom on the head; anything else frames the whole body. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void FocusCategory(const FString& Category);

	/** Spin the mannequin (degrees). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Creator")
	void RotatePreview(float DeltaYaw);

	UBytesAppearanceComponent* GetAppearance() const { return Appearance; }

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Creator")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Creator")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Creator")
	TObjectPtr<UBytesAppearanceComponent> Appearance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Creator")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Creator")
	TObjectPtr<UCameraComponent> Camera;

	/** Boom target (height, arm length) per framing. */
	UPROPERTY(EditAnywhere, Category = "Bytes|Creator")
	FVector2D FaceFraming = FVector2D(165.f, 70.f);

	UPROPERTY(EditAnywhere, Category = "Bytes|Creator")
	FVector2D BodyFraming = FVector2D(95.f, 320.f);

private:
	FVector2D TargetFraming;
};
