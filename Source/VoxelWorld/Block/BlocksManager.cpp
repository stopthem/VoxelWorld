// Fill out your copyright notice in the Description page of Project Settings.


#include "BlocksManager.h"

ABlocksManager::ABlocksManager()
{
}

void ABlocksManager::BeginPlay()
{
	Super::BeginPlay();

	GetAtlasPosOfTexture(EBlockType::Dirt);
}

FVector2d ABlocksManager::GetAtlasPosOfTexture(EBlockType BlockType)
{
	if (AtlasOneTextureNormalizedValue == 0)
	{
		AtlasOneTextureNormalizedValue = 0.5f / (TextureDimensions.X / 2);
	}

	const FBlockTextureTilingInfo* FoundTilingInfo = BlockTextureTilingInfos.FindByPredicate([&](const FBlockTextureTilingInfo& BlockTextureTilingInfo)
	{
		return BlockTextureTilingInfo.BlockType == BlockType;
	});

	FVector2D BlockTiling = FVector2D(FoundTilingInfo->BlockTiling.X, FoundTilingInfo->BlockTiling.Y);
	BlockTiling.Y = TextureDimensions.Y - FoundTilingInfo->BlockTiling.Y;
	return BlockTiling * AtlasOneTextureNormalizedValue;
}
