// Copyright Epic Games, Inc. All Rights Reserved.


#include "VoxelWorldGameModeBase.h"

AVoxelWorldGameModeBase::AVoxelWorldGameModeBase()
{
}

void AVoxelWorldGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnManagers();
}

void AVoxelWorldGameModeBase::SpawnManagers()
{
	for (TSubclassOf<AActor> ToSpawnManagerClass : ToSpawnManagers)
	{
		if (SpawnedManagers.FindByPredicate([&](const AActor* Manager)
		{
			return ToSpawnManagerClass->StaticClass() == Manager->StaticClass();
		}))
		{
			continue;
		}

		SpawnManager(ToSpawnManagerClass);
	}

	OnManagersSpawned.Broadcast(this);
}

AActor* AVoxelWorldGameModeBase::SpawnManager(const TSubclassOf<AActor> ActorClassToSpawn)
{
	AActor* Manager = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, FVector::ZeroVector, FRotator::ZeroRotator);
	Manager->SetFolderPath(FName("Managers"));

	SpawnedManagers.Add(Manager);

	return Manager;
}
