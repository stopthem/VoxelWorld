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

	FBlockTextureTilingInfo* FoundTilingInfo = BlockTextureTilingInfos.FindByPredicate([&](const FBlockTextureTilingInfo& BlockTextureTilingInfo)
	{
		return BlockTextureTilingInfo.BlockType == BlockType;
	});

	FoundTilingInfo->BlockTiling.Y = TextureDimensions.Y - FoundTilingInfo->BlockTiling.Y;
	return FoundTilingInfo->BlockTiling * AtlasOneTextureNormalizedValue;
}
