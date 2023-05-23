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
	static float AngleBetween(const FVector& aVector, const FVector& bVector);

	UFUNCTION(BlueprintPure)
	static float SignedAngleBetween(const FVector& aVector, const FVector& bVector, const FVector& axisVector);

public:
	UFUNCTION(BlueprintPure)
	static float NormalizeToRangeClamped(float value, float min, float max);

	UFUNCTION(BlueprintPure)
	static float ValueInCurveOrGiven(const UCurveFloat* curveFloat, float val);

	UFUNCTION(BlueprintPure)
	static bool IsWithinRange(const float val, const float min, const float max);

public:
	UFUNCTION(BlueprintPure)
	static float NormalizeToFloatRange(float value, const FFloatRange& floatRange);

	UFUNCTION(BlueprintPure)
	static float LerpInFloatRange(float value, const FFloatRange& floatRange);

	UFUNCTION(BlueprintPure)
	static bool IsWithinFloatRange(const float val, const FFloatRange& floatRange);
};
