// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQPCharacter.h"
#include "SQPPlayer.generated.h"

UCLASS()
class SQP_API ASQPPlayer : public ASQPCharacter
{
	GENERATED_BODY()

public:
	ASQPPlayer();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Splatoon)
	TArray<UTexture2D*> ColorTextureArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Splatoon)
	TArray<UTexture2D*> NormalTextureArray;
	
	UPROPERTY(EditDefaultsOnly, Category = Splatoon)
	TObjectPtr<UMaterial> CanvasMaterialBase;

	UPROPERTY(EditDefaultsOnly, Category = Splatoon)
	TObjectPtr<UMaterial> ColorBrushMaterialBase;

	UPROPERTY(EditDefaultsOnly, Category = Splatoon)
	TObjectPtr<UMaterial> NormalBrushMaterialBase;

	UPROPERTY(BlueprintReadOnly, Category = Splatoon)
	TObjectPtr<UMaterialInstanceDynamic> ColorBrushMaterialDynamicInstance;
	
	UPROPERTY(BlueprintReadOnly, Category = Splatoon)
	TObjectPtr<UMaterialInstanceDynamic> NormalBrushMaterialDynamicInstance;

	UFUNCTION(BlueprintCallable, Category = Splatoon)
	void GetRenderTargetFromHit(const FHitResult& Hit, UTextureRenderTarget2D*& OutColorRenderTarget, UTextureRenderTarget2D*& OutNormalRenderTarget) const;

	UFUNCTION(BlueprintCallable, Category = Splatoon)
	void PaintRenderTarget(int32 BrushIndex, const float BrushSize, const FVector2D& DrawLocation, UTextureRenderTarget2D* ColorRenderTarget, UTextureRenderTarget2D* NormalRenderTarget);

	UFUNCTION(BlueprintCallable, Category = Splatoon)
	void PaintColorRenderTarget(UTexture2D* BrushTexture, const float BrushSize, const FVector2D& DrawLocation, UTextureRenderTarget2D* ColorRenderTarget);

	UFUNCTION(BlueprintCallable, Category = Splatoon)
	void PaintNormalRenderTarget(UTexture2D* BrushTexture, const float BrushSize, const FVector2D& DrawLocation, UTextureRenderTarget2D* NormalRenderTarget);
};
