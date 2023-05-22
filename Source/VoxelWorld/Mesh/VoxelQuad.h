// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "VoxelQuad.generated.h"

class UProceduralMeshComponent;

/*
 * EVoxelQuadFace
 *
 * Enum that holds quad face.
 */
UENUM()
enum class EVoxelQuadFace : uint8
{
	Front,
	Back,
	Right,
	Left,
	Up,
	Down
};

/*
 * AVoxelQuad
 *
 * Custom quad creator class.
 */
USTRUCT(BlueprintType)
struct VOXELWORLD_API FVoxelQuad
{
	GENERATED_BODY()

public:
	FVoxelQuad();

	FVoxelQuad(UProceduralMeshComponent* ProceduralMeshComponent, const EVoxelQuadFace QuadFace);

	void GenerateMesh(UMaterial* Material, const FVector& Offset = FVector(0), const FVector& CubeRadius = FVector(50.0f));

private:
	void EmptyArrays();

public:
	UProceduralMeshComponent* GetProceduralMeshComponent() const { return ProceduralMeshComponent; }

protected:
	UPROPERTY()
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;

public:
	EVoxelQuadFace QuadFace;

	int32 MeshSection = 0;

	TArray<FVector> Vertices;

	TArray<int32> Triangles;

	TArray<FVector> Normals;

	TArray<FProcMeshTangent> Tangents;

	TArray<FVector2d> UVs;

	TArray<FLinearColor> Colors;
};
