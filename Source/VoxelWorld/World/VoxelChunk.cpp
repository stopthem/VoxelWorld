// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"

#include "VoxelWorld/VoxelWorldGameModeBase.h"
#include "VoxelWorld/Block/BlocksManager.h"
#include "VoxelWorld/Block/VoxelBlock.h"
#include "VoxelWorld/BlueprintFunctionLibraries/MathExBlueprintFunctionLibrary.h"
#include "VoxelWorld/CodeFunctionLibraries/Array3DFunctionLibrary.h"


AVoxelChunk::AVoxelChunk()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMeshComponent->SetupAttachment(RootComponent);
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();

	AVoxelWorldGameModeBase::Get(GetWorld())->OnManagersSpawned.AddDynamic(this, &ThisClass::OnManagersSpawned);
}

void AVoxelChunk::OnManagersSpawned(AVoxelWorldGameModeBase* VoxelWorldGameModeBase)
{
	const ABlocksManager* BlocksManager = VoxelWorldGameModeBase->GetManager<ABlocksManager>();

	BuildChunk(BlocksManager);
}

bool AVoxelChunk::TryGetBlockAt(const FVector& Offset, FVoxelBlock& out_FoundBlock)
{
	if (!UMathExBlueprintFunctionLibrary::IsWithinRange(Offset.X, 0, Width))
	{
		return false;
	}

	if (!UMathExBlueprintFunctionLibrary::IsWithinRange(Offset.Y, 0, Height))
	{
		return false;
	}

	if (!UMathExBlueprintFunctionLibrary::IsWithinRange(Offset.Z, 0, Depth))
	{
		return false;
	}

	out_FoundBlock = ChunkVoxelBlocks[Offset.X][Offset.Y][Offset.Z];
	return true;
}

int AVoxelChunk::Get3DElementPosInFlat(const int X, const int Y, const int Z) const
{
	return X + Width * (Y + Depth * Z);
}

void AVoxelChunk::BuildChunk(const ABlocksManager* BlocksManager)
{
	FArray3DFunctionLibrary::SetNum(ChunkVoxelBlocks, Width, Height, Depth);

	ChunkBlockTypes.SetNum(Width * Height * Depth);

	FVoxelMeshParameters VoxelMeshParameters(ProceduralMeshComponent, EBlockType::Stone, BlocksManager->GetBlockMaterial());

	int32 MeshSectionGroup = 0;

	for (int z = 0; z < Depth; ++z)
	{
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; ++x)
			{
				VoxelMeshParameters.Offset = FVector(x, y, z) * 100.0f;
				VoxelMeshParameters.MeshSectionGroup = MeshSectionGroup;

				MeshSectionGroup++;

				ChunkVoxelBlocks[x][y][z] = FVoxelBlock(VoxelMeshParameters, this);

				ChunkBlockTypes[Get3DElementPosInFlat(x, y, z)] = VoxelMeshParameters.BlockType;
			}
		}
	}
}
