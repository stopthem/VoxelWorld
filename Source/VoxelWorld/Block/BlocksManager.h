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
	Stone,
	Air,
	Water
};

USTRUCT()
struct FBlockTextureTilingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EBlockType BlockType;

	UPROPERTY(EditAnywhere)
	FIntVector2 BlockTiling;
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

public:
	UMaterial* GetBlockMaterial() const { return BlockMeshMaterial; }

private:
	UPROPERTY(EditAnywhere, Category="Block Material")
	TObjectPtr<UMaterial> BlockMeshMaterial;

	UPROPERTY(EditAnywhere, Category="Block Material")
	TObjectPtr<UTexture2D> BlocksTexture;

	UPROPERTY(EditAnywhere, Category="Block Material")
	FVector2D TextureDimensions = FVector2D(16, 16);

	UPROPERTY(EditAnywhere, Category="Block Material")
	TArray<FBlockTextureTilingInfo> BlockTextureTilingInfos;

public:
	FVector2D GetAtlasPosOfTexture(EBlockType BlockType);

private:
	float AtlasOneTextureNormalizedValue;
};
