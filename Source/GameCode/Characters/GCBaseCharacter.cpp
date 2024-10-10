// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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