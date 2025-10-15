// Fill out your copyright notice in the Description page of Project Settings.

#include "HostSideLobbyMenuWidget.h"

#include "HostSideLobbyPlayerInfoWidget.h"
#include "Components/VerticalBox.h"

UHostSideLobbyMenuWidget::UHostSideLobbyMenuWidget()
{
	if (static ConstructorHelpers::FClassFinder<UUserWidget>
	Finder(TEXT("/Game/Splatoon/Blueprint/LobbyLevel/WBP_HostSideLobbyPlayerInfoWidget.WBP_HostSideLobbyPlayerInfoWidget_C"));
	Finder.Succeeded())
	{
		PlayerInfoWidgetClass = Finder.Class;	
	}
}

void UHostSideLobbyMenuWidget::UpdateWidget()
{
	Super::UpdateWidget();

}
