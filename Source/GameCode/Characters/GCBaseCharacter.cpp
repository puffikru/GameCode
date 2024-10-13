// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/MovementComponents/GCBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
    UpdateIKSettings(DeltaSeconds);
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
float AGCBaseCharacter::GetIKOffsetForASocket(const FName& SocketName) const
{
    float Result = 0.0f;

    float CapsuleHalfHight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    const FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
    const FVector TraceStart(SocketLocation.X, SocketLocation.Y, GetActorLocation().Z);
    const FVector TraceEnd = TraceStart - (CapsuleHalfHight + IKTraceDistance) * FVector::UpVector;

    FHitResult HitResult;
    const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
    const FVector FootSizeBox = FVector(1.0f, 15.0f, 7.0f);

    if (UKismetSystemLibrary::BoxTraceSingle(GetWorld(), TraceStart, TraceEnd, FootSizeBox, GetMesh()->GetSocketRotation(SocketName),
            TraceType, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true))
    {
        float CharacterBottom = TraceStart.Z - CapsuleHalfHight;
        Result = CharacterBottom - HitResult.Location.Z;
    }

    return Result;
}
float AGCBaseCharacter::GetIKOffsetForAPelvis() const
{
    return IKRightFootOffset > IKLeftFootOffset ? -IKRightFootOffset : -IKLeftFootOffset;
}
void AGCBaseCharacter::UpdateIKSettings(float DeltaSeconds)
{
    IKLeftFootOffset = FMath::FInterpTo(IKLeftFootOffset, GetIKOffsetForASocket(LeftFootSocketName), DeltaSeconds, IKInterpSpeed);
    IKRightFootOffset = FMath::FInterpTo(IKRightFootOffset, GetIKOffsetForASocket(RightFootSocketName), DeltaSeconds, IKInterpSpeed);
    IKPelvisOffset = FMath::FInterpTo(IKPelvisOffset, GetIKOffsetForAPelvis(), DeltaSeconds, IKInterpSpeed);
}