// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQP_PS_ComponentBase.h"
#include "Components/ActorComponent.h"
#include "SQP_PS_PaintRoomComponent.generated.h"

UENUM(BlueprintType)
enum class EPaintRoomRole : uint8
{
	None = 0,
	CatchMindPainter = 1,
	CatchMindParticipant = 2,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SQP_API USQP_PS_PaintRoomComponent : public USQP_PS_ComponentBase
{
	GENERATED_BODY()

public:
	USQP_PS_PaintRoomComponent();
	
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//이 유저가 선택한 브러시 색상
	UPROPERTY()
	FLinearColor SelectedColor;

	//이 유저가 선택한 브러시 크기
	UPROPERTY()
	float SelectedBrushSize;

	UFUNCTION()
	void IncreaseLikeCounter();

	UPROPERTY(ReplicatedUsing=OnRep_LikeCounter)
	int32 LikeCounter = 0;
	
	UFUNCTION()
	void OnRep_LikeCounter() const;

	//페인트 볼 발사 가능 여부 프로퍼티
	__declspec(property(get=GetCanFirePaintBall, put=SetCanFirePaintBall)) bool CAN_FIRE_PAINT_BALL;
	UFUNCTION()
	FORCEINLINE bool GetCanFirePaintBall() const { return bCanFirePaintBall; }
	UFUNCTION()
	FORCEINLINE void SetCanFirePaintBall(const bool Value)
	{
		bCanFirePaintBall = Value;
		OnRep_bCanFirePaintBall();
	}

	//페인트 룸 역할 프로퍼티
	__declspec(property(get=GetPaintRoomRole, put=SetPaintRoomRole)) EPaintRoomRole PAINT_ROOM_ROLE;
	UFUNCTION()
	FORCEINLINE EPaintRoomRole GetPaintRoomRole() const { return PaintRoomRole; }
	UFUNCTION()
	FORCEINLINE void SetPaintRoomRole(const EPaintRoomRole Value)
	{
		PaintRoomRole = Value;
		OnRep_PaintRoomRole();

		switch (PaintRoomRole)
		{
		case EPaintRoomRole::None:
			{
				CAN_FIRE_PAINT_BALL = true;
				break;
			}
		case EPaintRoomRole::CatchMindPainter:
			{
				CAN_FIRE_PAINT_BALL = true;
				break;
			}
		case EPaintRoomRole::CatchMindParticipant:
			{
				CAN_FIRE_PAINT_BALL = false;
				break;
			}
		default:
			{
				CAN_FIRE_PAINT_BALL = true;
				break;
			}
		}	
	}

protected:
	//이 유저의 페인트 볼 발사 가능 여부
	UPROPERTY(ReplicatedUsing=OnRep_bCanFirePaintBall)
	bool bCanFirePaintBall;

	//페인트 볼 발사 가능 여부 리플리케이션 콜백
	UFUNCTION()
	void OnRep_bCanFirePaintBall();

	//이 유저의 페인트 룸 역할
	UPROPERTY(ReplicatedUsing=OnRep_PaintRoomRole)
	EPaintRoomRole PaintRoomRole;

	//페인트 룸 역할 리플리케이션 콜백
	UFUNCTION()
	void OnRep_PaintRoomRole();
};