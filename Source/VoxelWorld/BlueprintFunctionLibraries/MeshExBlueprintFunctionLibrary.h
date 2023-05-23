// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelWorld/Mesh/VoxelQuad.h"
#include "MeshExBlueprintFunctionLibrary.generated.h"

struct FVoxelMeshParameters;
class UProceduralMeshComponent;
/**
 * UMeshExBlueprintFunctionLibrary
 *
 * Utility functions for meshes.
 */
UCLASS(BlueprintType)
class UMeshExBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static void CreateProceduralCube(const FVoxelMeshParameters& VoxelMeshParameters, const EVoxelQuadFace QuadFaces = EVoxelQuadFace::All);
};
