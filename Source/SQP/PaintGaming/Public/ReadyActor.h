// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReadyActor.generated.h"

DECLARE_DELEGATE(FOnTimerFinished)

UCLASS()
class SQP_API AReadyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReadyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTexture2D> ThumbsUp;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTexture2D> Headache;

public:
	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> StaticMeshComp;
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynMat;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
	FVector OrbitCenter = FVector::ZeroVector;

	// Radius in XY plane
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit", meta=(ClampMin="0.0"))
	float Radius = 2050.f;

	// Angular speed in degrees per second
	UPROPERTY(Replicated)
	float AngularSpeedDeg = 20.f;

	// Height (Z) while orbiting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
	float FixedZ = 405.f;

	// If true, actor will face the center. If false, orientation won't change.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
	bool bFaceCenter = true;

	// If true, only rotate around yaw (no pitch/roll)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
	bool bOnlyYaw = true;

	// Start angle in degrees (0 => +X axis)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
	float StartAngleDeg = 0.f;

private:
	// internal angle in radians
	float CurrentAngleRad;

	UPROPERTY(Replicated)
	bool bIsHit = false;

	UPROPERTY(Replicated)
	float ElapsedTime = 0.f;

	UFUNCTION()
	void OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
