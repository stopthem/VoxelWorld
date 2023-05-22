// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshExBlueprintFunctionLibrary.generated.h"

class UProceduralMeshComponent;
/**
 * UMeshExBlueprintFunctionLibrary
 *
 * Utility functions for meshes.
 */
UCLASS(BlueprintType)
class VOXELWORLD_API UMeshExBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static void CreateProceduralCube(UProceduralMeshComponent* ProceduralMeshComponent, UMaterial* Material, const FVector& Offset = FVector(0), const FVector& CubeRadius = FVector(50.0f));
};
