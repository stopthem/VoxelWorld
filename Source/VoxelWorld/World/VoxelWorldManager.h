// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5Coro/Coroutine.h"
#include "VoxelWorldManager.generated.h"

class AVoxelWorldGameModeBase;
class AVoxelChunk;

UCLASS()
class VOXELWORLD_API AVoxelWorldManager : public AActor
{
	GENERATED_BODY()

public:
	AVoxelWorldManager();

	inline static const FIntVector World_Dimensions = FIntVector(10);
	inline static const FIntVector Chunk_Dimensions = FIntVector(10);

protected:
	virtual void BeginPlay() override;

private:
	// Chunk blueprint that we will spawn.
	UPROPERTY(EditAnywhere, Category="Chunk")
	TSubclassOf<AVoxelChunk> ChunkBlueprint;

private:
	UFUNCTION()
	void OnManagersSpawned(AVoxelWorldGameModeBase* VoxelWorldGameModeBase);

	UE5Coro::TCoroutine<void> BuildChunks() const;
};
