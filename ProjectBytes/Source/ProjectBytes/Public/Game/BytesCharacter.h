#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/BytesCharacterMovementComponent.h"
#include "BytesCharacter.generated.h"

class UBytesAppearanceComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
struct FInputActionValue;

/** Acceleration packed into 3 bytes for simulated proxies (Lyra's scheme). */
USTRUCT()
struct FBytesReplicatedAcceleration
{
	GENERATED_BODY()

	UPROPERTY()
	uint8 AccelXYRadians = 0;

	UPROPERTY()
	uint8 AccelXYMagnitude = 0;

	UPROPERTY()
	int8 AccelZ = 0;
};

/**
 * Third-person player character for motion-matched locomotion.
 *
 * Movement is capsule-driven and network-predicted (UBytesCharacterMovementComponent); the animation Blueprint
 * (child of UBytesAnimInstance) motion-matches to whatever the capsule does, on every machine. Everything the
 * animation needs that the engine doesn't already replicate goes to simulated proxies here: gait, aiming, and a
 * quantized acceleration so remote players' trajectories predict starts/stops/pivots.
 *
 * Controls work without any input assets (built at runtime): WASD/left stick move, mouse/right stick look,
 * Shift sprint (hold), Ctrl walk (hold), C crouch (toggle), Space jump, right mouse aim (hold).
 * Assign DefaultMappingContext + the actions in a Blueprint child to use your own assets instead.
 */
UCLASS()
class PROJECTBYTES_API ABytesCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABytesCharacter(const FObjectInitializer& ObjectInitializer);

	UBytesAppearanceComponent* GetAppearance() const { return Appearance; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	UBytesCharacterMovementComponent* GetBytesMovement() const;

	/** Gait for animation: predicted locally, replicated for remote players. */
	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	EBytesGait GetGait() const;

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	bool IsAiming() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes")
	TObjectPtr<UBytesAppearanceComponent> Appearance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Over-the-shoulder framing: X = arm length, Y = shoulder offset, Z = height. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Camera")
	FVector HipCamera = FVector(320.f, 55.f, 65.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Camera")
	FVector AimCamera = FVector(170.f, 70.f, 70.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Camera")
	float HipFOV = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Camera")
	float AimFOV = 70.f;

	/** Camera blend speed between hip and aim framing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Camera")
	float CameraBlendSpeed = 12.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bytes|Input")
	float LookSensitivity = 1.f;

	// Optional asset overrides. Leave empty to use the built-in runtime bindings.
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> SprintAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> WalkAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Input") TObjectPtr<UInputAction> AimAction;

private:
	void BuildDefaultInput();
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_SprintStarted(const FInputActionValue& Value);
	void Input_SprintCompleted(const FInputActionValue& Value);
	void Input_WalkStarted(const FInputActionValue& Value);
	void Input_WalkCompleted(const FInputActionValue& Value);
	void Input_Crouch(const FInputActionValue& Value);
	void Input_JumpStarted(const FInputActionValue& Value);
	void Input_JumpCompleted(const FInputActionValue& Value);
	void Input_AimStarted(const FInputActionValue& Value);
	void Input_AimCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void OnRep_ReplicatedAcceleration();

	/** Simulated proxies only: quantized acceleration for trajectory prediction. */
	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedAcceleration)
	FBytesReplicatedAcceleration ReplicatedAcceleration;

	/** Simulated proxies only. */
	UPROPERTY(Replicated)
	EBytesGait ReplicatedGait = EBytesGait::Run;

	/** Simulated proxies only. */
	UPROPERTY(Replicated)
	bool bReplicatedAiming = false;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> RuntimeMappingContext;
};
