// Copyright Epic Games, Inc. All Rights Reserved.


#include "SQPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "HostSideLobbyMenuWidget.h"
#include "SQP.h"
#include "SQPLobbyGameMode.h"
#include "SQPPlayerState.h"
#include "Blueprint/UserWidget.h"

class ASQPPlayerState;

void ASQPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}

void ASQPPlayerController::RequestSetReadyState(bool bNewReadyState)
{
	// 서버 RPC 호출
	Server_SetReadyState(bNewReadyState);
}

void ASQPPlayerController::Client_CreateLobbyWidget_Implementation(const TSubclassOf<UUserWidget> WidgetToShow)
{
	PRINTLOGNET(TEXT("Client RPC CreateLobbyWidget Start!"));
	
	//뷰포트에 전달받은 위젯 클래스의 인스턴스를 생성하여 추가
	LobbyMenuWidget = Cast<ULobbyMenuWidgetBase>(CreateWidget(GetWorld(), WidgetToShow));
	LobbyMenuWidget->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	
	PRINTLOGNET(TEXT("Client RPC CreateLobbyWidget End!"));
}

void ASQPPlayerController::Client_UpdateReadyStatusInUI_Implementation(bool bIsReady)
{
	// 여기에 위젯(UI)의 모습을 변경하는 코드를 작성
	// 예: if(LobbyWidget) LobbyWidget->SetPlayerReadyIndicator(bIsReady);
}

void ASQPPlayerController::Server_SetReadyState_Implementation(const bool Value)
{
	if (HasAuthority())
	{
		//자신의 플레이어 스테이트에 접근하여 변경
		if (ASQPPlayerState* PS = GetPlayerState<ASQPPlayerState>())
		{
			PS->SetReadyState(Value);
		}	
	}
}