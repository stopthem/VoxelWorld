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

	explicit FVoxelBlock(const FVoxelMeshParameters& VoxelMeshParameters, AVoxelChunk* VoxelChunk);

public:
	EBlockType GetBlockType() const { return BlockType; }

protected:
	EBlockType BlockType;

	UPROPERTY(VisibleAnywhere)
	AVoxelChunk* VoxelChunk;

	FVector Offset;

protected:
	bool HasSolidNeighbour(const FVector& OffsetDirVector) const;

	// UPROPERTY(VisibleAnywhere)
	// FVector MeshCubeRadius = FVector(100.0f, 100.0f, 100.0f);
	//
	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<UMaterial> BlockMeshMaterial;

private:
	// 	UFUNCTION()
	// void SetMaterialTiling();
};
