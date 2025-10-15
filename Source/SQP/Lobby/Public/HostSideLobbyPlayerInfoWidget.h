// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HostSideLobbyPlayerInfoWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class SQP_API UHostSideLobbyPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NameTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> KickButton;
};
