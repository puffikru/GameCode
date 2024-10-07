// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GameCodeBasePawn.h"

#include "Components/SphereComponent.h"
#include "Components/MovementComponents/GCBasePawnMovementComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogCameras, Log, All)

// Sets default values
AGameCodeBasePawn::AGameCodeBasePawn()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
    CollisionComponent->SetSphereRadius(50.0f);
    CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
    SetRootComponent(CollisionComponent);

    // MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("Movement Component"));
    MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UGCBasePawnMovementComponent>(TEXT("Movement Component"));
    MovementComponent->SetUpdatedComponent(CollisionComponent);
}

// Called to bind functionality to input
void AGameCodeBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("MoveForward", this, &AGameCodeBasePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AGameCodeBasePawn::MoveRight);
    PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AGameCodeBasePawn::Jump);
}
void AGameCodeBasePawn::MoveForward(float Value)
{
    InputForward = Value;
    if (Value != 0.0f)
    {
        AddMovementInput(CurrentViewActor->GetActorForwardVector(), Value);
    }
}
void AGameCodeBasePawn::MoveRight(float Value)
{
    InputRight = Value;
    if (Value != 0.0f)
    {
        AddMovementInput(CurrentViewActor->GetActorRightVector(), Value);
    }
}
void AGameCodeBasePawn::Jump()
{
    checkf(MovementComponent->IsA<UGCBasePawnMovementComponent>(), TEXT("AGameCodeBasePawn::Jump() Jump can work only with UGCBasePawnMovementComponent"));
    UGCBasePawnMovementComponent* BasePawnMovementComponent = StaticCast<UGCBasePawnMovementComponent*>(MovementComponent);
    BasePawnMovementComponent->JumpStart();
}
void AGameCodeBasePawn::BeginPlay()
{
    Super::BeginPlay();

    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (!CameraManager)
        return;
    CurrentViewActor = CameraManager->GetViewTarget();
    CameraManager->OnBlendComplete().AddUFunction(this, FName("OnBlendComplete"));
}
void AGameCodeBasePawn::OnBlendComplete()
{
    CurrentViewActor = GetController()->GetViewTarget();
    UE_LOG(LogCameras, Log, TEXT("AGameCodeBasePawn::OnBlendComplete() Current view actor: %s"), *CurrentViewActor->GetName());
}

 