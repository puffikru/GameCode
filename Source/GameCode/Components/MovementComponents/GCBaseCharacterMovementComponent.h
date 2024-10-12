// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GCBaseCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API UGCBaseCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    FORCEINLINE bool IsSprinting() const { return bIsSprinting; }
    virtual float GetMaxSpeed() const override;

    void StartSprint();
    void StopSprint();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character movement: sprint", meta=(ClampMin = 0.0f, UIMin = 0.0f))
    float SprintSpeed = 1200.0f;
    
private:
    bool bIsSprinting;
};
