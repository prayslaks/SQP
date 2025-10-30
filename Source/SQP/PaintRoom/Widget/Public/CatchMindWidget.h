// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CatchMindWidget.generated.h"

class UTextBlock;

UCLASS()
class SQP_API UCatchMindWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void HideAll() const;

	UFUNCTION()
	void ShowPainter() const;

	UFUNCTION()
	void ShowParticipant() const;

	UFUNCTION()
	void SetSuggestionText(const FString& Suggestion) const;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PainterRoleTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ParticipantRoleTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SuggestionTitleTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SuggestionTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TimerTextBlock;
};