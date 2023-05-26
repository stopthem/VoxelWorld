// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"

#include "ProceduralMeshComponent.h"
#include "VoxelWorldManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "VoxelWorld/VoxelWorldGameModeBase.h"
#include "VoxelWorld/Block/BlocksManager.h"
#include "VoxelWorld/Block/VoxelBlock.h"
#include "VoxelWorld/BlueprintFunctionLibraries/MeshExBlueprintFunctionLibrary.h"
#include "VoxelWorld/CodeFunctionLibraries/Array3DFunctionLibrary.h"
#include "VoxelWorld/Extra/FastNoiseLite.h"


AVoxelChunk::AVoxelChunk()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMeshComponent->SetupAttachment(RootComponent);
}

bool AVoxelChunk::TryGetBlockAt(const FVector& BlockArrayPos, FVoxelBlock& out_FoundBlock)
{
	if (!IsWithinChunkBounds(BlockArrayPos))
	{
		return false;
	}

	out_FoundBlock = ChunkBlocks[BlockArrayPos.Y][BlockArrayPos.Z][BlockArrayPos.X];

	return true;
}

bool AVoxelChunk::IsWithinChunkBounds(const FVector& BlockArrayPos)
{
	if (!UKismetMathLibrary::InRange_FloatFloat(BlockArrayPos.Y, 0, AVoxelWorldManager::Chunk_Dimensions.Y, true, false))
	{
		return false;
	}

	if (!UKismetMathLibrary::InRange_FloatFloat(BlockArrayPos.Z, 0, AVoxelWorldManager::Chunk_Dimensions.Z, true, false))
	{
		return false;
	}

	if (!UKismetMathLibrary::InRange_FloatFloat(BlockArrayPos.X, 0, AVoxelWorldManager::Chunk_Dimensions.X, true, false))
	{
		return false;
	}

	return true;
}

EVoxelQuadFace AVoxelChunk::GetNonSolidNeighbourFaces(const FVector& BlockArrayPos)
{
	// We have to set it to None, otherwise flag calculation is wrong.
	EVoxelQuadFace NonSolidQuadFaces = EVoxelQuadFace::None;

	// A nice little local function to prevent us to type much more.
	auto CheckNeighbourForNonSolidFace = [&](const FVector& Direction, const EVoxelQuadFace ToBeAddedQuadFace)
	{
		const FVector NeighbourOffset = BlockArrayPos + Direction;

		// const bool bIsWithinBounds = IsWithinChunkBounds(NeighbourOffset);

		// Find the corresponding block type of neighbour block.
		// We don't get the block directly because when we iterate through our 3d array, not all of the blocks are initialized and they are default which causes wrong calculation.
		const int NeighbourBlockTypeIndex = FArray3DFunctionLibrary::Get3DPosInFlat(ChunkBlocks, NeighbourOffset.X, NeighbourOffset.Y, NeighbourOffset.Z);

		// FColor color = FColor::Green;
		// if (!bIsWithinBounds)
		// {
		// 	color = FColor::Red;
		// }
		// if (bIsWithinBounds && ChunkBlockTypes[NeighbourBlockTypeIndex] == EBlockType::Air)
		// {
		// 	color = FColor::Cyan;
		// }
		if (!IsWithinChunkBounds(NeighbourOffset) || ChunkBlockTypes[NeighbourBlockTypeIndex] == EBlockType::Air)
		{
			// Add given face flag to our flags.
			NonSolidQuadFaces |= ToBeAddedQuadFace;
			// UE_LOG(LogTemp, Warning, TEXT("looked from %s to metric offset %s added face %s"), *BlockOffset.ToString(), *Direction.ToString(), *UEnum::GetValueAsString(ToBeAddedQuadFace));
		}

		// DrawDebugLine(GetWorld(), BlockArrayPos, BlockArrayPos + Direction * 25.0f, color, true, -1, 0, 5);
	};

	CheckNeighbourForNonSolidFace(FVector::ForwardVector, EVoxelQuadFace::Front);
	CheckNeighbourForNonSolidFace(FVector::BackwardVector, EVoxelQuadFace::Back);
	CheckNeighbourForNonSolidFace(FVector::RightVector, EVoxelQuadFace::Right);
	CheckNeighbourForNonSolidFace(FVector::LeftVector, EVoxelQuadFace::Left);
	CheckNeighbourForNonSolidFace(FVector::UpVector, EVoxelQuadFace::Up);
	CheckNeighbourForNonSolidFace(FVector::DownVector, EVoxelQuadFace::Down);

	return NonSolidQuadFaces;
}

void AVoxelChunk::GenerateBlockTypes()
{
	// Set our block types num.
	ChunkBlockTypes.SetNum(AVoxelWorldManager::Chunk_Dimensions.Y * AVoxelWorldManager::Chunk_Dimensions.X * AVoxelWorldManager::Chunk_Dimensions.Z);


	// Determine the air and solid blocks with the fBM(fractal brownian motion).
	// for (int i = 0; i < ChunkBlockTypes.Num(); ++i)
	// {
	// 	const float Y = (i % AVoxelWorldManager::Chunk_Dimensions.Y) + GetActorLocation().Y / 100;
	// 	const float Z = ((i / AVoxelWorldManager::Chunk_Dimensions.Y) % AVoxelWorldManager::Chunk_Dimensions.Z) + GetActorLocation().Z / 100;
	// 	const float X = (i / (AVoxelWorldManager::Chunk_Dimensions.Y * AVoxelWorldManager::Chunk_Dimensions.Z)) + GetActorLocation().X / 100;
	//
	// 	const float fBM = Noise.GetNoise(X, Y, Z);
	// 	// UE_LOG(LogTemp, Warning, TEXT("offset in metric %s  fbm %f"), *FVector(Y,Z,X).ToString(), fBM);
	// 	ChunkBlockTypes[i] = fBM < 0 ? EBlockType::Dirt : EBlockType::Air;
	// }

	// Set the height map.

	// Create our noise.
	FastNoiseLite Noise;

	Noise.SetFrequency(NoiseFrequency);
	Noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise.SetFractalType(FastNoiseLite::FractalType_FBm);

	const FVector MetricActorLocation = GetActorLocation() / 100;

	for (int x = 0; x < AVoxelWorldManager::Chunk_Dimensions.Z; ++x)
	{
		for (int y = 0; y < AVoxelWorldManager::Chunk_Dimensions.Y; ++y)
		{
			const float XLocation = x + MetricActorLocation.X;
			const float YLocation = y + MetricActorLocation.Y;

			const int Height = FMath::Clamp(FMath::RoundToInt((Noise.GetNoise(XLocation, YLocation) + 1) * AVoxelWorldManager::Chunk_Dimensions.X / 2), 0, AVoxelWorldManager::Chunk_Dimensions.X);

			for (int h = 0; h < Height; h++)
			{
				ChunkBlockTypes[FArray3DFunctionLibrary::Get3DPosInFlat(ChunkBlocks, x, y, h)] = EBlockType::Dirt;
			}

			for (int s = Height; s < AVoxelWorldManager::Chunk_Dimensions.X; s++)
			{
				ChunkBlockTypes[FArray3DFunctionLibrary::Get3DPosInFlat(ChunkBlocks, x, y, s)] = EBlockType::Air;
			}
		}
	}
}

void AVoxelChunk::BuildChunk()
{
	// Set our 3d array num.
	FArray3DFunctionLibrary::SetNum(ChunkBlocks, AVoxelWorldManager::Chunk_Dimensions.Y, AVoxelWorldManager::Chunk_Dimensions.Z, AVoxelWorldManager::Chunk_Dimensions.X);

	GenerateBlockTypes();

	const ABlocksManager* BlocksManager = AVoxelWorldGameModeBase::Get(GetWorld())->GetManager<ABlocksManager>();

	// We are defaulting them because we will probably call those again.
	ChunkMeshParams = FVoxelMeshParameters();
	VertexCount = 0;

	for (int x = 0; x < AVoxelWorldManager::Chunk_Dimensions.X; ++x)
	{
		for (int z = 0; z < AVoxelWorldManager::Chunk_Dimensions.Z; ++z)
		{
			for (int y = 0; y < AVoxelWorldManager::Chunk_Dimensions.Y; ++y)
			{
				const EBlockType BlockType = ChunkBlockTypes[FArray3DFunctionLibrary::Get3DPosInFlat(ChunkBlocks, x, y, z)];

				FVoxelBlockParameters VoxelBlockParameters;
				// This is the world offset, independent of array position of the block.
				VoxelBlockParameters.Offset = FVector(x, y, z) * 100.0f + GetActorLocation();
				VoxelBlockParameters.BlockType = BlockType;

				ChunkBlocks[y][z][x] = FVoxelBlock(VoxelBlockParameters, this);

				if (BlockType == EBlockType::Air)
				{
					continue;
				}

				FVoxelMeshParameters BlockMeshParams = UMeshExBlueprintFunctionLibrary::CalculateProceduralCube(VoxelBlockParameters, GetNonSolidNeighbourFaces(FVector(x, y, z)), VertexCount);
				// We are incrementing this by the last created block's vertices because every block needs their unique triangle points.
				VertexCount += BlockMeshParams.Vertices.Num();

				ChunkMeshParams.AppendOtherMeshParameters(BlockMeshParams);
			}
		}
	}

	// Create mesh.
	ProceduralMeshComponent->CreateMeshSection_LinearColor(0, ChunkMeshParams.Vertices, ChunkMeshParams.Triangles, ChunkMeshParams.Normals, ChunkMeshParams.UVs,
	                                                       TArray<FLinearColor>(), ChunkMeshParams.Tangents, false);

	// Set material.
	ProceduralMeshComponent->SetMaterial(0, BlocksManager->GetBlockMaterial());

	// Set our name accordingly to our world position.
	SetActorLabel("Chunk_" + FString::FromInt(GetActorLocation().X) + "_" + FString::FromInt(GetActorLocation().Y) + "_" + FString::FromInt(GetActorLocation().Z));
}
