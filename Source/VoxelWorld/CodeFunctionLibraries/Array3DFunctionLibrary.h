// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Array3DFunctionLibrary.generated.h"

/**
 * FArray3DFunctionLibrary
 *
 * Struct that holds useful 3D array functions.
 */
USTRUCT()
struct FArray3DFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename TArrayType>
	static void SetNum(TArray<TArray<TArray<TArrayType>>>& Array, int Width, int Height, int Depth);

	template <typename TArrayType>
	static bool IsInvalidIndex(TArray<TArray<TArray<TArrayType>>>& Array, int Width, int Height, int Depth);
};

template <typename TArrayType>
void FArray3DFunctionLibrary::SetNum(TArray<TArray<TArray<TArrayType>>>& Array, const int Width, const int Height, const int Depth)
{
	Array.SetNum(Width);
	for (int x = 0; x < Width; ++x)
	{
		Array[x].SetNum(Height);

		for (int y = 0; y < Height; ++y)
		{
			Array[x][y].SetNum(Depth);
		}
	}
}

template <typename TArrayType>
bool FArray3DFunctionLibrary::IsInvalidIndex(TArray<TArray<TArray<TArrayType>>>& Array, int Width, int Height, int Depth)
{
	if (!Array.IsValidIndex(Width))
	{
		return false;
	}

	if (!Array[Width].IsValidIndex(Height))
	{
		return false;
	}

	if (!Array[Width][Height].IsValidIndex(Depth))
	{
		return false;
	}

	return true;
}
