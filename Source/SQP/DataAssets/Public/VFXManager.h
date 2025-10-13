// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VFXType.h"
#include "VFXDataAsset.h"
#include "Core/Macro.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VFXManager.generated.h"

/**
 * 
 */
UCLASS()
class SQP_API UVFXManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	DEFINE_SUBSYSTEM_GETTER_INLINE(UVFXManager);

	UVFXManager();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="VFX")
	bool GetVFXData(EVFXType Type, FVFXData& Out) const;
	
	UFUNCTION(BlueprintCallable, Category="VFX")
	void ShowVFX( EVFXType Type, FVector Location, FRotator Rotator, FVector Scale);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TObjectPtr<class UVFXDataAsset> VFXAsset;
	
	UPROPERTY(EditAnywhere, Category = "VFX")
	TMap<EVFXType, FVFXData> VFXDataMap; 
};