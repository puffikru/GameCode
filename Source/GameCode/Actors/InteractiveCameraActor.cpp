// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractiveCameraActor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

AInteractiveCameraActor::AInteractiveCameraActor()
{
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Interaction volume"));
    BoxComponent->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
    BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    BoxComponent->SetupAttachment(GetRootComponent());
}
void AInteractiveCameraActor::BeginPlay()
{
    Super::BeginPlay();
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveCameraActor::OnBeginOverlap);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractiveCameraActor::OnEndOverlap);
}
void AInteractiveCameraActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FViewTargetTransitionParams TransitionToCameraParams;
    TransitionToCameraParams.BlendTime = TransitionToCameraTime;
    if (PlayerController)
    {
        PlayerController->SetViewTarget(this, TransitionToCameraParams);
    }
}
void AInteractiveCameraActor::OnEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FViewTargetTransitionParams TransitionToPawnParams;
    TransitionToPawnParams.BlendTime = TransitionToPawnTime;
    TransitionToPawnParams.bLockOutgoing = true; // чтобы при переходе не было глитчей
    if (PlayerController)
    {
        APawn* Pawn = PlayerController->GetPawn();
        PlayerController->SetViewTarget(Pawn, TransitionToPawnParams);
    }
}