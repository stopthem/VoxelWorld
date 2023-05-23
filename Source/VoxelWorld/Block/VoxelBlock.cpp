// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelBlock.h"

#include "BlocksManager.h"
#include "VoxelWorld/BlueprintFunctionLibraries/MeshExBlueprintFunctionLibrary.h"
#include "VoxelWorld/World/VoxelChunk.h"


// Sets default values
FVoxelBlock::FVoxelBlock()
	: BlockType(EBlockType::Dirt), VoxelChunk(nullptr)
{
}

FVoxelBlock::FVoxelBlock(const FVoxelMeshParameters& VoxelMeshParameters, AVoxelChunk* VoxelChunk)
	: BlockType(VoxelMeshParameters.BlockType), VoxelChunk(VoxelChunk), Offset(VoxelMeshParameters.Offset)
{
	EVoxelQuadFace QuadFacesToGenerate;

	auto CheckNeighbourForQuadFace = [&](const FVector& OffsetDirVector, const EVoxelQuadFace ToBeAddedQuadFace)
	{
		if (!HasSolidNeighbour(OffsetDirVector))
		{
			QuadFacesToGenerate |= ToBeAddedQuadFace;
		}
	};

	CheckNeighbourForQuadFace(FVector::ForwardVector, EVoxelQuadFace::Front);
	CheckNeighbourForQuadFace(FVector::BackwardVector, EVoxelQuadFace::Back);
	CheckNeighbourForQuadFace(FVector::RightVector, EVoxelQuadFace::Right);
	CheckNeighbourForQuadFace(FVector::LeftVector, EVoxelQuadFace::Left);
	CheckNeighbourForQuadFace(FVector::UpVector, EVoxelQuadFace::Up);
	CheckNeighbourForQuadFace(FVector::DownVector, EVoxelQuadFace::Down);

	UMeshExBlueprintFunctionLibrary::CreateProceduralCube(VoxelMeshParameters, QuadFacesToGenerate);
}

bool FVoxelBlock::HasSolidNeighbour(const FVector& OffsetDirVector) const
{
	FVoxelBlock Neighbour;
	if (!VoxelChunk->TryGetBlockAt(Offset + OffsetDirVector, Neighbour))
	{
		return false;
	}

	if (Neighbour.GetBlockType() == EBlockType::Water || Neighbour.GetBlockType() == EBlockType::Air)
	{
		// UE_LOG(LogTemp, Warning, TEXT("from %s dir vector %s is air or water "), *Offset.ToString(), *(Offset+OffsetDirVector).ToString());
		return false;
	}

	return true;
}

// void FVoxelBlock::SetMaterialTiling()
// {
// 	AVoxelWorldGameModeBase* VoxelGameModeBase = AVoxelWorldGameModeBase::Get(GetWorld());
//
// 	check(VoxelGameModeBase);
//
// 	BlocksManager = VoxelGameModeBase->GetManager<ABlocksManager>();
//
// 	const FVector2D BlockTextureTiling = BlocksManager->GetAtlasPosOfTexture(BlockType);
//
// 	for (int i = 0; i < ProceduralMeshComponent->GetMaterials().Num(); ++i)
// 	{
// 		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(ProceduralMeshComponent->GetMaterial(i), this);
// 		DynamicMaterial->SetScalarParameterValue("Tile_U", BlockTextureTiling.X);
// 		DynamicMaterial->SetScalarParameterValue("Tile_V", BlockTextureTiling.Y);
//
// 		ProceduralMeshComponent->SetMaterial(i, DynamicMaterial);
// 	}
//
// 	VoxelGameModeBase->OnManagersSpawned.RemoveDynamic(this, &ThisClass::SetMaterialTiling);
// }
