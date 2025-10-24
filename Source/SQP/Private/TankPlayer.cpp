// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayer.h"


ATankPlayer::ATankPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ATankPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

