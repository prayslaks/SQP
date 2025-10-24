// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQPCharacter.h"
#include "TankPlayer.generated.h"

UCLASS()
class SQP_API ATankPlayer : public ASQPCharacter
{
	GENERATED_BODY()

public:
	ATankPlayer();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
