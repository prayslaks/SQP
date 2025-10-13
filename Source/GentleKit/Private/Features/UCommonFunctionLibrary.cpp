// Copyright (c) 2025 Doppleddiggong. All rights reserved.

#include "Features/UCommonFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/DateTime.h"

bool UCommonFunctionLibrary::InBounds(const int32 Index, const int32 Count)
{
	return (Index >= 0) && (Index < Count);
}

int32 UCommonFunctionLibrary::GetRandomIndex(const TArray<int32>& TargetArray, bool& bIsValid)
{
	if (TargetArray.Num() == 0)
	{
		bIsValid = false;
		return INDEX_NONE;
	}
	bIsValid = true;
	return TargetArray[FMath::RandRange(0, TargetArray.Num() - 1)];
}

UAnimMontage* UCommonFunctionLibrary::GetRandomMontage(const TArray<UAnimMontage*>& Montages)
{
	const int32 Num = Montages.Num();
	if (Num <= 0)
		return nullptr;

	const int32 Idx = FMath::RandRange(0, Num - 1);
	return Montages[Idx];
}

int64 UCommonFunctionLibrary::GetNowTimestamp()
{
	const auto DataTime = FDateTime::UtcNow();
	return DataTime.ToUnixTimestamp();
}

UMaterialInstanceDynamic* UCommonFunctionLibrary::GetOrCreateMID(
	UPrimitiveComponent* Target, int32 ElementIndex, FName OptionalName)
{
	if (!Target)
		return nullptr;

	const int32 Num = Target->GetNumMaterials();
	if (ElementIndex < 0 || ElementIndex >= Num)
		return nullptr;

	UMaterialInterface* CurMat = Target->GetMaterial(ElementIndex);
	if (!CurMat)
		return nullptr;

	if (UMaterialInstanceDynamic* AsMID = Cast<UMaterialInstanceDynamic>(CurMat))
		return AsMID;

	UMaterialInstanceDynamic* NewMID = UMaterialInstanceDynamic::Create(CurMat, Target, OptionalName);
	if (NewMID)
		Target->SetMaterial(ElementIndex, NewMID);

	return NewMID;
}

void UCommonFunctionLibrary::PlayLocationSound(const AActor* Actor, USoundBase* Sound, const float RetriggerDelay)
{
	if (!IsValid(Actor) || !Sound)
		return;
	
	if (auto World = Actor->GetWorld())
	{
		if ( RetriggerDelay > 0.0f)
		{
			TWeakObjectPtr<const AActor> WeakActor = Actor;
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, [WeakActor, Sound]()
			{
				if (WeakActor.IsValid())
				{
					UGameplayStatics::PlaySoundAtLocation(WeakActor.Get(), Sound, WeakActor->GetActorLocation());
				}
			}, RetriggerDelay, false);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(Actor, Sound, Actor->GetActorLocation());
		}
	}
}

float UCommonFunctionLibrary::GetDistance(AActor* A, AActor* B)
{
	if ( !IsValid(A) || !IsValid(B) )
		return 0;

	return UKismetMathLibrary::Vector_Distance( A->GetActorLocation(), B->GetActorLocation() );
}
