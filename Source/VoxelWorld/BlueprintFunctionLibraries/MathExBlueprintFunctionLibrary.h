// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathExBlueprintFunctionLibrary.generated.h"

/**
 * UMathExBlueprintFunctionLibrary
 *
 * A blueprint function library class for Math functions
 */
UCLASS()
class UMathExBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static float AngleBetweenVectors(const FVector& AVector, const FVector& BVector);

	UFUNCTION(BlueprintPure)
	static float SignedAngleBetween(const FVector& AVector, const FVector& BVector, const FVector& AxisVector);

public:
	UFUNCTION(BlueprintPure)
	static float NormalizeToRangeClamped(float Value, float Min, float Max);

	UFUNCTION(BlueprintPure)
	static float ValueInCurveOrGiven(const UCurveFloat* CurveFloat, float Val);

public:
	UFUNCTION(BlueprintPure)
	static float NormalizeToFloatRange(float Value, const FFloatRange& FloatRange);

	UFUNCTION(BlueprintPure)
	static float LerpInFloatRange(float Value, const FFloatRange& FloatRange);

	UFUNCTION(BlueprintPure)
	static bool IsWithinFloatRange(float Val, const FFloatRange& FloatRange);

public:
	UFUNCTION(BlueprintPure)
	static float fBM(float X, float Z, int Octaves, float Scale, float HeightScale, float HeightOffset);
};
