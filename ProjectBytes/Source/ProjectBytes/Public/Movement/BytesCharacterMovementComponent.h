#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BytesCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EBytesGait : uint8
{
	Walk,
	Run,
	Sprint,
};

/**
 * How the character feels. The capsule always leads and animation follows (motion matching + warping), so these
 * numbers decide responsiveness; the animation side only decides how nicely it catches up.
 *   Snappy     ~APB: near-instant starts/stops/turns
 *   Responsive default: quick to react, with a few frames of weight so motion matching can show starts/plants
 *   Realistic  ~Game Animation Sample: heavy, animation-driven feel (for comparison)
 */
UENUM(BlueprintType)
enum class EBytesMovementFeel : uint8
{
	Snappy,
	Responsive,
	Realistic,
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesGaitSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement")
	float MaxSpeed = 420.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement")
	float MaxAcceleration = 2400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement")
	float BrakingDeceleration = 2600.f;

	/** Yaw degrees per second when turning toward movement / aim. Negative = instant. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement")
	float RotationRate = 720.f;
};

USTRUCT(BlueprintType)
struct PROJECTBYTES_API FBytesMovementTuning
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") FBytesGaitSettings Walk;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") FBytesGaitSettings Run;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") FBytesGaitSettings Sprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") FBytesGaitSettings Crouch;
	/** Speed multiplier while aiming/strafing (applies on top of walk/run). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") float StrafeSpeedScale = 0.85f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") float BrakingFriction = 6.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") float AirControl = 0.35f;
	/** Suggested Motion Matching node blend time for this feel (read by UBytesAnimInstance). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bytes|Movement") float MotionMatchingBlendTime = 0.18f;

	static FBytesMovementTuning ForFeel(EBytesMovementFeel Feel);
};

/**
 * Character movement with network-predicted gaits for motion matching.
 *
 * Sprint / walk / strafe(aim) intents travel in the saved-move compressed flags, so the server simulates exactly
 * what the owning client predicted: no corrections when you tap sprint. The effective gait is derived from those
 * flags + state (crouch, aiming, moving) identically on both sides.
 *
 * Simulated proxies don't normally know acceleration, which motion matching needs to predict the future trajectory
 * (starts, stops, pivots). ABytesCharacter replicates a quantized acceleration to them and it's kept here through
 * SimulateMovement - the same approach Lyra uses.
 */
UCLASS()
class PROJECTBYTES_API UBytesCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSavedMove_Bytes;

public:
	UBytesCharacterMovementComponent();

	// ---- Intents (set on the owning client; predicted + sent to the server) ----------------------

	UFUNCTION(BlueprintCallable, Category = "Bytes|Movement")
	void SetWantsToSprint(bool bWants) { bWantsToSprint = bWants; }

	UFUNCTION(BlueprintCallable, Category = "Bytes|Movement")
	void SetWantsToWalk(bool bWants) { bWantsToWalk = bWants; }

	/** Aiming: face the camera direction and strafe instead of turning toward movement. */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Movement")
	void SetWantsToStrafe(bool bWants) { bWantsToStrafe = bWants; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	bool WantsToSprint() const { return bWantsToSprint; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	bool WantsToWalk() const { return bWantsToWalk; }

	// ---- Effective state (deterministic from intents + movement state) ---------------------------

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	EBytesGait GetGait() const;

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	bool IsStrafing() const { return bWantsToStrafe; }

	const FBytesGaitSettings& GetActiveGaitSettings() const;

	/** Settings for an arbitrary gait/stance (animation uses this with the replicated gait on remote players). */
	const FBytesGaitSettings& GetGaitSettings(EBytesGait InGait, bool bCrouched) const;

	/** Upper bound used to quantize replicated acceleration (same on every machine). */
	float GetAccelerationQuantizationRange() const;

	// ---- Feel ------------------------------------------------------------------------------------

	/** Must be applied identically on server and owning client (it changes the simulation). */
	UFUNCTION(BlueprintCallable, Category = "Bytes|Movement")
	void ApplyFeel(EBytesMovementFeel NewFeel);

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	EBytesMovementFeel GetFeel() const { return Feel; }

	UFUNCTION(BlueprintPure, Category = "Bytes|Movement")
	FBytesMovementTuning GetTuning() const { return Tuning; }

	/** Called by ABytesCharacter on simulated proxies with the replicated acceleration. */
	void SetReplicatedAcceleration(const FVector& InAcceleration);

	// ---- UCharacterMovementComponent -------------------------------------------------------------

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	virtual float GetMaxBrakingDeceleration() const override;
	virtual FRotator GetDeltaRotation(float DeltaTime) const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void SimulateMovement(float DeltaTime) override;

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual bool ClientUpdatePositionAfterServerUpdate() override;

	/** Default feel; per-gait numbers below are filled from it and can then be tweaked in a Blueprint child. */
	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Movement")
	EBytesMovementFeel Feel = EBytesMovementFeel::Responsive;

	UPROPERTY(EditDefaultsOnly, Category = "Bytes|Movement")
	FBytesMovementTuning Tuning;

private:
	void UpdateRotationMode();

	bool bWantsToSprint = false;
	bool bWantsToWalk = false;
	bool bWantsToStrafe = false;
	bool bHasReplicatedAcceleration = false;
};
