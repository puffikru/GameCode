// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/GCBasePawnAnimInstance.h"
#include "../GameCodeBasePawn.h"
#include "GameFramework/PawnMovementComponent.h"

void UGCBasePawnAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    checkf(TryGetPawnOwner()->IsA<AGameCodeBasePawn>(),
        TEXT("UGCBasePawnAnimInstance::NativeBeginPlay() only GameCodeBasePawn can work with"));
    CachedBasePawn = StaticCast<AGameCodeBasePawn*>(TryGetPawnOwner());
}
void UGCBasePawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!CachedBasePawn.IsValid())
    {
        return;
    }

    InputForward = CachedBasePawn->GetInputForward();
    InputRight = CachedBasePawn->GetInputRight();
    bIsInAir = CachedBasePawn->GetMovementComponent()->IsFalling();
}