// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GCBaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMECODE_API UGCBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character animation")
    float Speed = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character animation")
    bool bIsFalling = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character animation")
    bool bIsCrouching = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character animation")
    bool bIsSprinting = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character animation")
    bool bIsOutOfStamina = false;

    UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category="Character | IK settings")
    FVector LeftFootEffectorLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category="Character | IK settings")
    FVector RightFootEffectorLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category="Character | IK settings")
    FVector IKPelvisOffset = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category="Character | IK settings")
    FRotator RightFootRotation = FRotator::ZeroRotator;

    UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, Category="Character | IK settings")
    FRotator LeftFootRotation = FRotator::ZeroRotator;

private:
    TWeakObjectPtr<class AGCBaseCharacter> CachedBaseCharacter;
};
