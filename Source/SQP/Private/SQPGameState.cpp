// Fill out your copyright notice in the Description page of Project Settings.


#include "SQPGameState.h"

#include "SQPPaintWorldSubsystem.h"

void ASQPGameState::Multicast_PaintRenderTarget_Implementation(const FVector Start, const FVector End, const uint8 BrushIndex, const float BrushSize)
{
	if (const auto Subsystem = GetWorld()->GetSubsystem<USQPPaintWorldSubsystem>())
	{
		Subsystem->TryPaint(Start, End, BrushIndex, BrushSize);
	}
}
