// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"

#include "Kismet/KismetMathLibrary.h"
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
	if (!UKismetMathLibrary::InRange_FloatFloat(Offset.Y, 0, Width, true, false))
	{
		return false;
	}

	if (!UKismetMathLibrary::InRange_FloatFloat(Offset.Z, 0, Height, true, false))
	{
		return false;
	}

	if (!UKismetMathLibrary::InRange_FloatFloat(Offset.X, 0, Depth, true, false))
	{
		return false;
	}

	out_FoundBlock = ChunkBlocks[Offset.Y][Offset.Z][Offset.X];
	return true;
}

int AVoxelChunk::Get3DElementPosInFlat(const int X, const int Y, const int Z) const
{
	return Y + Width * (Z + Depth * X);
}

void AVoxelChunk::BuildChunk(const ABlocksManager* BlocksManager)
{
	FArray3DFunctionLibrary::SetNum(ChunkBlocks, Width, Height, Depth);

	ChunkBlockTypes.SetNum(Width * Depth * Height);

	for (int i = 0; i < ChunkBlockTypes.Num(); ++i)
	{
		const int Y = i % Width;
		const int Z = (i / Width) % Height;
		const int X = i / (Width * Height);

		const float fBM = UMathExBlueprintFunctionLibrary::fBM(Y, X, 18, 0.001f, 2.0f, 4);
		UE_LOG(LogTemp, Warning, TEXT("offset in metric %s  fbm %f"), *FVector(Y,Z,X).ToString(), fBM);
		ChunkBlockTypes[i] = fBM > Z ? EBlockType::Dirt : EBlockType::Air;
	}

	FVoxelBlockParameters VoxelBlockParameters(ProceduralMeshComponent, EBlockType::Stone, BlocksManager->GetBlockMaterial());

	int32 MeshSectionGroup = 0;

	for (int x = 0; x < Depth; ++x)
	{
		for (int z = 0; z < Height; ++z)
		{
			for (int y = 0; y < Width; ++y)
			{
				VoxelBlockParameters.Offset = FVector(x, y, z) * 100.0f;
				VoxelBlockParameters.MeshSectionGroup = MeshSectionGroup;

				MeshSectionGroup++;

				VoxelBlockParameters.BlockType = ChunkBlockTypes[Get3DElementPosInFlat(x, y, z)];

				ChunkBlocks[y][z][x] = FVoxelBlock(VoxelBlockParameters, this);
			}
		}
	}

	for (int x = 0; x < Depth; ++x)
	{
		for (int z = 0; z < Height; ++z)
		{
			for (int y = 0; y < Width; ++y)
			{
				FVoxelBlock Block = ChunkBlocks[y][z][x];

				if (Block.GetBlockType() == EBlockType::Air)
				{
					continue;
				}

				Block.BuildCube();
			}
		}
	}
}
