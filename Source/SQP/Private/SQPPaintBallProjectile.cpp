// Fill out your copyright notice in the Description page of Project Settings.

#include "SQPPaintBallProjectile.h"

#include "SQP.h"
#include "SQPPaintWorldSubsystem.h"
#include "SQP_PC_PaintRoom.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaintGaming/Public/ReadyActor.h"

ASQPPaintBallProjectile::ASQPPaintBallProjectile()
{
	//발사체 이동 컴포넌트 설정
	ProjectileMoveComp->InitialSpeed = 3000;
}

void ASQPPaintBallProjectile::BeginPlay()
{
	Super::BeginPlay();

	//서버 혹은 클라이언트에 따라 실제 작동 여부 결정
	if (bIsReal)
	{
		//바인드
		SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASQPPaintBallProjectile::OnOverlapBeginCallback);
	}

	DynMat = FindComponentByClass<UStaticMeshComponent>()->CreateAndSetMaterialInstanceDynamic(0);
}

void ASQPPaintBallProjectile::OnOverlapBeginCallback(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (auto OtherPaintBall = Cast<ASQPPaintBallProjectile>(OtherActor))
	{
		PRINTLOGNET(TEXT("%s"), *OtherActor->GetActorNameOrLabel());
		return;
	}
	
	//서버 측은 진짜일 것이므로
	if (HasAuthority() && bIsReal)
	{
		//모든 클라이언트에 채색 시도 명령
		for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (const auto PC = Cast<ASQP_PC_PaintRoom>(It->Get()))
			{
				PC->Client_PaintColor(GetActorLocation(), GetActorForwardVector(), PaintColor, BrushSize);
			}
		}
		
		//Multicast_TryPaint(PaintColor, BrushSize);
	}

	//비활성화
	InactivateProjectile();
}

void ASQPPaintBallProjectile::SetPaintColor(const FLinearColor& Value)
{
	PaintColor = Value;
	Multicast_ColorPaintBall(Value);
}

void ASQPPaintBallProjectile::Multicast_ColorPaintBall_Implementation(const FLinearColor Color)
{
	if (DynMat)
	{
		DynMat->SetVectorParameterValue(TEXT("PaintBallColor"), Color);
	}
}

void ASQPPaintBallProjectile::Multicast_TryPaint_Implementation(const FLinearColor BrushColor, const float BrushSizeValue)
{
	PRINTLOGNET(TEXT("Success!"));
	
	const FVector Offset = GetActorForwardVector() * 200;
	const FVector Start = GetActorLocation() - Offset;
	const FVector End = GetActorLocation() + Offset;
	const TArray<AActor*> ActorsToIgnore{this};
	const uint8 BrushIndex = FMath::RandRange(0, 8);

	if (const auto Subsystem = GetWorld()->GetSubsystem<USQPPaintWorldSubsystem>())
	{
		if (!BrushSizeValue)
		{
			constexpr float TempBrushSize = 250;
			Subsystem->TryPaintColor(Start, End, ActorsToIgnore, BrushIndex, TempBrushSize, BrushColor);
		}
		Subsystem->TryPaintColor(Start, End, ActorsToIgnore, BrushIndex, BrushSizeValue, BrushColor);
	}
}