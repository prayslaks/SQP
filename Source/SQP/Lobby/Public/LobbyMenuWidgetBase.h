// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenuWidgetBase.generated.h"

class UVerticalBox;
class UTextBlock;

UCLASS()
class SQP_API ULobbyMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumOfPlayers;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> PlayerInfoBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerInfoWidgetClass;

	UFUNCTION()
	void UpdateLobbyPlayerInfo();

	UFUNCTION()
	virtual void UpdateWidget();
};
