// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrayBlueprintFunctionLibrary.h"

UArrayBlueprintFunctionLibrary::UArrayBlueprintFunctionLibrary()
{
}

TArray<float> UArrayBlueprintFunctionLibrary::ConvertDoubleArrayToFloatArray(TArray<double>& Source)
{
	TArray<float> FloatArray;
	for (const double Val : Source)
	{
		FloatArray.Add(static_cast<float>(Val));
	}

	return FloatArray;
}
