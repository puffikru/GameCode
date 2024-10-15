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

    bool IsOutOfStamina() const { return bIsOutOfStamina; }
    void SetIsOutOfStamina(bool bIsOutOfStamina_In) { bIsOutOfStamina = bIsOutOfStamina_In; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Movement | Sprint", meta=(ClampMin = 0.0f, UIMin = 0.0f))
    float SprintSpeed = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Movement | Stamina", meta=(ClampMin = 0.0f, UIMin = 0.0f))
    float OutOfStaminaSpeed = 300.0f;
    
private:
    bool bIsSprinting = false;
    bool bIsOutOfStamina = false;
};
