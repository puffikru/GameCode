// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GCBaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMECODE_API APlayerCharacter : public AGCBaseCharacter
{
	GENERATED_BODY()

public:
    APlayerCharacter();
    
    virtual void MoveForward(float Value) override;
    virtual void MoveRight(float Value) override;
    virtual void Turn(float Value) override;
    virtual void LookUp(float Value) override;
    virtual void TurnAtRate(float Value) override;
    virtual void LookUpAtRate(float Value) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character | Camera")
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character | Camera")
    class USpringArmComponent* SpringArmComponent;
};
