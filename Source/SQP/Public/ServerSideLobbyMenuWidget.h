// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerSideLobbyMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SQP_API UServerSideLobbyMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumOfPlayers;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StartButton;
};