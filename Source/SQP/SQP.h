// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Shared/FLogWriter.h"

// 일반 디버깅 로그 카테고리 선언
DECLARE_LOG_CATEGORY_EXTERN(SQP, Log, All);

// 글로벌 로그 객체 접근자
inline FLogWriter& GetLogWriter() { return FLogWriter::Get(); }

// 현재 함수와 라인 정보를 문자열로
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// 간단한 디버깅용 호출 위치 로그
#define PRINTINFO() UE_LOG(SQP, Warning, TEXT("%s"), *CALLINFO)

// 로그 + 파일 출력
#define PRINTLOG(fmt, ...) \
do { \
const FString __LogMessage__ = FString::Printf(fmt, ##__VA_ARGS__); \
const FString __FullMessage__ = FString::Printf(TEXT("%s : %s"), *CALLINFO, *__LogMessage__); \
UE_LOG(SQP, Warning, TEXT("%s"), *__FullMessage__); \
GetLogWriter().WriteLog(__FullMessage__); \
} while(0)

// 화면 출력 + 로그
#define PRINT_STRING(fmt, ...) \
do { \
const FString __msg__ = FString::Printf(fmt, ##__VA_ARGS__); \
const FString __FullMessage__ = FString::Printf(TEXT("%s : %s"), *CALLINFO, *__msg__); \
UE_LOG(SQP, Warning, TEXT("%s"), *__FullMessage__); \
GetLogWriter().WriteLog(__FullMessage__); \
if (GEngine) { \
GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, __msg__); \
} \
} while(0)

// 네트워크 디버깅 로그 카테고리 선언
DECLARE_LOG_CATEGORY_EXTERN(SQPNET, Log, All);

// 네트워크 정보를 문자열로
#define NETMODEINFO \
((GetNetMode() == NM_Client) ? *FString::Printf(TEXT("CLIENT %d"), UE::GetPlayInEditorID()) \
: ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))

// 간단한 디버깅용 호출 위치 로그
#define PRINTINFONET() UE_LOG(SQPNET, Warning, TEXT("[%s] %s"), NETMODEINFO, *CALLINFO)

// 로그 + 파일 출력
#define PRINTLOGNET(fmt, ...) \
do { \
const FString __NetMessage__ = FString(NETMODEINFO); \
const FString __LogMessage__ = FString::Printf(fmt, ##__VA_ARGS__); \
const FString __FullMessage__ = FString::Printf(TEXT("[%s] %s : %s"), *__NetMessage__, *CALLINFO, *__LogMessage__); \
UE_LOG(SQPNET, Warning, TEXT("%s"), *__FullMessage__); \
GetLogWriter().WriteLog(__FullMessage__); \
} while(0)