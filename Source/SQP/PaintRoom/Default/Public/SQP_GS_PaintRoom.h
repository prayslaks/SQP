// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQPGameState.h"
#include "SQP_GS_PaintRoom.generated.h"

struct FPaintExecutionData;

UCLASS()
class SQP_API ASQP_GS_PaintRoom : public ASQPGameState
{
	GENERATED_BODY()

public:
	ASQP_GS_PaintRoom();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_PaintExecutionDataSnapshot)
	TArray<FPaintExecutionData> PaintExecutionDataSnapshot;

	UFUNCTION()
	void OnRep_PaintExecutionDataSnapshot();

	bool bHasInitialPaintDataBeenApplied = false;

	UPROPERTY()
	TObjectPtr<UTexture2D> RandomImage;
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetRandomImage(UTexture2D* Image);

	UPROPERTY()
	TObjectPtr<class UTexture2D> CompareAImage;
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetCompareAImage(UTexture2D* Image);

	UPROPERTY()
	TObjectPtr<class UTexture2D> CompareBImage;
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetCompareBImage(UTexture2D* Image);
};
