// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectilePoolWorldSubsystem.generated.h"

class AProjectileBase;

UCLASS()
class SQP_API UProjectilePoolWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//현재 월드 비활성 시 풀링되어 있던 오브젝트 처리
	virtual void Deinitialize() override;

	//풀에서 임의의 발사체를 추출
	UFUNCTION(BlueprintCallable)
	AProjectileBase* PopProjectile(TSubclassOf<AProjectileBase> Class, const FTransform& FireTransform, const float& InitSpeed);

	//풀에 대상 발사체를 삽입
	UFUNCTION(BlueprintCallable)
	void PushProjectile(AProjectileBase* Projectile);

private:
	//클래스를 토대로 발사체를 저장하는 풀링
	TMap<UClass*, TSharedPtr<TQueue<AProjectileBase*>>> ProjectilePools;

	//요청한 발사체를 스폰한다
	UFUNCTION()
	AProjectileBase* SpawnRequestedProjectile(TSubclassOf<AProjectileBase> Class, const FVector& Location, const FRotator& Rotation) const;
};