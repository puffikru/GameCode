// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/GCPlayerController.h"

#include "Characters/GCBaseCharacter.h"

void AGCPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    CachedBaseCharacter = Cast<AGCBaseCharacter>(InPawn);
}
void AGCPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAxis("MoveForward", this, &AGCPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AGCPlayerController::MoveRight);
    InputComponent->BindAxis("Turn", this, &AGCPlayerController::Turn);
    InputComponent->BindAxis("LookUp", this, &AGCPlayerController::LookUp);
    InputComponent->BindAxis("TurnAtRate", this, &AGCPlayerController::TurnAtRate);
    InputComponent->BindAxis("LookUpAtRate", this, &AGCPlayerController::LookUpAtRate);
    InputComponent->BindAction("Jump", IE_Pressed, this, &AGCPlayerController::Jump);
    InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AGCPlayerController::ChangeCrouchState);
}
void AGCPlayerController::MoveForward(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->MoveForward(Value);
    }
}
void AGCPlayerController::MoveRight(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->MoveRight(Value);
    }
}
void AGCPlayerController::Turn(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->Turn(Value);
    }
}
void AGCPlayerController::LookUp(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->LookUp(Value);
    }
}
void AGCPlayerController::TurnAtRate(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->TurnAtRate(Value);
    }
}
void AGCPlayerController::LookUpAtRate(float Value)
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->LookUpAtRate(Value);
    }
}
void AGCPlayerController::ChangeCrouchState()
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->ChangeCrouchState();
    }
}
void AGCPlayerController::Jump()
{
    if (CachedBaseCharacter.IsValid())
    {
        CachedBaseCharacter->Jump();
    }
}