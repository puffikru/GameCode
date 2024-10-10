// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/GCBaseCharacterAnimInstance.h"
#include "../GCBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGCBaseCharacterAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    checkf(TryGetPawnOwner()->IsA<AGCBaseCharacter>(),
        TEXT("UGCBaseCharacterAnimInstance::NativeBeginPlay() UGCBaseCharacterAnimInstance can be use only with AGCBaseCharacter"));
    CachedBaseCharacter = StaticCast<AGCBaseCharacter*>(TryGetPawnOwner());
}
void UGCBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!CachedBaseCharacter.IsValid())
    {
        return;
    }

    UCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetCharacterMovement();
    Speed = CharacterMovement->Velocity.Size();
    bIsFalling = CharacterMovement->IsFalling();
    bIsCrouching = CharacterMovement->IsCrouching();
}