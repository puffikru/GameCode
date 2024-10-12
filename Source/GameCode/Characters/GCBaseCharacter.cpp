// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCBaseCharacter.h"

#include "Components/MovementComponents/GCBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGCBaseCharacter::AGCBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGCBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    GCBaseCharacterMovementComponent = StaticCast<UGCBaseCharacterMovementComponent*>(GetCharacterMovement());
}

void AGCBaseCharacter::ChangeCrouchState()
{
    if (GetCharacterMovement()->IsCrouching())
    {
        UnCrouch();
    }
    else
    {
        Crouch();
    }
}

void AGCBaseCharacter::StartSprint()
{
    bIsSprintRequested = true;
    if (bIsCrouched)
    {
        UnCrouch();
    }
}

void AGCBaseCharacter::StopSprint()
{
    bIsSprintRequested = false;
}

void AGCBaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    TryChangeSprintState();
}
void AGCBaseCharacter::OnSprintStart_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("AGCBaseCharacter::OnSprintStart_Implementation()"));
}
void AGCBaseCharacter::OnSprintEnd_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("AGCBaseCharacter::OnSprintEnd_Implementation()"));
}

bool AGCBaseCharacter::CanSprint()
{
    return true;
}

void AGCBaseCharacter::TryChangeSprintState()
{
    if (bIsSprintRequested && !GCBaseCharacterMovementComponent->IsSprinting() && CanSprint())
    {
        GCBaseCharacterMovementComponent->StartSprint();
        OnSprintStart();
    }

    if (!bIsSprintRequested && GCBaseCharacterMovementComponent->IsSprinting())
    {
        GCBaseCharacterMovementComponent->StopSprint();
        OnSprintEnd();
    }
}