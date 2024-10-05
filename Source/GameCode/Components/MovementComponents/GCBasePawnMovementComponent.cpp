// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MovementComponents/GCBasePawnMovementComponent.h"

void UGCBasePawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    if (ShouldSkipUpdate(DeltaTime))
        return;
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const FVector PendingInput = GetPendingInputVector().GetClampedToMaxSize(1.0f);
    Velocity = PendingInput * MaxSpeed;
    ConsumeInputVector();

    if (bEnableGravity)
    {
        FHitResult HitResult;
        FVector StartPoint = UpdatedComponent->GetComponentLocation();
        float LineTraceLength = 50.0f + GetGravityZ() * DeltaTime;
        FVector EndPoint = StartPoint - LineTraceLength * FVector::UpVector;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());

        bool bWasFalling = bIsFalling;
        bIsFalling = !GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, CollisionParams);
        if (bIsFalling)
        {
            VerticalVelocity += GetGravityZ() * FVector::UpVector * DeltaTime;
            Velocity += VerticalVelocity;
        }
        else if (bWasFalling)
        {
            VerticalVelocity = FVector::ZeroVector;
        }
    }

    const FVector Delta = Velocity * DeltaTime;
    if (!Delta.IsNearlyZero(1e-6f))
    {
        const FQuat Rot = UpdatedComponent->GetComponentQuat();
        FHitResult Hit(1.f);
        SafeMoveUpdatedComponent(Delta, Rot, true, Hit);

        if (Hit.IsValidBlockingHit())
        {
            HandleImpact(Hit, DeltaTime, Delta);
            // Try to slide the remaining distance along the surface.
            SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
        }
        MoveUpdatedComponent(Delta, Rot, true);
    }
    UpdateComponentVelocity();
}
void UGCBasePawnMovementComponent::JumpStart()
{
    VerticalVelocity = InitialJumpVelocity * FVector::UpVector;
}