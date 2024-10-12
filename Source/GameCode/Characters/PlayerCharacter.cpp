// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint arm"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->bUsePawnControlRotation = false;

    GetCharacterMovement()->bOrientRotationToMovement = 1;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}
void APlayerCharacter::MoveForward(float Value)
{
    Super::MoveForward(Value);
    if (!FMath::IsNearlyZero(Value, 1e-6f))
    {
        FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
        FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
        // AddMovementInput(GetActorForwardVector(), Value);
        AddMovementInput(ForwardVector, Value);
    }
}
void APlayerCharacter::MoveRight(float Value)
{
    Super::MoveRight(Value);
    if (!FMath::IsNearlyZero(Value, 1e-6f))
    {
        FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
        FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
        // AddMovementInput(GetActorRightVector(), Value);
        AddMovementInput(RightVector, Value);
    }
}
void APlayerCharacter::Turn(float Value)
{
    Super::Turn(Value);
    AddControllerYawInput(Value);
}
void APlayerCharacter::LookUp(float Value)
{
    Super::LookUp(Value);
    AddControllerPitchInput(Value);
}
void APlayerCharacter::TurnAtRate(float Value)
{
    Super::TurnAtRate(Value);
    AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void APlayerCharacter::LookUpAtRate(float Value)
{
    Super::LookUpAtRate(Value);
    AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    SpringArmComponent->TargetOffset += FVector(0.0f, 0.0f, HalfHeightAdjust);
}
void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    SpringArmComponent->TargetOffset -= FVector(0.0f, 0.0f, HalfHeightAdjust);
}
bool APlayerCharacter::CanJumpInternal_Implementation() const
{
    return bIsCrouched || Super::CanJumpInternal_Implementation();
    
}
void APlayerCharacter::OnJumped_Implementation()
{
    Super::OnJumped_Implementation();
    if (bIsCrouched)
    {
        UnCrouch();
    }
}