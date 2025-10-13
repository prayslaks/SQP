// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SFXType.h"
#include "Core/Macro.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFXManager.generated.h"

/**
 * 
 */
UCLASS()
class SQP_API USFXManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	DEFINE_SUBSYSTEM_GETTER_INLINE(USFXManager);

	USFXManager();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="Sound")
	void PlaySound(ESFXType Type, FVector Location);

	UFUNCTION(BlueprintCallable, Category="Sound")
	void PlaySound2D(ESFXType Type);

	UFUNCTION(BlueprintCallable, Category="Sound")
	void StopSound2D(const ESFXType Type);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USFXDataAsset> SoundAsset;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	TMap<ESFXType, TObjectPtr<USoundBase>> SoundData;

	UPROPERTY()
	TMap<ESFXType, UAudioComponent*> ActiveSounds;
};
