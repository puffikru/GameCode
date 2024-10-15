// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GCBaseCharacter.generated.h"

class UGCBaseCharacterMovementComponent;

UCLASS(Abstract, NotBlueprintable)
class GAMECODE_API AGCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    AGCBaseCharacter(const FObjectInitializer& ObjectInitializer);
    
    virtual void MoveForward(float Value) {}
    virtual void MoveRight(float Value) {}
    virtual void Turn(float Value) {}
    virtual void LookUp(float Value) {}
    virtual void TurnAtRate(float Value) {}
    virtual void LookUpAtRate(float Value) {}

    virtual void ChangeCrouchState();

    virtual void StartSprint();
    virtual  void StopSprint();

    virtual void Tick(float DeltaSeconds) override;

    FORCEINLINE UGCBaseCharacterMovementComponent* GetBaseCharacterMovementComponent() const { return GCBaseCharacterMovementComponent; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character | IK settings")
    FName LeftFootSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character | IK settings")
    FName RightFootSocketName;
    
    float GetIKLeftFootOffset() const { return IKLeftFootOffset; }

    float GetIKRightFootOffset() const { return IKRightFootOffset; }
    
    float GetIKPelvisOffset() const { return IKPelvisOffset; }

    FRotator GetLeftFootRotation() const { return  LeftFootRotation; }

    FRotator GetRightFootRotation() const { return RightFootRotation; }
    
    virtual void Jump() override;

protected:
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintNativeEvent, Category="Character | Movement")
    void OnSprintStart();
    virtual void OnSprintStart_Implementation();
    
    UFUNCTION(BlueprintNativeEvent, Category="Character | Movement")
    void OnSprintEnd();
    virtual void OnSprintEnd_Implementation();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Controls")
    float BaseTurnRate = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Controls")
    float BaseLookUpRate = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Movement")
    float SprintSpeed = 800.0f;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Character | IK settings", meta=(ClampMin = 0.0f, UIMin = 0.0f))
    float IKInterpSpeed = 20.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character | IK settings", meta = (ClampMin = 0.0f, UIMin = 0.0f))
    float IKTraceDistance = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Movement")
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Movement")
    float StaminaRestoreVelocity = 25.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character | Movement")
    float SprintStaminaConsumptionVelocity = 25.0f;

    virtual bool CanSprint();
    
    void DrawDebugStamina();
    virtual bool CanJump();

    UGCBaseCharacterMovementComponent* GCBaseCharacterMovementComponent;

private:
    void TryChangeSprintState(float DeltaTime);
    float GetIKOffsetForASocket(const FName& SocketName) const;
    float GetIKOffsetForAPelvis() const;
    void UpdateIKSettings(float DeltaSeconds);
    FRotator GetFootRotation(const FName& SocketName) const;
    
    bool bIsSprintRequested = false;

    float IKLeftFootOffset = 0.0f;
    float IKRightFootOffset = 0.0f;
    float IKPelvisOffset = 0.0f;

    FRotator LeftFootRotation = FRotator::ZeroRotator;
    FRotator RightFootRotation = FRotator::ZeroRotator;

    float CurrentStamina = 0.0f;
    void UpdateStamina(float DeltaSeconds);
};
