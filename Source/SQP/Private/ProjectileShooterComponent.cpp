// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileShooterComponent.h"
#include "ProjectileBase.h"
#include "ProjectilePoolWorldSubsystem.h"
#include "SQP.h"
#include "SQPPaintBallProjectile.h"
#include "SQP_PS_Master.h"
#include "SQP_PS_PaintRoomComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

UProjectileShooterComponent::UProjectileShooterComponent() :
	ShootRate(1),
	ProjectileSpeed(5000),
	TimeAtLastShootAtServer(0)
{
	PrimaryComponentTick.bCanEverTick = false;

	//오디오 컴포넌트 부착
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(this);
	AudioComp->bAutoActivate = false;

	//사운드 에셋
	if (static ConstructorHelpers::FObjectFinder<USoundWave>
		Finder(TEXT("'/Game/Assets/Sounds/Boink.Boink'"));
		Finder.Succeeded())
	{
		AudioComp->SetSound(Finder.Object);
	}
}

void UProjectileShooterComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<APawn>(GetOwner());
}

void UProjectileShooterComponent::PoolingProjectile(const TSubclassOf<AProjectileBase> ProjectileClass, const FTransform& SpawnTransform) const
{
	if (const auto Subsystem = GetWorld()->GetSubsystem<UProjectilePoolWorldSubsystem>())
	{
		//월드서브시스템에서 발사체 풀링
		AProjectileBase* Projectile = Subsystem->PopProjectile(ProjectileClass, SpawnTransform, 2000);
		if (!Projectile)
		{
			return;
		}

		//오너 설정
		Projectile->SetOwner(GetOwner());

		//페인트볼에 색상 설정
		if (const auto PaintBall = Cast<ASQPPaintBallProjectile>(Projectile))
		{
			if (const auto Player = Cast<ACharacter>(GetOwner()))
			{
				if (const auto PlayerState = Player->GetPlayerState<ASQP_PS_Master>())
				{
					PaintBall->SetPaintBallOwner(PlayerState);
					PaintBall->SetPaintColor(PlayerState->PaintRoom->SelectedColor);
					PaintBall->SetBrushSize(PlayerState->PaintRoom->SelectedBrushSize);
				}
			}
		}
	}
}

void UProjectileShooterComponent::PullTrigger()
{
	//로컬 컨트롤러 확인
	if (!OwnerCharacter || !OwnerCharacter->IsLocallyControlled())
	{
		return;
	}

	//현재 시간과 이전 사격 시간을 비교하여 사격 주기와 대조
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (TimeAtLastShootAtClient + ShootRate > CurrentTime)
	{
		return;
	}

	//사격 시간 업데이트
	TimeAtLastShootAtClient = CurrentTime;

	//사격음 재생
	if (AudioComp)
	{
		AudioComp->Play();
	}
	
	//사격 순간의 트랜스폼 저장
	const FTransform MuzzleTransform = GetComponentTransform();

	//클라이언트 측 가짜 발사체 스폰
	PoolingProjectile(FakeProjectileClass, MuzzleTransform);
	
	//서버 측의 진짜 발사체를 위해서 사격 정보 전달
	const FVector MuzzleLocation = MuzzleTransform.GetLocation();
	const FVector ShootDirection = MuzzleTransform.GetRotation().GetForwardVector();
	const float ShooterServerTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	Server_Fire(MuzzleLocation, ShootDirection, ShooterServerTime);
}

void UProjectileShooterComponent::ReleaseTrigger()
{
	
}

void UProjectileShooterComponent::Server_Fire_Implementation(const FVector MuzzleLocation, const FVector_NetQuantizeNormal ShootDirection, const float ShooterServerTime)
{
	//오너 캐릭터의 유효성 확인
	if (OwnerCharacter == nullptr)
	{
		return;
	}
	
	//이전 사격 시간과 비교하여 너무 빠르면 차단
	const float CurrentTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	if (TimeAtLastShootAtServer + ShootRate > CurrentTime)
	{
		return;
	}

	//사격 시간 업데이트
	TimeAtLastShootAtServer = CurrentTime;

	//지연 시간을 토대로 트랜스폼을 재구축
	const float Latency = GetWorld()->GetGameState()->GetServerWorldTimeSeconds() - ShooterServerTime;
	const FTransform MuzzleTransform(ShootDirection.ToOrientationRotator(), MuzzleLocation + ProjectileSpeed * Latency * ShootDirection);

	//서버 측의 비시각적 충돌 처리 진짜 발사체를 풀링
	PoolingProjectile(RealProjectileClass, MuzzleTransform);

	//모든 클라이언트에 시각적 가짜 발사체를 풀링하도록 명령
	Multicast_FireVisuals(MuzzleLocation, ShootDirection, ShooterServerTime);
}

void UProjectileShooterComponent::Multicast_FireVisuals_Implementation(const FVector MuzzleLocation, const FVector_NetQuantizeNormal ShootDirection, const float ShooterServerTime)
{
	PRINTLOGNET(TEXT("Multicast Fake PaintBall!"));
	
	//발사 주체인 클라이언트를 제외한 나머지 클라이언트들만 가짜 발사체를 풀링하고 사운드를 재생
	if (OwnerCharacter && !OwnerCharacter->IsLocallyControlled())
	{
		PRINTLOGNET(TEXT("Multicast Fake PaintBall!"));
		
		//지연 시간을 토대로 트랜스폼을 재구축
		const float Latency = GetWorld()->GetGameState()->GetServerWorldTimeSeconds() - ShooterServerTime;
		const FTransform MuzzleTransform(ShootDirection.ToOrientationRotator(), MuzzleLocation + ProjectileSpeed * Latency * ShootDirection);
		
		//시각적 가짜 발사체를 풀링하도록 명령
		PoolingProjectile(FakeProjectileClass, MuzzleTransform);

		//사격음 재생
		if (AudioComp)
		{
			AudioComp->Play();
		}
	}
}