#include "Animation/BytesAnimInstance.h"
#include "Game/BytesCharacter.h"
#include "DrawDebugHelpers.h"
#include "HAL/IConsoleManager.h"

static TAutoConsoleVariable<int32> CVarBytesDebugTrajectory(
	TEXT("bytes.Anim.DebugTrajectory"), 0, TEXT("Draw predicted (green) and past (blue) locomotion trajectories (0/1)."));

namespace
{
	float SignedAngle2D(const FVector& Direction, const FRotator& Facing)
	{
		if (Direction.SizeSquared2D() < KINDA_SMALL_NUMBER)
		{
			return 0.f;
		}
		const FVector Local = Facing.UnrotateVector(Direction.GetSafeNormal2D());
		return static_cast<float>(FMath::RadiansToDegrees(FMath::Atan2(Local.Y, Local.X)));
	}
}

void UBytesAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ABytesCharacter>(TryGetPawnOwner());
	HistoryWorld.Reset();
}

void UBytesAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABytesCharacter* Owner = Character.Get();
	if (!Owner)
	{
		Character = Cast<ABytesCharacter>(TryGetPawnOwner());
		Owner = Character.Get();
	}
	const UBytesCharacterMovementComponent* Movement = Owner ? Owner->GetBytesMovement() : nullptr;
	if (!Movement)
	{
		return;
	}

	// Gait/aim come predicted on the owner and replicated on remote copies; crouch is replicated by the engine.
	Gait = Owner->GetGait();
	bIsAiming = Owner->IsAiming();
	Stance = Movement->IsCrouching() ? EBytesStance::Crouching : EBytesStance::Standing;
	const FBytesGaitSettings& GaitSettings = Movement->GetGaitSettings(Gait, Stance == EBytesStance::Crouching);
	GaitMaxSpeed = GaitSettings.MaxSpeed;

	const FRotator Facing = Owner->GetActorRotation();
	Velocity = Movement->Velocity;
	Speed = static_cast<float>(Velocity.Size2D());
	// On simulated proxies this is the replicated input intent (see ABytesCharacter::OnRep_ReplicatedAcceleration).
	Acceleration = Movement->GetCurrentAcceleration();
	AccelerationAmount = FMath::Clamp(static_cast<float>(Acceleration.Size2D()) / FMath::Max(1.f, GaitSettings.MaxAcceleration), 0.f, 1.f);
	bHasAcceleration = AccelerationAmount > 0.01f;
	MovementDirectionAngle = SignedAngle2D(Velocity, Facing);
	AccelerationDirectionAngle = SignedAngle2D(Acceleration, Facing);

	const FRotator Aim = (Owner->GetBaseAimRotation() - Facing).GetNormalized();
	AimPitch = static_cast<float>(Aim.Pitch);
	AimYaw = static_cast<float>(Aim.Yaw);

	bIsInAir = Movement->IsFalling();
	if (bWasInAir && !bIsInAir)
	{
		LandedTimer = LandingWindow;
	}
	bWasInAir = bIsInAir;
	LandedTimer = FMath::Max(0.f, LandedTimer - DeltaSeconds);
	bJustLanded = LandedTimer > 0.f;

	MotionMatchingBlendTime = Movement->GetTuning().MotionMatchingBlendTime;

	RecordHistory(DeltaSeconds);
	PredictTrajectory(GaitSettings);
	UpdateLocomotionState(DeltaSeconds, GaitSettings);

	const bool bMoving = Speed > 10.f || bHasAcceleration;
	const float OrientationTarget = !bIsInAir && bMoving ? 1.f : 0.f;
	const float StrideTarget = !bIsInAir && Speed > 10.f ? 1.f : 0.f;
	OrientationWarpingAlpha = FMath::FInterpTo(OrientationWarpingAlpha, OrientationTarget, DeltaSeconds, WarpingAlphaSpeed);
	StrideWarpingAlpha = FMath::FInterpTo(StrideWarpingAlpha, StrideTarget, DeltaSeconds, WarpingAlphaSpeed);

	if (CVarBytesDebugTrajectory.GetValueOnGameThread() != 0)
	{
		DrawDebug();
	}
}

void UBytesAnimInstance::UpdateLocomotionState(float DeltaSeconds, const FBytesGaitSettings& GaitSettings)
{
	EBytesLocomotionState NewState;
	const FVector Velocity2D(Velocity.X, Velocity.Y, 0.f);
	const FVector Accel2D(Acceleration.X, Acceleration.Y, 0.f);

	if (bIsInAir)
	{
		NewState = EBytesLocomotionState::InAir;
	}
	else if (!bHasAcceleration)
	{
		NewState = Speed > 10.f ? EBytesLocomotionState::Stopping : EBytesLocomotionState::Idle;
	}
	else if (Speed > 150.f && FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(FVector::DotProduct(Velocity2D.GetSafeNormal(), Accel2D.GetSafeNormal()), -1.0, 1.0))) > PivotAngleThreshold)
	{
		NewState = EBytesLocomotionState::Pivoting;
	}
	else if (Speed < GaitSettings.MaxSpeed * 0.8f && FVector::DotProduct(Velocity2D, Accel2D) >= 0.f)
	{
		NewState = EBytesLocomotionState::Starting;
	}
	else
	{
		NewState = EBytesLocomotionState::Moving;
	}

	TimeInLocomotionState = NewState == LocomotionState ? TimeInLocomotionState + DeltaSeconds : 0.f;
	LocomotionState = NewState;
}

void UBytesAnimInstance::PredictTrajectory(const FBytesGaitSettings& GaitSettings)
{
	// A small model of the movement component (accelerate toward input, brake without input) - good enough to
	// classify starts/stops/pivots and to visualize what motion matching is being asked to match.
	const ABytesCharacter* Owner = Character.Get();
	FutureTrajectory.Reset();
	if (!Owner || PredictionTimes.Num() == 0)
	{
		return;
	}

	constexpr float Step = 1.f / 30.f;
	const float MaxAccel = FMath::Max(1.f, GaitSettings.MaxAcceleration);
	const FVector InputDirection = Acceleration.GetSafeNormal2D();
	const FVector TargetVelocity = InputDirection * GaitSettings.MaxSpeed * AccelerationAmount;

	FVector Position = FVector::ZeroVector;
	FVector SimVelocity(Velocity.X, Velocity.Y, 0.f);
	float Time = 0.f;
	int32 NextSample = 0;
	const float LastTime = PredictionTimes.Last();
	while (NextSample < PredictionTimes.Num() && Time < LastTime + Step)
	{
		const float Rate = bHasAcceleration ? MaxAccel : GaitSettings.BrakingDeceleration;
		const FVector Delta = TargetVelocity - SimVelocity;
		SimVelocity += Delta.GetClampedToMaxSize(Rate * Step);
		Position += SimVelocity * Step;
		Time += Step;
		while (NextSample < PredictionTimes.Num() && Time >= PredictionTimes[NextSample])
		{
			FutureTrajectory.Add(Owner->GetActorRotation().UnrotateVector(Position));
			++NextSample;
		}
	}
	FutureVelocity = SimVelocity;
}

void UBytesAnimInstance::RecordHistory(float DeltaSeconds)
{
	const ABytesCharacter* Owner = Character.Get();
	if (!Owner)
	{
		return;
	}
	HistoryTimer += DeltaSeconds;
	if (HistoryWorld.Num() == 0 || HistoryTimer >= HistoryInterval)
	{
		HistoryTimer = 0.f;
		HistoryWorld.Insert(Owner->GetActorLocation(), 0);
		if (HistoryWorld.Num() > HistorySamples)
		{
			HistoryWorld.SetNum(HistorySamples);
		}
	}
	PastTrajectory.Reset();
	for (const FVector& World : HistoryWorld)
	{
		PastTrajectory.Add(Owner->GetActorTransform().InverseTransformPosition(World));
	}
}

void UBytesAnimInstance::DrawDebug() const
{
	const ABytesCharacter* Owner = Character.Get();
	UWorld* World = Owner ? Owner->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}
	const FTransform Transform = Owner->GetActorTransform();
	const FVector Feet = Owner->GetActorLocation() - FVector(0.f, 0.f, Owner->GetSimpleCollisionHalfHeight());
	FVector Previous = Feet;
	for (const FVector& Local : FutureTrajectory)
	{
		const FVector Point = Feet + Transform.GetRotation().RotateVector(Local);
		DrawDebugLine(World, Previous, Point, FColor::Green, false, -1.f, 0, 2.f);
		DrawDebugSphere(World, Point, 6.f, 6, FColor::Green);
		Previous = Point;
	}
	Previous = Feet;
	for (const FVector& Local : PastTrajectory)
	{
		const FVector Point = Transform.TransformPosition(Local) - FVector(0.f, 0.f, Owner->GetSimpleCollisionHalfHeight());
		DrawDebugLine(World, Previous, Point, FColor::Blue, false, -1.f, 0, 2.f);
		Previous = Point;
	}
	static const TCHAR* StateNames[] = { TEXT("Idle"), TEXT("Starting"), TEXT("Moving"), TEXT("Stopping"), TEXT("Pivoting"), TEXT("InAir") };
	DrawDebugString(World, Owner->GetActorLocation() + FVector(0.f, 0.f, 110.f),
		FString::Printf(TEXT("%s  %.0f cm/s  accel %.0f%%"), StateNames[static_cast<uint8>(LocomotionState)], Speed, AccelerationAmount * 100.f),
		nullptr, FColor::White, 0.f, true);
}
