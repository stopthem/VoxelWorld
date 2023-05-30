// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/Block/VoxelBlock.h"
#include "VoxelChunk.generated.h"

enum class EBlockType : uint8;
class AVoxelWorldManager;
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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	// Mesh component that produces the mesh for us.
	UPROPERTY(VisibleAnywhere, Category="Block Mesh")
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;

private:
	UPROPERTY(EditAnywhere, Category="Noise Settings")
	int NoiseFractalOctaves = 18;

	UPROPERTY(EditAnywhere, Category="Noise Settings")
	float NoiseFractalGain = 0.001f;

	UPROPERTY(EditAnywhere, Category="Noise Settings")
	float NoiseFrequency = 0.03f;

	UPROPERTY(EditAnywhere, Category="Noise Settings")
	float NoiseLacunarity = 0.5f;

	UPROPERTY(EditAnywhere, Category="Noise Settings")
	float NoiseWeightedStr = 0.5f;

public:
	TArray<EBlockType> GetChunkBlockTypes() { return ChunkBlockTypes; }

	// NOTE : BlockArrayPos must be considered 3d array position, not world position.
	bool TryGetBlockAt(const FVector& BlockArrayPos, FVoxelBlock& out_FoundBlock);

	// Is given ArrayOffset within 3d array bounds ?.
	// NOTE : BlockArrayPos must be considered 3d array position, not world position.
	bool IsWithinChunkBounds(const FVector& BlockArrayPos);

private:
	// NOTE : BlockArrayPos must be considered 3d array position, not world position.
	EVoxelQuadFace GetNonSolidNeighbourFaces(const FVector& BlockArrayPos);

private:
	// 3d array of blocks.
	TArray<TArray<TArray<FVoxelBlock>>> ChunkBlocks;

	// flat = x + Width * (y + Depth * z) = original x,y,z
	// x = i % Width
	// y = (i / Width) % Height
	// z = i /  (Width * Height)
	TArray<EBlockType> ChunkBlockTypes;

	// Information used to create section in ProceduralMeshComponent.
	FVoxelMeshParameters ChunkMeshParams;

	int32 VertexCount = 0;

private:
	FVector GetMetricActorLocation() const { return GetActorLocation() / 100.0f; }

private:
	void GenerateBlockTypes();

public:
	void BuildChunk();
};
