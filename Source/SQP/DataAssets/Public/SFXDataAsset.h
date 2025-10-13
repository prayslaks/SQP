// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFXType.h"
#include "Engine/DataAsset.h"
#include "SFXDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SQP_API USFXDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TMap<ESFXType, TObjectPtr<USoundBase>> SoundData;
};
