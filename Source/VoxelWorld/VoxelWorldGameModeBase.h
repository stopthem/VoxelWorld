// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelWorldGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoxelWorldGameMode_OnManagersSpawned, AVoxelWorldGameModeBase*, VoxelWorldGameModeBase);

class UGameplayStatics;
/**
 * AVoxelWorldGameModeBase
 *
 * Game mode base class that this game uses.
 */
UCLASS()
class VOXELWORLD_API AVoxelWorldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVoxelWorldGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	static AVoxelWorldGameModeBase* Get(const UWorld* World)
	{
		return Cast<AVoxelWorldGameModeBase>(World->GetAuthGameMode());
	}

	// Broadcasted when all the managers in ToSpawnManagers are spawned.
	UPROPERTY(BlueprintAssignable)
	FVoxelWorldGameMode_OnManagersSpawned OnManagersSpawned;

public:
	// Holder of the manager blueprints.
	UPROPERTY(EditAnywhere, Category="Managers")
	TArray<TSubclassOf<AActor>> ToSpawnManagers;

	// Get manager of the given type.
	// Only get manager if given type is derived from AActor.
	template <typename TManagerClass>
	typename TEnableIf<TIsDerivedFrom<TManagerClass, AActor>::IsDerived, TManagerClass*>::Type GetManager();

private:
	UPROPERTY()
	TArray<AActor*> SpawnedManagers;

	void SpawnManagers();

	AActor* SpawnManager(const TSubclassOf<AActor> ActorClassToSpawn);
};

template <typename TManagerClass>
typename TEnableIf<TIsDerivedFrom<TManagerClass, AActor>::IsDerived, TManagerClass*>::Type AVoxelWorldGameModeBase::GetManager()
{
	if (auto FoundManager = SpawnedManagers.FindByPredicate([](const AActor* Manager)
	{
		return Cast<TManagerClass>(Manager);
	}))
	{
		return reinterpret_cast<TManagerClass*>(*FoundManager);
	}

	UE_LOG(LogTemp, Warning, TEXT("no manager found with the type -> %s"), *GetTypeName<TManagerClass>());
	return nullptr;
}
