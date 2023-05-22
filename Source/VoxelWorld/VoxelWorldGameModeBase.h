// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VoxelWorldGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoxelWorldGameMode_OnManagersSpawned);

class UGameplayStatics;
/**
 * 
 */
UCLASS()
class VOXELWORLD_API AVoxelWorldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	static AVoxelWorldGameModeBase* Get(const UWorld* World)
	{
		return Cast<AVoxelWorldGameModeBase>(World->GetAuthGameMode());
	}

	UPROPERTY(BlueprintAssignable)
	FVoxelWorldGameMode_OnManagersSpawned OnManagersSpawned;

public:
	UPROPERTY(EditAnywhere, Category="Managers")
	TArray<TSubclassOf<AActor>> ToSpawnManagers;

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
