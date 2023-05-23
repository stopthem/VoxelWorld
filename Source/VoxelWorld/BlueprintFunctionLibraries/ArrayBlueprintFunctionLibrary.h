// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArrayBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UArrayBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UArrayBlueprintFunctionLibrary();

	template <typename T>
	static void RemoveDuplicates(TArray<T>& sourceArray);

	template <typename T>
	static void AppendUnique(TArray<T>& source, TArray<T>& target);

public:
	static TArray<float> ConvertDoubleArrayToFloatArray(TArray<double>& source);
};

template <typename T>
void UArrayBlueprintFunctionLibrary::RemoveDuplicates(TArray<T>& sourceArray)
{
	TSet<T> set = TSet(sourceArray);
	sourceArray = set.Array();
}

template <typename T>
void UArrayBlueprintFunctionLibrary::AppendUnique(TArray<T>& source, TArray<T>& target)
{
	for (auto sourceElement : source)
	{
		target.AddUnique(sourceElement);
	}
}
