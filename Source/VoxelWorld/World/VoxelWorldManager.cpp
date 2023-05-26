// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorldManager.h"

#include "VoxelChunk.h"
#include "VoxelWorld/VoxelWorldGameModeBase.h"


AVoxelWorldManager::AVoxelWorldManager()
{
}

void AVoxelWorldManager::BeginPlay()
{
	Super::BeginPlay();

	// We bind to this because we want BlocksManager to be available.
	AVoxelWorldGameModeBase::Get(GetWorld())->OnManagersSpawned.AddDynamic(this, &ThisClass::OnManagersSpawned);
}

void AVoxelWorldManager::OnManagersSpawned(AVoxelWorldGameModeBase* VoxelWorldGameModeBase)
{
	for (int x = 0; x < World_Dimensions.Y; ++x)
	{
		for (int z = 0; z < World_Dimensions.X; ++z)
		{
			const FVector ChunkLocation = FVector(x * Chunk_Dimensions.X * 50.0f, z * Chunk_Dimensions.Y * 50.0f, 0);
			AVoxelChunk* SpawnedChunk = GetWorld()->SpawnActor<AVoxelChunk>(ChunkBlueprint, ChunkLocation, FRotator(0));

			SpawnedChunk->BuildChunk();

			SpawnedChunk->SetFolderPath("Chunks");
		}
	}
}
