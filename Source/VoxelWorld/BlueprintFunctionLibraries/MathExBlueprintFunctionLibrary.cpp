// Fill out your copyright notice in the Description page of Project Settings.


#include "MathExBlueprintFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

float UMathExBlueprintFunctionLibrary::AngleBetweenVectors(const FVector& AVector, const FVector& BVector)
{
	const float Dot = AVector.Dot(BVector);
	return FMath::RadiansToDegrees(FMath::Acos(Dot));
}

float UMathExBlueprintFunctionLibrary::SignedAngleBetween(const FVector& AVector, const FVector& BVector, const FVector& AxisVector)
{
	const float AngleBetween = AngleBetweenVectors(AVector, BVector);

	const FVector CrossVector = AVector.Cross(BVector);

	return CrossVector.Dot(AxisVector) < 0 ? -AngleBetween : AngleBetween;
}

float UMathExBlueprintFunctionLibrary::NormalizeToRangeClamped(const float Value, const float Min, const float Max)
{
	const double NormalizedToRange = UKismetMathLibrary::NormalizeToRange(Value, Min, Max);
	return FMath::Clamp(NormalizedToRange, 0, 1);
}

float UMathExBlueprintFunctionLibrary::ValueInCurveOrGiven(const UCurveFloat* CurveFloat, const float Val)
{
	return IsValid(CurveFloat) ? CurveFloat->GetFloatValue(Val) : Val;
}

bool UMathExBlueprintFunctionLibrary::IsWithinFloatRange(const float Val, const FFloatRange& FloatRange)
{
	return Val >= FloatRange.GetLowerBoundValue() && Val <= FloatRange.GetUpperBoundValue();
}

float UMathExBlueprintFunctionLibrary::fBM(const float X, const float Z, const int Octaves, const float Scale, const float HeightScale, const float HeightOffset)
{
	float Total = 0.0f;
	float Frequency = 1;

	for (int i = 0; i < Octaves; ++i)
	{
		Total += FMath::PerlinNoise2D(FVector2D(X * Scale * Frequency, Z * Scale * Frequency)) * HeightScale;
		Frequency *= 2;
	}

	return Total + HeightOffset;
}

float UMathExBlueprintFunctionLibrary::NormalizeToFloatRange(const float Value, const FFloatRange& FloatRange)
{
	return UKismetMathLibrary::NormalizeToRange(Value, FloatRange.GetLowerBound().GetValue(), FloatRange.GetUpperBound().GetValue());
}

float UMathExBlueprintFunctionLibrary::LerpInFloatRange(const float Value, const FFloatRange& FloatRange)
{
	return FMath::Lerp(FloatRange.GetLowerBound().GetValue(), FloatRange.GetUpperBound().GetValue(), Value);
}
