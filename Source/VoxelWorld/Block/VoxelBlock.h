// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/Mesh/VoxelQuad.h"
#include "VoxelBlock.generated.h"

class ABlocksManager;
enum class EBlockType : uint8;
enum class EVoxelQuadFace : uint8;
class UProceduralMeshComponent;
/*
 * AVoxelBlock
 *
 * Base class that all blocks in the game has.
 */
UCLASS()
class VOXELWORLD_API AVoxelBlock : public AActor
{
	GENERATED_BODY()

public:
	AVoxelBlock();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Block")
	EBlockType BlockType;

	UPROPERTY(EditAnywhere, Category="Block")
	FVector MeshCubeRadius = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, Category="BlockMesh")
	TObjectPtr<UMaterial> BlockMeshMaterial;

private:
	UFUNCTION()
	void SetMaterialTiling();

protected:
	UPROPERTY(VisibleAnywhere, Category="BlockMesh")
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

protected:
	UPROPERTY()
	TObjectPtr<ABlocksManager> BlocksManager;
};
