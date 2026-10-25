// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WARFRONTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/** Camera perspective used by the player character */
UENUM(BlueprintType)
enum class EWARFRONTCameraMode : uint8
{
	ThirdPerson UMETA(DisplayName="Third Person"),
	FirstPerson UMETA(DisplayName="First Person")
};

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AWARFRONTCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Toggle Camera Input Action. If left empty, a runtime action mapped to DefaultToggleCameraKey is created */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ToggleCameraAction;

	/** Key used for the runtime toggle camera mapping when no ToggleCameraAction asset is assigned */
	UPROPERTY(EditAnywhere, Category="Input")
	FKey DefaultToggleCameraKey;

	/** Runtime toggle camera action, created when no asset is assigned */
	UPROPERTY(Transient)
	UInputAction* RuntimeToggleCameraAction;

	/** Runtime mapping context holding the toggle camera key */
	UPROPERTY(Transient)
	UInputMappingContext* RuntimeCameraMappingContext;

	/** Current camera perspective. Replicated so other players see the matching body rotation */
	UPROPERTY(ReplicatedUsing=OnRep_CameraMode, BlueprintReadOnly, Category="Camera")
	EWARFRONTCameraMode CameraMode = EWARFRONTCameraMode::ThirdPerson;

	/** Camera boom location relative to the capsule center in first person (roughly eye height) */
	UPROPERTY(EditAnywhere, Category="Camera")
	FVector FirstPersonCameraOffset = FVector(10.0f, 0.0f, 70.0f);

	/** How fast the camera blends between perspectives. Higher is faster */
	UPROPERTY(EditAnywhere, Category="Camera", meta = (ClampMin = "0.1"))
	float CameraBlendSpeed = 10.0f;

	/** Bone hidden for the owning player in first person so the head does not block the view */
	UPROPERTY(EditAnywhere, Category="Camera")
	FName HeadBoneName = TEXT("head");

	/** Blend between third person (0) and first person (1) */
	float CameraBlendAlpha = 0.0f;

	/** Whether the head bone is currently hidden */
	bool bHeadHidden = false;

	/** Third person camera and rotation settings captured after blueprint defaults are applied */
	float ThirdPersonArmLength = 0.0f;
	FVector ThirdPersonBoomLocation = FVector::ZeroVector;
	FVector ThirdPersonSocketOffset = FVector::ZeroVector;
	FVector ThirdPersonTargetOffset = FVector::ZeroVector;
	bool bThirdPersonOrientRotationToMovement = true;
	bool bThirdPersonUseControllerRotationYaw = false;

public:

	/** Constructor */
	AWARFRONTCharacter();

	/** Camera blending */
	virtual void Tick(float DeltaTime) override;

	/** Replicated properties */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	/** Captures the third person camera setup */
	virtual void PostInitializeComponents() override;

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Creates the runtime toggle camera action and mapping context for the local player */
	UInputAction* CreateDefaultToggleCameraInput();

	/** Applies the body rotation rules of the current camera mode */
	void ApplyCameraModeRotationSettings();

	/** Moves the camera towards the current camera mode */
	void UpdateCameraBlend(float DeltaTime);

	/** Hides or shows the head bone */
	void SetHeadHidden(bool bHidden);

	/** Asks the server to switch camera mode */
	UFUNCTION(Server, Reliable)
	void ServerSetCameraMode(EWARFRONTCameraMode NewMode);

	/** Camera mode replication handler */
	UFUNCTION()
	void OnRep_CameraMode();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Switches between third and first person */
	UFUNCTION(BlueprintCallable, Category="Camera")
	void ToggleCameraMode();

	/** Sets the camera mode locally and on the server */
	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetCameraMode(EWARFRONTCameraMode NewMode);

	/** Returns the current camera mode */
	UFUNCTION(BlueprintPure, Category="Camera")
	EWARFRONTCameraMode GetCameraMode() const { return CameraMode; }

	/** Returns true while in first person */
	UFUNCTION(BlueprintPure, Category="Camera")
	bool IsFirstPerson() const { return CameraMode == EWARFRONTCameraMode::FirstPerson; }

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

