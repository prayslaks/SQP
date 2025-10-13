// Fill out your copyright notice in the Description page of Project Settings.


#include "VFXManager.h"
#include "VFXDataAsset.h"
#include "VFXType.h"
#include "NiagaraFunctionLibrary.h"
#include "SQP.h"
#include "Shared/FComponentHelper.h"


#define VFX_DATA_PATH TEXT("'/Game/DataAssets/DA_VFX.DA_VFX'")

UVFXManager::UVFXManager()
{
	if (auto LoadedAsset = FComponentHelper::LoadAsset<UVFXDataAsset>(VFX_DATA_PATH))
	{
		VFXAsset = LoadedAsset;
		VFXDataMap = VFXAsset->VFXData;
	}
}

void UVFXManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!VFXAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load VFXDataAsset from path"));
	}
}


bool UVFXManager::GetVFXData(EVFXType Type, FVFXData& Out) const
{
	if (const FVFXData* Found = VFXDataMap.Find(Type))
	{
		Out = *Found;
		return true;
	}

	PRINTLOG(TEXT("DataGetFail : %s"), *UEnum::GetValueAsString(Type) );
	return false;
}

void UVFXManager::ShowVFX( EVFXType Type,
	FVector Location, FRotator Rotator, FVector Scale)
{
	FVFXData Params;
	if (!this->GetVFXData(Type, Params))
		return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		Params.VFXAsset,
		Location + Params.LocationOffset,
		Rotator + Params.RotatorOffset,
		Scale * Params.Scale,
		true,
		true,
		ENCPoolMethod::None,
		true
	);
}