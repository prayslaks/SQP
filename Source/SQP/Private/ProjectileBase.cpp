// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "ProjectilePoolWorldSubsystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	//액터 틱 비활성화
	PrimaryActorTick.bCanEverTick = true;

	//충돌체 부착
	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("SphereComp"));
	SphereComp->SetCollisionProfileName(FName("Projectile"), true);
	SetRootComponent(SphereComp);

	//발사체 이동 컴포넌트 부착
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMoveComp"));

	//발사체 속도 설정
	ProjectileMoveComp->InitialSpeed = 2000;
	
	//총탄이 속도를 따라 회전하도록 설정
	ProjectileMoveComp->bRotationFollowsVelocity = true;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//풀링 델리게이트 바인드
	PoolingDelegate.BindUFunction(this, FName("Inactivate"));
}

void AProjectileBase::Active(const FTransform& FireTransform, const float InitSpeed)
{
	//활성화
	SetActorLocationAndRotation(FireTransform.GetLocation(), FireTransform.GetRotation());
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	//이동 방향 전환
	if (ProjectileMoveComp)
	{
		//초기 속도로 전환
		ProjectileMoveComp->Velocity = InitSpeed * GetActorForwardVector();
	}

	//5초 후에 풀에 반환
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(PoolingTimerHandle, PoolingDelegate, 5, false);
	}
}

void AProjectileBase::Inactivate()
{
	//풀링 타이머 핸들 비활성
	if (PoolingTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(PoolingTimerHandle);
	}
	
	//비활성화
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	//풀에 반환한다
	if (const UWorld* World = GetWorld())
	{
		if (const auto Subsystem = World->GetSubsystem<UProjectilePoolWorldSubsystem>())
		{
			Subsystem->PushProjectile(this);
		}
	}
}