// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/Block/VoxelBlock.h"

#include "VoxelChunk.generated.h"

class AVoxelWorldGameModeBase;
class ABlocksManager;
class UProceduralMeshComponent;
/*
 * AVoxelChunk
 *
 * The chunk actor class holding cubes.
 */
UCLASS()
class VOXELWORLD_API AVoxelChunk : public AActor
{
	GENERATED_BODY()

public:
	AVoxelChunk();

protected:
	// Where we wait for the VoxelGameModeBase OnManagersSpawned.
	virtual void BeginPlay() override;

	// This is where we start spawning our blocks.
	UFUNCTION()
	void OnManagersSpawned(AVoxelWorldGameModeBase* VoxelWorldGameModeBase);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	// Mesh component that produces the mesh for us.
	UPROPERTY(VisibleAnywhere, Category="BlockMesh")
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;

public:
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }
	int GetDepth() const { return Depth; }

protected:
	// Width of the 3D blocks array.
	UPROPERTY(EditAnywhere)
	int Width = 2;

	// Height of the 3D blocks array.
	UPROPERTY(EditAnywhere)
	int Height = 2;

	// Depth of the 3D blocks array.
	UPROPERTY(EditAnywhere)
	int Depth = 2;

public:
	TArray<EBlockType> GetChunkBlockTypes() { return ChunkBlockTypes; }

	bool TryGetBlockAt(const FVector& Offset, FVoxelBlock& out_FoundBlock);

protected:
	TArray<TArray<TArray<FVoxelBlock>>> ChunkVoxelBlocks;

	// x + Width * (y + Depth * z) = original x,y,z
	TArray<EBlockType> ChunkBlockTypes;

public:
	int Get3DElementPosInFlat(const int X, const int Y, const int Z) const;

protected:
	void BuildChunk(const ABlocksManager* BlocksManager);
};
