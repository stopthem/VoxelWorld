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
	static void RemoveDuplicates(TArray<T>& Source);

	template <typename T>
	static void AppendUnique(TArray<T>& Source, TArray<T>& Target);

public:
	static TArray<float> ConvertDoubleArrayToFloatArray(TArray<double>& Source);
};

template <typename T>
void UArrayBlueprintFunctionLibrary::RemoveDuplicates(TArray<T>& Source)
{
	TSet<T> Set = TSet(Source);
	Source = Set.Array();
}

template <typename T>
void UArrayBlueprintFunctionLibrary::AppendUnique(TArray<T>& Source, TArray<T>& Target)
{
	for (auto SourceElement : Source)
	{
		Target.AddUnique(SourceElement);
	}
} 
