// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AReadyActor::AReadyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AReadyActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp = FindComponentByClass<UStaticMeshComponent>();
	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AReadyActor::OnOverLap);
	DynMat = StaticMeshComp->CreateAndSetMaterialInstanceDynamic(0);
	
	// convert start angle to radians
	CurrentAngleRad = FMath::DegreesToRadians(StartAngleDeg);
	// if Radius is zero, keep at center (but still can face center)
}

void AReadyActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReadyActor, AngularSpeedDeg);
	DOREPLIFETIME(AReadyActor, bIsHit);
	DOREPLIFETIME(AReadyActor, ElapsedTime);
}

// Called every frame
void AReadyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// update angle
	float AngularSpeedRad = FMath::DegreesToRadians(AngularSpeedDeg);
	CurrentAngleRad += AngularSpeedRad * DeltaTime;

	// compute new position in XY plane
	float X = OrbitCenter.X + FMath::Cos(CurrentAngleRad) * Radius;
	float Y = OrbitCenter.Y + FMath::Sin(CurrentAngleRad) * Radius;
	float Z = FixedZ + OrbitCenter.Z;

	FVector NewLocation(X, Y, Z);
	SetActorLocation(NewLocation);

	if (bFaceCenter)
	{
		FVector Direction = (OrbitCenter - NewLocation); // points from actor -> center
		if (!Direction.IsNearlyZero())
		{
			FRotator LookRot = Direction.Rotation(); // full rotation (pitch,yaw,roll=0)
			if (bOnlyYaw)
			{
				// Keep only yaw, zero pitch & roll
				FRotator Current = GetActorRotation();
				LookRot.Pitch = 0.f;
				LookRot.Roll = 0.f;
				// optionally preserve current pitch if wanted: LookRot.Pitch = Current.Pitch;
			}
			SetActorRotation(LookRot);
		}
	}

	if (bIsHit)
	{
		ElapsedTime += DeltaTime;
		DynMat->SetTextureParameterValue(FName("Emotion"), Headache);
		if (ElapsedTime >= 6.0f)
		{
			bIsHit = false;
			AngularSpeedDeg = 20.f;
		}
	}
	else
	{
		DynMat->SetTextureParameterValue(FName("Emotion"), ThumbsUp);
	}
}

void AReadyActor::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		ElapsedTime = 0.f;
		AngularSpeedDeg = 75.f;
		bIsHit = true;
	}
}