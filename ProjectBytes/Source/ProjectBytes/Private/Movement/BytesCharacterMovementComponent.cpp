#include "Movement/BytesCharacterMovementComponent.h"
#include "GameFramework/Character.h"

// ---- Saved moves: carry the gait intents so server and client simulate the same thing ------------

class FSavedMove_Bytes : public FSavedMove_Character
{
public:
	using Super = FSavedMove_Character;

	virtual void Clear() override
	{
		Super::Clear();
		bSavedWantsToSprint = false;
		bSavedWantsToWalk = false;
		bSavedWantsToStrafe = false;
	}

	virtual uint8 GetCompressedFlags() const override
	{
		uint8 Flags = Super::GetCompressedFlags();
		if (bSavedWantsToSprint)
		{
			Flags |= FLAG_Custom_0;
		}
		if (bSavedWantsToWalk)
		{
			Flags |= FLAG_Custom_1;
		}
		if (bSavedWantsToStrafe)
		{
			Flags |= FLAG_Custom_2;
		}
		return Flags;
	}

	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override
	{
		const FSavedMove_Bytes* Other = static_cast<const FSavedMove_Bytes*>(NewMove.Get());
		if (bSavedWantsToSprint != Other->bSavedWantsToSprint || bSavedWantsToWalk != Other->bSavedWantsToWalk
			|| bSavedWantsToStrafe != Other->bSavedWantsToStrafe)
		{
			return false;
		}
		return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
	}

	virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override
	{
		Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);
		if (const UBytesCharacterMovementComponent* Movement = Cast<UBytesCharacterMovementComponent>(C->GetCharacterMovement()))
		{
			bSavedWantsToSprint = Movement->bWantsToSprint;
			bSavedWantsToWalk = Movement->bWantsToWalk;
			bSavedWantsToStrafe = Movement->bWantsToStrafe;
		}
	}

	virtual void PrepMoveFor(ACharacter* C) override
	{
		Super::PrepMoveFor(C);
		if (UBytesCharacterMovementComponent* Movement = Cast<UBytesCharacterMovementComponent>(C->GetCharacterMovement()))
		{
			Movement->bWantsToSprint = bSavedWantsToSprint;
			Movement->bWantsToWalk = bSavedWantsToWalk;
			Movement->bWantsToStrafe = bSavedWantsToStrafe;
		}
	}

	bool bSavedWantsToSprint = false;
	bool bSavedWantsToWalk = false;
	bool bSavedWantsToStrafe = false;
};

class FNetworkPredictionData_Client_Bytes : public FNetworkPredictionData_Client_Character
{
public:
	explicit FNetworkPredictionData_Client_Bytes(const UCharacterMovementComponent& ClientMovement)
		: FNetworkPredictionData_Client_Character(ClientMovement)
	{
	}

	virtual FSavedMovePtr AllocateNewMove() override
	{
		return FSavedMovePtr(new FSavedMove_Bytes());
	}
};

// ---- Tuning presets -----------------------------------------------------------------------------

namespace
{
	FBytesGaitSettings Gait(float MaxSpeed, float MaxAcceleration, float BrakingDeceleration, float RotationRate)
	{
		FBytesGaitSettings Settings;
		Settings.MaxSpeed = MaxSpeed;
		Settings.MaxAcceleration = MaxAcceleration;
		Settings.BrakingDeceleration = BrakingDeceleration;
		Settings.RotationRate = RotationRate;
		return Settings;
	}

	float AxisDelta(float Rate, float DeltaTime)
	{
		// Same convention as the engine: negative rate means "snap".
		return Rate >= 0.f ? FMath::Min(Rate * DeltaTime, 360.f) : 360.f;
	}
}

FBytesMovementTuning FBytesMovementTuning::ForFeel(EBytesMovementFeel Feel)
{
	FBytesMovementTuning T;
	switch (Feel)
	{
	case EBytesMovementFeel::Snappy:
		T.Walk = Gait(190.f, 4096.f, 4096.f, 1080.f);
		T.Run = Gait(450.f, 4096.f, 4096.f, 1080.f);
		T.Sprint = Gait(650.f, 3200.f, 3600.f, 900.f);
		T.Crouch = Gait(230.f, 4096.f, 4096.f, 1080.f);
		T.BrakingFriction = 12.f;
		T.AirControl = 0.5f;
		T.MotionMatchingBlendTime = 0.1f;
		break;
	case EBytesMovementFeel::Realistic:
		T.Walk = Gait(175.f, 700.f, 900.f, 360.f);
		T.Run = Gait(400.f, 800.f, 1000.f, 400.f);
		T.Sprint = Gait(600.f, 700.f, 900.f, 300.f);
		T.Crouch = Gait(200.f, 600.f, 800.f, 360.f);
		T.BrakingFriction = 2.f;
		T.AirControl = 0.2f;
		T.MotionMatchingBlendTime = 0.3f;
		break;
	case EBytesMovementFeel::Responsive:
	default:
		// Reaches run speed in ~0.18s and stops in ~0.16s: reacts within a couple of frames, but slow enough
		// for motion matching to show a start, a foot plant and a pivot instead of snapping.
		T.Walk = Gait(180.f, 1600.f, 2000.f, 720.f);
		T.Run = Gait(420.f, 2400.f, 2600.f, 720.f);
		T.Sprint = Gait(620.f, 1800.f, 2200.f, 540.f);
		T.Crouch = Gait(220.f, 1800.f, 2200.f, 720.f);
		T.BrakingFriction = 6.f;
		T.AirControl = 0.35f;
		T.MotionMatchingBlendTime = 0.18f;
		break;
	}
	return T;
}

// ---- Component ----------------------------------------------------------------------------------

UBytesCharacterMovementComponent::UBytesCharacterMovementComponent()
{
	// Capsule-driven locomotion (no root motion): gameplay stays crisp and prediction-friendly, animation follows.
	bOrientRotationToMovement = true;
	bUseControllerDesiredRotation = false;
	bUseSeparateBrakingFriction = true;
	GroundFriction = 8.f;
	JumpZVelocity = 480.f;
	GetNavAgentPropertiesRef().bCanCrouch = true;
	bCanWalkOffLedgesWhenCrouching = true;
	ApplyFeel(Feel);
}

#if WITH_EDITOR
void UBytesCharacterMovementComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// Picking a feel in a Blueprint child refills the numbers; tweak Tuning afterwards if needed.
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UBytesCharacterMovementComponent, Feel))
	{
		ApplyFeel(Feel);
	}
}
#endif

void UBytesCharacterMovementComponent::ApplyFeel(EBytesMovementFeel NewFeel)
{
	Feel = NewFeel;
	Tuning = FBytesMovementTuning::ForFeel(NewFeel);
	BrakingFriction = Tuning.BrakingFriction;
	AirControl = Tuning.AirControl;
	// Keep the stock fields in sync for anything (AI, trajectory prediction) that reads them directly.
	MaxWalkSpeed = Tuning.Run.MaxSpeed;
	MaxWalkSpeedCrouched = Tuning.Crouch.MaxSpeed;
	MaxAcceleration = Tuning.Run.MaxAcceleration;
	BrakingDecelerationWalking = Tuning.Run.BrakingDeceleration;
	RotationRate = FRotator(0.f, Tuning.Run.RotationRate, 0.f);
}

EBytesGait UBytesCharacterMovementComponent::GetGait() const
{
	// Sprint needs to be moving and not aiming or crouched; otherwise walk if held, else run.
	const bool bMoving = !Acceleration.IsNearlyZero() || Velocity.SizeSquared2D() > FMath::Square(10.f);
	if (bWantsToSprint && bMoving && !bWantsToStrafe && !IsCrouching())
	{
		return EBytesGait::Sprint;
	}
	return bWantsToWalk ? EBytesGait::Walk : EBytesGait::Run;
}

const FBytesGaitSettings& UBytesCharacterMovementComponent::GetActiveGaitSettings() const
{
	return GetGaitSettings(GetGait(), IsCrouching());
}

const FBytesGaitSettings& UBytesCharacterMovementComponent::GetGaitSettings(EBytesGait InGait, bool bCrouched) const
{
	if (bCrouched)
	{
		return Tuning.Crouch;
	}
	switch (InGait)
	{
	case EBytesGait::Walk: return Tuning.Walk;
	case EBytesGait::Sprint: return Tuning.Sprint;
	default: return Tuning.Run;
	}
}

float UBytesCharacterMovementComponent::GetAccelerationQuantizationRange() const
{
	return FMath::Max(1.f, FMath::Max(FMath::Max(Tuning.Walk.MaxAcceleration, Tuning.Run.MaxAcceleration),
		FMath::Max(Tuning.Sprint.MaxAcceleration, Tuning.Crouch.MaxAcceleration)));
}

float UBytesCharacterMovementComponent::GetMaxSpeed() const
{
	if (MovementMode != MOVE_Walking && MovementMode != MOVE_NavWalking && MovementMode != MOVE_Falling)
	{
		return Super::GetMaxSpeed();
	}
	const float Speed = GetActiveGaitSettings().MaxSpeed;
	return bWantsToStrafe && !IsCrouching() ? Speed * Tuning.StrafeSpeedScale : Speed;
}

float UBytesCharacterMovementComponent::GetMaxAcceleration() const
{
	return IsFalling() ? Super::GetMaxAcceleration() : GetActiveGaitSettings().MaxAcceleration;
}

float UBytesCharacterMovementComponent::GetMaxBrakingDeceleration() const
{
	return MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking
		? GetActiveGaitSettings().BrakingDeceleration
		: Super::GetMaxBrakingDeceleration();
}

FRotator UBytesCharacterMovementComponent::GetDeltaRotation(float DeltaTime) const
{
	return FRotator(AxisDelta(RotationRate.Pitch, DeltaTime), AxisDelta(GetActiveGaitSettings().RotationRate, DeltaTime),
		AxisDelta(RotationRate.Roll, DeltaTime));
}

void UBytesCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	bWantsToWalk = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
	bWantsToStrafe = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}

FNetworkPredictionData_Client* UBytesCharacterMovementComponent::GetPredictionData_Client() const
{
	if (!ClientPredictionData)
	{
		UBytesCharacterMovementComponent* MutableThis = const_cast<UBytesCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Bytes(*this);
	}
	return ClientPredictionData;
}

void UBytesCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
	UpdateRotationMode();
}

void UBytesCharacterMovementComponent::UpdateRotationMode()
{
	// Aiming: face where the camera looks and strafe. Otherwise turn toward where you're going.
	bOrientRotationToMovement = !bWantsToStrafe;
	bUseControllerDesiredRotation = bWantsToStrafe;
}

void UBytesCharacterMovementComponent::SetReplicatedAcceleration(const FVector& InAcceleration)
{
	bHasReplicatedAcceleration = true;
	Acceleration = InAcceleration;
}

void UBytesCharacterMovementComponent::SimulateMovement(float DeltaTime)
{
	if (bHasReplicatedAcceleration)
	{
		// SimulateMovement recomputes acceleration from velocity; keep the replicated input intent instead so
		// the motion matching trajectory on remote players predicts starts/stops/pivots correctly.
		const FVector ReplicatedAcceleration = Acceleration;
		Super::SimulateMovement(DeltaTime);
		Acceleration = ReplicatedAcceleration;
	}
	else
	{
		Super::SimulateMovement(DeltaTime);
	}
}
