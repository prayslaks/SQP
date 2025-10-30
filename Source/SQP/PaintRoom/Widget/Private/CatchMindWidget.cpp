// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchMindWidget.h"

#include "Components/TextBlock.h"

void UCatchMindWidget::HideAll() const
{
	PainterRoleTextBlock->SetVisibility(ESlateVisibility::Hidden);
	ParticipantRoleTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SuggestionTitleTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SuggestionTextBlock->SetVisibility(ESlateVisibility::Hidden);
	TimerTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UCatchMindWidget::ShowPainter() const
{
	PainterRoleTextBlock->SetVisibility(ESlateVisibility::Visible);
	ParticipantRoleTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SuggestionTitleTextBlock->SetVisibility(ESlateVisibility::Visible);
	SuggestionTextBlock->SetVisibility(ESlateVisibility::Visible);
	TimerTextBlock->SetVisibility(ESlateVisibility::Visible);
}

void UCatchMindWidget::ShowParticipant() const
{
	PainterRoleTextBlock->SetVisibility(ESlateVisibility::Hidden);
	ParticipantRoleTextBlock->SetVisibility(ESlateVisibility::Visible);
	SuggestionTitleTextBlock->SetVisibility(ESlateVisibility::Visible);
	SuggestionTextBlock->SetVisibility(ESlateVisibility::Visible);
	TimerTextBlock->SetVisibility(ESlateVisibility::Visible);
}

void UCatchMindWidget::SetSuggestionText(const FString& Suggestion) const
{
	SuggestionTextBlock->SetText(FText::FromString(Suggestion));
}