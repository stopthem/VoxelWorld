// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/Mesh/VoxelQuad.h"
#include "VoxelBlock.generated.h"

class AVoxelChunk;
class ABlocksManager;
enum class EBlockType : uint8;
enum class EVoxelQuadFace : uint8;
class UProceduralMeshComponent;
/*
 * FVoxelBlock
 *
 * Base struct to construct a block.
 */
USTRUCT()
struct VOXELWORLD_API FVoxelBlock
{
	GENERATED_BODY()

public:
	FVoxelBlock();

	explicit FVoxelBlock(const FVoxelBlockParameters& VoxelBlockParameters, AVoxelChunk* VoxelChunk);

public:
	void BuildCube() const;

public:
	EBlockType GetBlockType() const { return VoxelBlockParameters.BlockType; }

protected:
	UPROPERTY(VisibleAnywhere)
	AVoxelChunk* VoxelChunk;

	FVoxelBlockParameters VoxelBlockParameters;

protected:
	bool HasSolidNeighbour(const FVector& OffsetDirVector) const;

	FVector GetOffsetInMeters() const
	{
		return VoxelBlockParameters.Offset / 100.0f;
	}

	// UPROPERTY(VisibleAnywhere)
	// FVector MeshCubeRadius = FVector(100.0f, 100.0f, 100.0f);
	//
	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<UMaterial> BlockMeshMaterial;

private:
	// 	UFUNCTION()
	// void SetMaterialTiling();
};
