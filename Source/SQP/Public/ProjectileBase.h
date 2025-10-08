// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SQP_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

	virtual void BeginPlay() override;

	//활성화
	UFUNCTION()
	void Active(const FTransform& FireTransform, const float InitSpeed);

	//비활성화
	UFUNCTION(BlueprintCallable)
	void Inactivate();

protected:
	//풀링 타이머 핸들
	FTimerHandle PoolingTimerHandle;

	//풀링 델리게이트
	FTimerDelegate PoolingDelegate;

	//충돌체 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp;

	//발사체 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMoveComp;
};
