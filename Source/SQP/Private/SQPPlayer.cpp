// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/SQPPlayer.h"

ASQPPlayer::ASQPPlayer()
{
	//틱 활성화
	PrimaryActorTick.bCanEverTick = true;
}

void ASQPPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ASQPPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASQPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}