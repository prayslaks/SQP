// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileShooterComponent.h"
#include "ProjectilePoolWorldSubsystem.h"

UProjectileShooterComponent::UProjectileShooterComponent() :
	bIsOnTrigger(false),
	ElapsedTimeAfterLastShoot(0),
	ShootRate(0.2),
	ShootCounter(0),
	BurstLimiter(-1)
{
	//컴포넌트 틱 활성화
	PrimaryComponentTick.bCanEverTick = true;
}

void UProjectileShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//트리거가 활성화되어 있다면
	if (bIsOnTrigger)
	{
		//버스트 리미터보다 적게 발사했다면
		if (BurstLimiter == -1 || ShootCounter < BurstLimiter)
		{
			//시간이 지나가고
			ElapsedTimeAfterLastShoot += DeltaTime;

			//발사 시간이 지나가면
			if (ElapsedTimeAfterLastShoot > ShootRate)
			{
				//발사 카운터를 증가시키고
				ShootCounter++;
			
				//발사 시간을 차감하고
				ElapsedTimeAfterLastShoot -= ShootRate;

				//발사체를 발사한다
				if (const auto Subsystem = GetWorld()->GetSubsystem<UProjectilePoolWorldSubsystem>())
				{
					Subsystem->PopProjectile(ProjectileClass, GetComponentTransform(), 2000);
				}
			}	
		}
	}
}

void UProjectileShooterComponent::PullTrigger()
{
	bIsOnTrigger = true;
	ElapsedTimeAfterLastShoot = ShootRate;
	ShootCounter = 0;
}

void UProjectileShooterComponent::ReleaseTrigger()
{
	bIsOnTrigger = false;
}