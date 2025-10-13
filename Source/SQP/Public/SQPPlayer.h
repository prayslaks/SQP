// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQPCharacter.h"
#include "SQPPlayer.generated.h"

UCLASS()
class SQP_API ASQPPlayer : public ASQPCharacter
{
	GENERATED_BODY()

public:
	ASQPPlayer();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
