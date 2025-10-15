// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientSideLobbyMenuWidget.h"
#include "SQPPlayerController.h"
#include "ToggleButton.h"
#include "Components/Button.h"

UClientSideLobbyMenuWidget::UClientSideLobbyMenuWidget()
{
	if (static ConstructorHelpers::FClassFinder<UUserWidget>
	Finder(TEXT("/Game/Splatoon/Blueprint/LobbyLevel/WBP_ClientSideLobbyPlayerInfoWidget.WBP_ClientSideLobbyPlayerInfoWidget_C"));
	Finder.Succeeded())
	{
		PlayerInfoWidgetClass = Finder.Class;	
	}
}

void UClientSideLobbyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReadyButton->OnToggleStateChanged.AddDynamic(this, &UClientSideLobbyMenuWidget::OnReadyButtonClicked);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UClientSideLobbyMenuWidget::OnReadyButtonClicked(const bool Value)
{
	Cast<ASQPPlayerController>(GetWorld()->GetFirstPlayerController())->Server_SetReadyState(Value);
	
}