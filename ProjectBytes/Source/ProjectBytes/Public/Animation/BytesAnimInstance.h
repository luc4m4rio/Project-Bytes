#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Movement/BytesCharacterMovementComponent.h"
#include "BytesAnimInstance.generated.h"

class ABytesCharacter;

UENUM(BlueprintType)
enum class EBytesStance : uint8
{
	Standing,
	Crouching,
};

/** Coarse locomotion phase: handy as a Chooser key to pick motion matching databases, and for debugging. */
UENUM(BlueprintType)
enum class EBytesLocomotionState : uint8
{
	Idle,
	Starting,
	Moving,
	Stopping,
	Pivoting,
	InAir,
};

/**
 * Parent class for the motion matching Animation Blueprint.
 *
 * Every machine (owner, other clients, listen host) runs motion matching locally; nothing about the pose is
 * replicated. What makes remote players look right is that the inputs here are the same everywhere:
 * velocity/rotation from the movement replication, plus gait, aiming and acceleration that ABytesCharacter
 * replicates to simulated proxies. On a dedicated server the mesh doesn't tick poses at all.
 *
 * The AnimBP reads these properties (thread-safe member access) to:
 *   - pick databases in a Chooser table (Gait, Stance, bIsAiming, LocomotionState, bIsInAir)
 *   - drive the Motion Matching node (MotionMatchingBlendTime from the active movement feel)
 *   - feed Orientation Warping (MovementDirectionAngle) and Stride Warping (Speed)
 * The trajectory the Motion Matching node searches with comes from the engine's trajectory generation in the
 * AnimBP; it reads the character movement component, which on remote players now carries real acceleration.
 * FutureTrajectory/PastTrajectory here are a light C++ prediction used for LocomotionState and debug drawing
 * (bytes.Anim.DebugTrajectory 1).
 */
UCLASS()
class PROJECTBYTES_API UBytesAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// ---- Selection keys --------------------------------------------------------------------------

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	EBytesGait Gait = EBytesGait::Run;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	EBytesStance Stance = EBytesStance::Standing;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	EBytesLocomotionState LocomotionState = EBytesLocomotionState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	bool bIsAiming = false;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	bool bIsInAir = false;

	/** True for LandingWindow seconds after touching down (pick landing databases / additive). */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	bool bJustLanded = false;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float TimeInLocomotionState = 0.f;

	// ---- Kinematics ------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	FVector Velocity = FVector::ZeroVector;

	/** Horizontal speed (cm/s): Stride Warping locomotion speed. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float Speed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	FVector Acceleration = FVector::ZeroVector;

	/** 0..1 of the current gait's max acceleration: how hard the stick/keys are pushed. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float AccelerationAmount = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	bool bHasAcceleration = false;

	/** Velocity direction relative to where the character faces (-180..180): Orientation Warping angle. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float MovementDirectionAngle = 0.f;

	/** Where the player is pushing, relative to facing (-180..180). */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float AccelerationDirectionAngle = 0.f;

	/** Aim offset inputs, relative to the actor (replicated control pitch on remote players). */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float AimPitch = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float AimYaw = 0.f;

	/** Gait max speed the animation should match (Stride Warping reference, playrate clamps). */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Locomotion")
	float GaitMaxSpeed = 420.f;

	// ---- Prediction ------------------------------------------------------------------------------

	/** Predicted positions (actor-local) at PredictionTimes. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Trajectory")
	TArray<FVector> FutureTrajectory;

	/** Recorded positions (actor-local), newest first, every HistoryInterval. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Trajectory")
	TArray<FVector> PastTrajectory;

	/** Predicted velocity at the last prediction time. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Trajectory")
	FVector FutureVelocity = FVector::ZeroVector;

	// ---- Motion matching tuning (bind to node pins) -----------------------------------------------

	/** From the movement feel preset: short = snappy, long = smooth. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Motion Matching")
	float MotionMatchingBlendTime = 0.18f;

	/** Full while moving/strafing; eases out at idle so the character doesn't twist in place. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Motion Matching")
	float OrientationWarpingAlpha = 0.f;

	/** Full while grounded and moving; off in air. */
	UPROPERTY(BlueprintReadOnly, Category = "Bytes|Motion Matching")
	float StrideWarpingAlpha = 0.f;

	// ---- Settings --------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Trajectory")
	TArray<float> PredictionTimes = { 0.25f, 0.5f, 1.0f };

	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Trajectory")
	float HistoryInterval = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Trajectory")
	int32 HistorySamples = 4;

	/** Angle between velocity and input above which a change of direction counts as a pivot. */
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Locomotion")
	float PivotAngleThreshold = 110.f;

	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Locomotion")
	float LandingWindow = 0.2f;

	/** How fast the warping alphas follow their targets. */
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Motion Matching")
	float WarpingAlphaSpeed = 8.f;

private:
	void UpdateLocomotionState(float DeltaSeconds, const FBytesGaitSettings& GaitSettings);
	void PredictTrajectory(const FBytesGaitSettings& GaitSettings);
	void RecordHistory(float DeltaSeconds);
	void DrawDebug() const;

	TWeakObjectPtr<ABytesCharacter> Character;
	TArray<FVector> HistoryWorld;
	float HistoryTimer = 0.f;
	float LandedTimer = 0.f;
	bool bWasInAir = false;
};
