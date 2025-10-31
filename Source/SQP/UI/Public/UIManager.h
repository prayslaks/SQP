// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS()
class SQP_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UUIManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	TSubclassOf<UUserWidget> MainUIClass;
	UPROPERTY()
	TObjectPtr<class UMainUI> MainUI;
	
	UPROPERTY(meta=(BindWidget))
	TSubclassOf<class UUserWidget> TimerUIClass;
	
public:
	UMainUI* CreateMainUI();
	class USlider* GetSliderUI();
	FLinearColor GetCurrentColor();

	class UTimerUI* CreateTimerUI();
};
