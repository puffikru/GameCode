// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/GCBaseCharacterAnimInstance.h"
#include "../GCBaseCharacter.h"
#include "../../Components/MovementComponents/GCBaseCharacterMovementComponent.h"

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

    UGCBaseCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetBaseCharacterMovementComponent();
    Speed = CharacterMovement->Velocity.Size();
    bIsFalling = CharacterMovement->IsFalling();
    bIsCrouching = CharacterMovement->IsCrouching();
    bIsSprinting = CharacterMovement->IsSprinting();
    bIsOutOfStamina = CharacterMovement->IsOutOfStamina();

    LeftFootEffectorLocation = FVector((CachedBaseCharacter->GetIKLeftFootOffset() + CachedBaseCharacter->GetIKPelvisOffset()) * -1, 0.0f, 0.0f);
    RightFootEffectorLocation = FVector(CachedBaseCharacter->GetIKRightFootOffset() + CachedBaseCharacter->GetIKPelvisOffset(), 0.0f, 0.0f);
    IKPelvisOffset = FVector(0.0f, 0.0f, CachedBaseCharacter->GetIKPelvisOffset());
    LeftFootRotation = CachedBaseCharacter->GetLeftFootRotation();
    RightFootRotation = CachedBaseCharacter->GetRightFootRotation();
}