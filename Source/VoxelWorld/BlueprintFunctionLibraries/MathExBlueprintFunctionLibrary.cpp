// Fill out your copyright notice in the Description page of Project Settings.


#include "MathExBlueprintFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

float UMathExBlueprintFunctionLibrary::AngleBetween(const FVector& aVector, const FVector& bVector)
{
	const float dot = aVector.Dot(bVector);
	return FMath::RadiansToDegrees(FMath::Acos(dot));
}

float UMathExBlueprintFunctionLibrary::SignedAngleBetween(const FVector& aVector, const FVector& bVector, const FVector& axisVector)
{
	const float angleBetween = AngleBetween(aVector, bVector);

	const FVector crossVector = aVector.Cross(bVector);

	return crossVector.Dot(axisVector) < 0 ? -angleBetween : angleBetween;
}

float UMathExBlueprintFunctionLibrary::NormalizeToRangeClamped(float value, float min, float max)
{
	const double normalizedToRange = UKismetMathLibrary::NormalizeToRange(value, min, max);
	return FMath::Clamp(normalizedToRange, 0, 1);
}

float UMathExBlueprintFunctionLibrary::ValueInCurveOrGiven(const UCurveFloat* curveFloat, float val)
{
	return IsValid(curveFloat) ? curveFloat->GetFloatValue(val) : val;
}

bool UMathExBlueprintFunctionLibrary::IsWithinRange(const float val, const float min, const float max)
{
	return val >= min && val < max;
}

bool UMathExBlueprintFunctionLibrary::IsWithinFloatRange(const float val, const FFloatRange& floatRange)
{
	return val >= floatRange.GetLowerBoundValue() && val <= floatRange.GetUpperBoundValue();
}

float UMathExBlueprintFunctionLibrary::NormalizeToFloatRange(float value, const FFloatRange& floatRange)
{
	return UKismetMathLibrary::NormalizeToRange(value, floatRange.GetLowerBound().GetValue(), floatRange.GetUpperBound().GetValue());
}

float UMathExBlueprintFunctionLibrary::LerpInFloatRange(float value, const FFloatRange& floatRange)
{
	return FMath::Lerp(floatRange.GetLowerBound().GetValue(), floatRange.GetUpperBound().GetValue(), value);
}
