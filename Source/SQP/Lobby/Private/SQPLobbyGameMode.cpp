// Fill out your copyright notice in the Description page of Project Settings.

#include "SQPLobbyGameMode.h"
#include "SQP.h"
#include "SQPPlayerController.h"
#include "SQPPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameStateBase.h"

ASQPLobbyGameMode::ASQPLobbyGameMode()
{
	if (static ConstructorHelpers::FClassFinder<ASQPPlayerController>
		Finder(TEXT("/Game/Splatoon/Blueprint/Lobby/BP_SQPPlayerController.BP_SQPPlayerController_C"));
		Finder.Succeeded())
	{
		PlayerControllerClass = Finder.Class;
	}

	if (static ConstructorHelpers::FClassFinder<ASQPPlayerState>
		Finder(TEXT("/Game/Splatoon/Blueprint/Lobby/BP_SQPPlayerState.BP_SQPPlayerState_C"));
		Finder.Succeeded())
	{
		PlayerStateClass = Finder.Class;
	}
}

void ASQPLobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASQPLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PRINTLOGNET(TEXT("Lobby PostLogin Start!"));

	//정상 상황이라면 이 캐스팅은 성공해야 한다
	ASQPPlayerController* PC = Cast<ASQPPlayerController>(NewPlayer);
	if (PC == nullptr)
	{
		return;
	}

	//전송할 위젯 선택
	TSubclassOf<UUserWidget> WidgetToShow = nullptr;
	
	if (GetNetMode() != NM_DedicatedServer && PC->IsLocalController())
	{
		//리슨 서버 측 클라이언트
		WidgetToShow = ServerSideLobbyMenuWidgetClass;
	}
	else
	{
		//외부 클라이언트
		WidgetToShow = ClientSideLobbyMenuWidgetClass;
	}

	//클라이언트에 지정한 위젯을 생성해서 보여주도록 명령
	PC->Client_CreateClientSideLobbyWidget(WidgetToShow);

	PRINTLOGNET(TEXT("Lobby PostLogin End!"));
}

void ASQPLobbyGameMode::OnPlayerReadyStateChanged()
{
	CheckAllPlayersReady();
}

void ASQPLobbyGameMode::CheckAllPlayersReady()
{
	//최소 시작 인원
	constexpr int32 MinPlayersToStart = 2;

	//최소 인원 미달
	if (GetWorld()->GetGameState()->PlayerArray.Num() < MinPlayersToStart)
	{
		return;
	}

	//초기값
	bool bAllPlayersReady = true;

	//게임 스테이트의 플레이어 목록을 순회
	for (APlayerState* PS : GetWorld()->GetGameState()->PlayerArray)
	{
		//한 명이라도 준비가 안됐거나 캐스팅 실패 시 false
		ASQPPlayerState* MyPS = Cast<ASQPPlayerState>(PS);
		if (!MyPS || !MyPS->IsReady())
		{
			bAllPlayersReady = false;
			break;
		}
	}

	if (bAllPlayersReady)
	{
		// 모든 플레이어 준비 완료! 메인 게임 맵으로 이동
		if (UWorld* World = GetWorld())
		{
			// bAbsolute 옵션을 false로 하여 ?listen 같은 옵션을 유지하지 않도록 함
			World->ServerTravel("/Game/Maps/MainGameMap", false);
		}
	}
}