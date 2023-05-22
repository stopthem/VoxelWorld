// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlocksManager.generated.h"

UENUM()
enum class EBlockType : uint8
{
	Grass,
	Dirt,
	Stone
};

USTRUCT()
struct FBlockTextureTilingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EBlockType BlockType;

	UPROPERTY(EditAnywhere)
	FVector2D BlockTiling;
};

/*
 * ABlocksManager
 *
 * Manager class of the blocks.
 */
UCLASS()
class VOXELWORLD_API ABlocksManager : public AActor
{
	GENERATED_BODY()

public:
	ABlocksManager();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Block Texture")
	TObjectPtr<UTexture2D> BlocksTexture;

	UPROPERTY(EditAnywhere, Category="Block Texture")
	FVector2D TextureDimensions = FVector2D(16, 16);

	UPROPERTY(EditAnywhere, Category="Block Texture")
	TArray<FBlockTextureTilingInfo> BlockTextureTilingInfos;

public:
	FVector2D GetAtlasPosOfTexture(EBlockType BlockType);

private:
	float AtlasOneTextureNormalizedValue;
};
