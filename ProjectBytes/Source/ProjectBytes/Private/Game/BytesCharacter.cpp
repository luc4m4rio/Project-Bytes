#include "Game/BytesCharacter.h"
#include "Appearance/BytesAppearanceComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "Net/UnrealNetwork.h"

ABytesCharacter::ABytesCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBytesCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	// The camera turns the view; the movement component decides how the body turns (toward movement, or toward
	// the aim direction while aiming).
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Appearance = CreateDefaultSubobject<UBytesAppearanceComponent>(TEXT("Appearance"));
	Appearance->BodyMeshComponentName = ACharacter::MeshComponentName;

	// Standard mannequin placement inside the capsule.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()), FRotator(0.f, -90.f, 0.f));
	// Motion matching is cosmetic: don't run it where nobody is looking (dedicated servers, off-screen players).
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickMontagesWhenNotRendered;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = HipCamera.X;
	CameraBoom->SocketOffset = FVector(0.f, HipCamera.Y, HipCamera.Z);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 18.f; // a touch of lag reads as weight without making aim feel floaty

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetFieldOfView(HipFOV);
}

UBytesCharacterMovementComponent* ABytesCharacter::GetBytesMovement() const
{
	return Cast<UBytesCharacterMovementComponent>(GetCharacterMovement());
}

void ABytesCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority() && GetBytesMovement())
	{
		ReplicatedFeel = GetBytesMovement()->GetFeel();
	}
	if (GetNetMode() == NM_DedicatedServer)
	{
		// Servers never render: only montages (for gameplay notifies) tick.
		GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickMontagesWhenNotRendered;
	}
}

// ---- Replication --------------------------------------------------------------------------------

void ABytesCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// The owner predicts these itself; only remote copies need them.
	DOREPLIFETIME_CONDITION(ABytesCharacter, ReplicatedAcceleration, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ABytesCharacter, ReplicatedGait, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ABytesCharacter, bReplicatedAiming, COND_SimulatedOnly);
	DOREPLIFETIME(ABytesCharacter, ReplicatedFeel);
}

void ABytesCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	const UBytesCharacterMovementComponent* Movement = GetBytesMovement();
	if (!Movement)
	{
		return;
	}
	const double Range = Movement->GetAccelerationQuantizationRange();
	const FVector Accel = Movement->GetCurrentAcceleration();
	double Magnitude = 0.0;
	double Radians = 0.0;
	FMath::CartesianToPolar(Accel.X, Accel.Y, Magnitude, Radians);

	// Angle wraps naturally into a byte (256 steps around the circle).
	ReplicatedAcceleration.AccelXYRadians = static_cast<uint8>(FMath::FloorToInt32((Radians / UE_TWO_PI) * 256.0) & 0xFF);
	ReplicatedAcceleration.AccelXYMagnitude = static_cast<uint8>(FMath::Clamp(FMath::FloorToInt32((Magnitude / Range) * 255.0), 0, 255));
	ReplicatedAcceleration.AccelZ = static_cast<int8>(FMath::Clamp(FMath::FloorToInt32((Accel.Z / Range) * 127.0), -127, 127));
	ReplicatedGait = Movement->GetGait();
	bReplicatedAiming = Movement->IsStrafing();
}

void ABytesCharacter::OnRep_ReplicatedAcceleration()
{
	UBytesCharacterMovementComponent* Movement = GetBytesMovement();
	if (!Movement)
	{
		return;
	}
	const double Range = Movement->GetAccelerationQuantizationRange();
	const double Magnitude = (ReplicatedAcceleration.AccelXYMagnitude / 255.0) * Range;
	const double Radians = (ReplicatedAcceleration.AccelXYRadians / 256.0) * UE_TWO_PI;
	FVector Accel;
	FMath::PolarToCartesian(Magnitude, Radians, Accel.X, Accel.Y);
	Accel.Z = (ReplicatedAcceleration.AccelZ / 127.0) * Range;
	Movement->SetReplicatedAcceleration(Accel);
}

void ABytesCharacter::SetMovementFeel(EBytesMovementFeel NewFeel)
{
	if (HasAuthority() && GetBytesMovement())
	{
		ReplicatedFeel = NewFeel;
		GetBytesMovement()->ApplyFeel(NewFeel);
	}
}

void ABytesCharacter::OnRep_MovementFeel()
{
	if (UBytesCharacterMovementComponent* Movement = GetBytesMovement(); Movement && Movement->GetFeel() != ReplicatedFeel)
	{
		Movement->ApplyFeel(ReplicatedFeel);
	}
}

EBytesGait ABytesCharacter::GetGait() const
{
	const UBytesCharacterMovementComponent* Movement = GetBytesMovement();
	if (GetLocalRole() == ROLE_SimulatedProxy || !Movement)
	{
		return ReplicatedGait;
	}
	return Movement->GetGait();
}

bool ABytesCharacter::IsAiming() const
{
	const UBytesCharacterMovementComponent* Movement = GetBytesMovement();
	if (GetLocalRole() == ROLE_SimulatedProxy || !Movement)
	{
		return bReplicatedAiming;
	}
	return Movement->IsStrafing();
}

// ---- Camera -------------------------------------------------------------------------------------

void ABytesCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!IsLocallyControlled())
	{
		return;
	}
	const bool bAim = IsAiming();
	const FVector Target = bAim ? AimCamera : HipCamera;
	const float Alpha = FMath::Clamp(DeltaSeconds * CameraBlendSpeed, 0.f, 1.f);
	CameraBoom->TargetArmLength = FMath::Lerp(CameraBoom->TargetArmLength, static_cast<float>(Target.X), Alpha);
	CameraBoom->SocketOffset = FMath::Lerp(CameraBoom->SocketOffset, FVector(0.f, Target.Y, Target.Z), Alpha);
	FollowCamera->SetFieldOfView(FMath::Lerp(FollowCamera->FieldOfView, bAim ? AimFOV : HipFOV, Alpha));
}

// ---- Input --------------------------------------------------------------------------------------

namespace
{
	UInputAction* MakeAction(UObject* Outer, const TCHAR* Name, EInputActionValueType Type)
	{
		UInputAction* Action = NewObject<UInputAction>(Outer, Name);
		Action->ValueType = Type;
		return Action;
	}

	void MapDirection(UInputMappingContext* Context, UInputAction* Action, const FKey& Key, bool bSwizzle, bool bNegate)
	{
		FEnhancedActionKeyMapping& Mapping = Context->MapKey(Action, Key);
		if (bSwizzle)
		{
			Mapping.Modifiers.Add(NewObject<UInputModifierSwizzleAxis>(Context)); // default YXZ: key drives Y
		}
		if (bNegate)
		{
			Mapping.Modifiers.Add(NewObject<UInputModifierNegate>(Context));
		}
	}
}

void ABytesCharacter::BuildDefaultInput()
{
	if (DefaultMappingContext || RuntimeMappingContext)
	{
		return; // designer-provided assets, or already built (called from both restart and input setup)
	}
	RuntimeMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_BytesDefault"));
	UInputMappingContext* Context = RuntimeMappingContext;

	MoveAction = MakeAction(this, TEXT("IA_Move"), EInputActionValueType::Axis2D);
	LookAction = MakeAction(this, TEXT("IA_Look"), EInputActionValueType::Axis2D);
	SprintAction = MakeAction(this, TEXT("IA_Sprint"), EInputActionValueType::Boolean);
	WalkAction = MakeAction(this, TEXT("IA_Walk"), EInputActionValueType::Boolean);
	CrouchAction = MakeAction(this, TEXT("IA_Crouch"), EInputActionValueType::Boolean);
	JumpAction = MakeAction(this, TEXT("IA_Jump"), EInputActionValueType::Boolean);
	AimAction = MakeAction(this, TEXT("IA_Aim"), EInputActionValueType::Boolean);

	// Move: X = right, Y = forward.
	MapDirection(Context, MoveAction, EKeys::W, /*Swizzle*/ true, /*Negate*/ false);
	MapDirection(Context, MoveAction, EKeys::S, true, true);
	MapDirection(Context, MoveAction, EKeys::D, false, false);
	MapDirection(Context, MoveAction, EKeys::A, false, true);
	Context->MapKey(MoveAction, EKeys::Gamepad_Left2D);

	// Look: mouse Y is inverted relative to pitch input.
	{
		FEnhancedActionKeyMapping& Mouse = Context->MapKey(LookAction, EKeys::Mouse2D);
		UInputModifierNegate* NegateY = NewObject<UInputModifierNegate>(Context);
		NegateY->bX = false;
		NegateY->bY = true;
		NegateY->bZ = false;
		Mouse.Modifiers.Add(NegateY);

		FEnhancedActionKeyMapping& Stick = Context->MapKey(LookAction, EKeys::Gamepad_Right2D);
		// Sticks are a rate, not a delta: scale by frame time (~150 deg/s with the default 2.5 input scale).
		Stick.Modifiers.Add(NewObject<UInputModifierScaleByDeltaTime>(Context));
		UInputModifierScalar* StickSpeed = NewObject<UInputModifierScalar>(Context);
		StickSpeed->Scalar = FVector(60.0, 60.0, 1.0);
		Stick.Modifiers.Add(StickSpeed);
		UInputModifierNegate* StickNegateY = NewObject<UInputModifierNegate>(Context);
		StickNegateY->bX = false;
		StickNegateY->bY = true;
		StickNegateY->bZ = false;
		Stick.Modifiers.Add(StickNegateY);
	}

	Context->MapKey(SprintAction, EKeys::LeftShift);
	Context->MapKey(SprintAction, EKeys::Gamepad_LeftThumbstick);
	Context->MapKey(WalkAction, EKeys::LeftControl);
	Context->MapKey(CrouchAction, EKeys::C);
	Context->MapKey(CrouchAction, EKeys::Gamepad_FaceButton_Right);
	Context->MapKey(JumpAction, EKeys::SpaceBar);
	Context->MapKey(JumpAction, EKeys::Gamepad_FaceButton_Bottom);
	Context->MapKey(AimAction, EKeys::RightMouseButton);
	Context->MapKey(AimAction, EKeys::Gamepad_LeftTrigger);
}

void ABytesCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	BuildDefaultInput();

	const APlayerController* PC = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Input = PC ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()) : nullptr;
	if (Input)
	{
		Input->ClearAllMappings();
		Input->AddMappingContext(DefaultMappingContext ? DefaultMappingContext.Get() : RuntimeMappingContext.Get(), 0);
	}
}

void ABytesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BuildDefaultInput();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!Input)
	{
		return; // project isn't using Enhanced Input as its input component class
	}
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	Input->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::Input_SprintStarted);
	Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::Input_SprintCompleted);
	Input->BindAction(WalkAction, ETriggerEvent::Started, this, &ThisClass::Input_WalkStarted);
	Input->BindAction(WalkAction, ETriggerEvent::Completed, this, &ThisClass::Input_WalkCompleted);
	Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::Input_Crouch);
	Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Input_JumpStarted);
	Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::Input_JumpCompleted);
	Input->BindAction(AimAction, ETriggerEvent::Started, this, &ThisClass::Input_AimStarted);
	Input->BindAction(AimAction, ETriggerEvent::Completed, this, &ThisClass::Input_AimCompleted);
}

void ABytesCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (!Controller)
	{
		return;
	}
	const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f);
	AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::X), Axis.Y);
	AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y), Axis.X);
}

void ABytesCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>() * LookSensitivity;
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ABytesCharacter::Input_SprintStarted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToSprint(true);
}

void ABytesCharacter::Input_SprintCompleted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToSprint(false);
}

void ABytesCharacter::Input_WalkStarted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToWalk(true);
}

void ABytesCharacter::Input_WalkCompleted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToWalk(false);
}

void ABytesCharacter::Input_Crouch(const FInputActionValue&)
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void ABytesCharacter::Input_JumpStarted(const FInputActionValue&)
{
	Jump();
}

void ABytesCharacter::Input_JumpCompleted(const FInputActionValue&)
{
	StopJumping();
}

void ABytesCharacter::Input_AimStarted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToStrafe(true);
}

void ABytesCharacter::Input_AimCompleted(const FInputActionValue&)
{
	GetBytesMovement()->SetWantsToStrafe(false);
}
