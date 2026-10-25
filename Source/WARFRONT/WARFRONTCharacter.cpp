// Copyright Epic Games, Inc. All Rights Reserved.

#include "WARFRONTCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Net/UnrealNetwork.h"
#include "WARFRONT.h"

AWARFRONTCharacter::AWARFRONTCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Tick drives the camera blend
	PrimaryActorTick.bCanEverTick = true;

	DefaultToggleCameraKey = EKeys::V;
}

void AWARFRONTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// capture the third person setup after blueprint defaults so overrides are respected
	ThirdPersonArmLength = CameraBoom->TargetArmLength;
	ThirdPersonBoomLocation = CameraBoom->GetRelativeLocation();
	ThirdPersonSocketOffset = CameraBoom->SocketOffset;
	ThirdPersonTargetOffset = CameraBoom->TargetOffset;
	bThirdPersonOrientRotationToMovement = GetCharacterMovement()->bOrientRotationToMovement;
	bThirdPersonUseControllerRotationYaw = bUseControllerRotationYaw;
}

void AWARFRONTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// the owner applies its own camera mode immediately
	DOREPLIFETIME_CONDITION(AWARFRONTCharacter, CameraMode, COND_SkipOwner);
}

void AWARFRONTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// only the owning player has a camera to blend
	if (IsLocallyControlled())
	{
		UpdateCameraBlend(DeltaTime);
	}
}

void AWARFRONTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWARFRONTCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AWARFRONTCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWARFRONTCharacter::Look);

		// Camera perspective
		UInputAction* CameraAction = ToggleCameraAction ? ToggleCameraAction : CreateDefaultToggleCameraInput();

		if (CameraAction)
		{
			EnhancedInputComponent->BindAction(CameraAction, ETriggerEvent::Started, this, &AWARFRONTCharacter::ToggleCameraMode);
		}
	}
	else
	{
		UE_LOG(LogWARFRONT, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWARFRONTCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AWARFRONTCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AWARFRONTCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AWARFRONTCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AWARFRONTCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AWARFRONTCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

UInputAction* AWARFRONTCharacter::CreateDefaultToggleCameraInput()
{
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController)
	{
		return nullptr;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (!Subsystem)
	{
		return nullptr;
	}

	// create the action and its mapping once
	if (!RuntimeToggleCameraAction)
	{
		RuntimeToggleCameraAction = NewObject<UInputAction>(this, TEXT("IA_ToggleCamera"));

		RuntimeCameraMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Camera"));
		RuntimeCameraMappingContext->MapKey(RuntimeToggleCameraAction, DefaultToggleCameraKey);
	}

	// higher priority than the template contexts
	Subsystem->AddMappingContext(RuntimeCameraMappingContext, 1);

	return RuntimeToggleCameraAction;
}

void AWARFRONTCharacter::ToggleCameraMode()
{
	SetCameraMode(IsFirstPerson() ? EWARFRONTCameraMode::ThirdPerson : EWARFRONTCameraMode::FirstPerson);
}

void AWARFRONTCharacter::SetCameraMode(EWARFRONTCameraMode NewMode)
{
	if (CameraMode == NewMode)
	{
		return;
	}

	// apply locally right away, then let the server replicate it to other players
	CameraMode = NewMode;
	ApplyCameraModeRotationSettings();

	if (!HasAuthority())
	{
		ServerSetCameraMode(NewMode);
	}
}

void AWARFRONTCharacter::ServerSetCameraMode_Implementation(EWARFRONTCameraMode NewMode)
{
	SetCameraMode(NewMode);
}

void AWARFRONTCharacter::OnRep_CameraMode()
{
	ApplyCameraModeRotationSettings();
}

void AWARFRONTCharacter::ApplyCameraModeRotationSettings()
{
	if (IsFirstPerson())
	{
		// the body faces where the camera looks
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		// restore the template orbit behavior
		bUseControllerRotationYaw = bThirdPersonUseControllerRotationYaw;
		GetCharacterMovement()->bOrientRotationToMovement = bThirdPersonOrientRotationToMovement;
	}
}

void AWARFRONTCharacter::UpdateCameraBlend(float DeltaTime)
{
	const float TargetAlpha = IsFirstPerson() ? 1.0f : 0.0f;

	if (CameraBlendAlpha == TargetAlpha)
	{
		return;
	}

	// ease towards the target and snap when close enough
	CameraBlendAlpha = FMath::FInterpTo(CameraBlendAlpha, TargetAlpha, DeltaTime, CameraBlendSpeed);

	if (FMath::IsNearlyEqual(CameraBlendAlpha, TargetAlpha, 0.001f))
	{
		CameraBlendAlpha = TargetAlpha;
	}

	CameraBoom->TargetArmLength = FMath::Lerp(ThirdPersonArmLength, 0.0f, CameraBlendAlpha);
	CameraBoom->SetRelativeLocation(FMath::Lerp(ThirdPersonBoomLocation, FirstPersonCameraOffset, CameraBlendAlpha));
	CameraBoom->SocketOffset = FMath::Lerp(ThirdPersonSocketOffset, FVector::ZeroVector, CameraBlendAlpha);
	CameraBoom->TargetOffset = FMath::Lerp(ThirdPersonTargetOffset, FVector::ZeroVector, CameraBlendAlpha);

	// hide the head only once the camera is almost inside it
	SetHeadHidden(IsFirstPerson() && CameraBlendAlpha > 0.9f);
}

void AWARFRONTCharacter::SetHeadHidden(bool bHidden)
{
	if (bHeadHidden == bHidden || GetMesh()->GetBoneIndex(HeadBoneName) == INDEX_NONE)
	{
		return;
	}

	// each machine has its own mesh, so this only affects the owning player's view
	if (bHidden)
	{
		GetMesh()->HideBoneByName(HeadBoneName, EPhysBodyOp::PBO_None);
	}
	else
	{
		GetMesh()->UnHideBoneByName(HeadBoneName);
	}

	bHeadHidden = bHidden;
}
