// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/BlueprintFunctionLibraries/MeshExBlueprintFunctionLibrary.h"
#include "VoxelBlock.generated.h"

class ABlocksManager;
enum class EBlockType : uint8;
enum class EVoxelQuadFace : uint8;
class UProceduralMeshComponent;
class AVoxelChunk;
/*
 * FVoxelBlock
 *
 * Base struct to construct a block.
 * Has no purpose other than block type for now.
 */
USTRUCT()
struct VOXELWORLD_API FVoxelBlock
{
	GENERATED_BODY()

public:
	FVoxelBlock();

	explicit FVoxelBlock(const FVoxelBlockParameters& VoxelBlockParameters, AVoxelChunk* VoxelChunk);

public:
	EBlockType GetBlockType() const { return VoxelBlockParameters.BlockType; }

protected:
	UPROPERTY(VisibleAnywhere)
	AVoxelChunk* VoxelChunk;

	FVoxelBlockParameters VoxelBlockParameters;
};
