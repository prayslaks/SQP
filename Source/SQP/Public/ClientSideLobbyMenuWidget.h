// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClientSideLobbyMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SQP_API UClientSideLobbyMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumOfPlayers;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ReadyButton;
};
