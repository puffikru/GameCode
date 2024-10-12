// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MovementComponents/GCBaseCharacterMovementComponent.h"

float UGCBaseCharacterMovementComponent::GetMaxSpeed() const
{
    float Result = Super::GetMaxSpeed();
    if (bIsSprinting)
    {
        Result = SprintSpeed;
    }
    return Result;
}
void UGCBaseCharacterMovementComponent::StartSprint()
{
    bIsSprinting = true;
    bForceMaxAccel = 1;
}
void UGCBaseCharacterMovementComponent::StopSprint()
{
    bIsSprinting = false;
    bForceMaxAccel = 0;
}