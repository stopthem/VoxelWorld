// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelBlock.h"

#include "BlocksManager.h"
#include "ProceduralMeshComponent.h"
#include "VoxelWorld/VoxelWorldGameModeBase.h"
#include "VoxelWorld/BlueprintFunctionLibraries/MeshExBlueprintFunctionLibrary.h"


// Sets default values
AVoxelBlock::AVoxelBlock()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVoxelBlock::BeginPlay()
{
	Super::BeginPlay();

	UMeshExBlueprintFunctionLibrary::CreateProceduralCube(ProceduralMeshComponent, BlockMeshMaterial, FVector(0), MeshCubeRadius);

	AVoxelWorldGameModeBase::Get(GetWorld())->OnManagersSpawned.AddDynamic(this, &ThisClass::SetMaterialTiling);
}

void AVoxelBlock::SetMaterialTiling()
{
	AVoxelWorldGameModeBase* VoxelGameModeBase = AVoxelWorldGameModeBase::Get(GetWorld());

	check(VoxelGameModeBase);

	BlocksManager = VoxelGameModeBase->GetManager<ABlocksManager>();

	const FVector2D BlockTextureTiling = BlocksManager->GetAtlasPosOfTexture(BlockType);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *BlockTextureTiling.ToString());
	for (int i = 0; i < ProceduralMeshComponent->GetMaterials().Num(); ++i)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(ProceduralMeshComponent->GetMaterial(i), this);
		DynamicMaterial->SetScalarParameterValue("Tile_U", BlockTextureTiling.X);
		DynamicMaterial->SetScalarParameterValue("Tile_V", BlockTextureTiling.Y);

		ProceduralMeshComponent->SetMaterial(i, DynamicMaterial);
	}

	VoxelGameModeBase->OnManagersSpawned.RemoveDynamic(this, &ThisClass::SetMaterialTiling);
}
