// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TankAnim.generated.h"

/**
 * 
 */
UCLASS()
class SQP_API UTankAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	TObjectPtr<class ATankCharacter> Owner;
	UPROPERTY()
	TObjectPtr<class UCameraComponent> FollowCam;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	FRotator TurretRotation = FRotator(0, 0, 0);

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
