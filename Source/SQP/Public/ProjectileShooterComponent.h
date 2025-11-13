// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "ProjectileShooterComponent.generated.h"

class AProjectileBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SQP_API UProjectileShooterComponent : public UArrowComponent
{
	GENERATED_BODY()

public:
	//각종 프로퍼티를 초기화하는 생성자
	UProjectileShooterComponent();

	//소유 캐릭터 획득
	virtual void BeginPlay() override;

	//발사체 풀링 월드 서브시스템에 요청한 발사체 클래스를 풀링하여 반환
	UFUNCTION()
	void PoolingProjectile(const TSubclassOf<AProjectileBase> ProjectileClass, const FTransform& SpawnTransform) const;
	
	//외부에서 호출해 발사 신호를 주는 메서드
	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	//외부에서 호출해 발사 신호를 끊는 메서드
	UFUNCTION(BlueprintCallable)
	void ReleaseTrigger();

	//유저의 발사 입력 신호를 전달하여 진짜 발사체 생성을 명령하는 Server RPC
	UFUNCTION(Server, Reliable)
	void Server_Fire(const FVector MuzzleLocation, const FVector_NetQuantizeNormal ShootDirection, const float ShooterServerTime);

	//서버의 발사 이후, 발사 주체를 제외한 모든 클라이언트에게 가짜 발사체 생성을 명령하는 Multicast RPC
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FireVisuals(const FVector MuzzleLocation, const FVector_NetQuantizeNormal ShootDirection, const float ShooterServerTime);

	//서버에서 발사할 블루프린트 클래스를 에디터에서 설정
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileBase> RealProjectileClass;

	//클라이언트에서 발사할 블루프린트 클래스를 에디터에서 설정
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileBase> FakeProjectileClass;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APawn> OwnerCharacter;

	//클라이언트 측 지난 발사 시간
	UPROPERTY(VisibleAnywhere)
	float TimeAtLastShootAtClient;

	//서버 측 지난 발사 시간
	UPROPERTY(VisibleAnywhere)
	float TimeAtLastShootAtServer;

	//다음 발사까지 걸리는 시간
	UPROPERTY(EditDefaultsOnly)
	float ShootRate;

	//발사체 속도
	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed;

	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioComp;
};
