// Fill out your copyright notice in the Description page of Project Settings.


#include "SQPGameState.h"

#include "LobbyMenuWidgetBase.h"
#include "SQP.h"
#include "SQPLobbyGameMode.h"
#include "SQPPaintWorldSubsystem.h"
#include "SQPPlayerController.h"
#include "Net/UnrealNetwork.h"

void ASQPGameState::Multicast_PaintRenderTarget_Implementation(const FVector Start, const FVector End, const uint8 BrushIndex, const float BrushSize)
{
	if (const auto Subsystem = GetWorld()->GetSubsystem<USQPPaintWorldSubsystem>())
	{
		Subsystem->TryPaint(Start, End, BrushIndex, BrushSize);
	}
}

void ASQPGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASQPGameState, ExistingPlayerInfoArray);	
}

void ASQPGameState::OnRep_ExistingPlayerInfoArray()
{
	PRINTLOGNET(TEXT("Replicated New PlayerInfo"));

	Multicast_UpdatePlayerInfoBox();
}

void ASQPGameState::Multicast_UpdatePlayerInfoBox_Implementation()
{
	PRINTLOGNET(TEXT("Receive UpdatePlayerInfoBox!"));

	Cast<ASQPPlayerController>(GetWorld()->GetFirstPlayerController())->LobbyMenuWidget->UpdateLobbyPlayerInfo();
	
}