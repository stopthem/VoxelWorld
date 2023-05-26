// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelBlock.h"

#include "VoxelWorld/BlueprintFunctionLibraries/MeshExBlueprintFunctionLibrary.h"
#include "VoxelWorld/World/VoxelChunk.h"


// Sets default values
FVoxelBlock::FVoxelBlock()
	: VoxelChunk(nullptr), VoxelBlockParameters()
{
}

FVoxelBlock::FVoxelBlock(const FVoxelBlockParameters& VoxelBlockParameters, AVoxelChunk* VoxelChunk)
	: VoxelChunk(VoxelChunk), VoxelBlockParameters(VoxelBlockParameters)
{
}

//
// FVoxelMeshParameters FVoxelBlock::CalculateBlock() const
// {
// 	EVoxelQuadFace QuadFacesToGenerate = EVoxelQuadFace::None;
//
// 	auto CheckNeighbourForQuadFace = [&](const FVector& OffsetDirVector, const EVoxelQuadFace ToBeAddedQuadFace)
// 	{
// 		if (!HasSolidNeighbour(OffsetDirVector))
// 		{
// 			QuadFacesToGenerate |= ToBeAddedQuadFace;
// 			// UE_LOG(LogTemp, Warning, TEXT("looked from %s to metric offset %s added face %s"), *GetOffsetInMeters().ToString(), *OffsetDirVector.ToString(), *UEnum::GetValueAsString(ToBeAddedQuadFace));
// 		}
// 	};
//
// 	CheckNeighbourForQuadFace(FVector::ForwardVector, EVoxelQuadFace::Front);
// 	CheckNeighbourForQuadFace(FVector::BackwardVector, EVoxelQuadFace::Back);
// 	CheckNeighbourForQuadFace(FVector::RightVector, EVoxelQuadFace::Right);
// 	CheckNeighbourForQuadFace(FVector::LeftVector, EVoxelQuadFace::Left);
// 	CheckNeighbourForQuadFace(FVector::UpVector, EVoxelQuadFace::Up);
// 	CheckNeighbourForQuadFace(FVector::DownVector, EVoxelQuadFace::Down);
//
// 	return UMeshExBlueprintFunctionLibrary::CalculateProceduralCube(VoxelBlockParameters, QuadFacesToGenerate);
// }

// bool FVoxelBlock::HasSolidNeighbour(const FVector& OffsetDirVector) const
// {
// 	FVoxelBlock Neighbour;
// 	if (!VoxelChunk->TryGetBlockAt(GetLocalOffset() + OffsetDirVector, Neighbour))
// 	{
// 		return false;
// 	}
//
// 	if (Neighbour.GetBlockType() == EBlockType::Water || Neighbour.GetBlockType() == EBlockType::Air)
// 	{
// 		return false;
// 	}
//
// 	return true;
// }

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
