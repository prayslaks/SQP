// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyMenuWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameFramework/GameStateBase.h"

void ULobbyMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ULobbyMenuWidgetBase::UpdateWidget), 0.1, true, 0);
}

void ULobbyMenuWidgetBase::UpdateLobbyPlayerInfo()
{
	
}

void ULobbyMenuWidgetBase::UpdateWidget()
{
	NumOfPlayers->SetText(FText::FromString(FString::Printf(TEXT("%d"), GetWorld()->GetGameState()->PlayerArray.Num())));
}