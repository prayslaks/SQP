// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompareActor.generated.h"

UENUM(BlueprintType)
enum class EPaintGamePlayer : uint8
{
	PlayerA,
	PlayerB
};

UCLASS()
class SQP_API ACompareActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACompareActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PaintGamePlayer")
	EPaintGamePlayer PaintGamePlayer = EPaintGamePlayer::PlayerA;

	

	UPROPERTY()
	TObjectPtr<class UAISimilarityClient> Client;
	UPROPERTY()
	TObjectPtr<class ASQP_GS_PaintRoom> GS;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FinishGame();

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynMat;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCompareImage(UTexture2D* Image);

	void EvaluateWinner();
};
