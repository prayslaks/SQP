#pragma once

#include "CoreMinimal.h"
#include "VFXType.h"
#include "Engine/DataAsset.h"
#include "VFXDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FVFXData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNiagaraSystem> VFXAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector LocationOffset = FVector::Zero();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator RotatorOffset = FRotator(0, 0, 0 );
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Scale = 1.f;
};

UCLASS(BlueprintType)
class SQP_API UVFXDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "VFX")
	TMap<EVFXType, FVFXData> VFXData;
};