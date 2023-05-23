// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld/Block/BlocksManager.h"
#include "VoxelQuad.generated.h"

class UProceduralMeshComponent;

/*
 * FVoxelMeshParameters
 *
 * Holds variables about Voxel Mesh.
 */
USTRUCT(BlueprintType)
struct FVoxelMeshParameters
{
	GENERATED_BODY()

public:
	FVoxelMeshParameters();

	FVoxelMeshParameters(UProceduralMeshComponent* ProceduralMeshComponent, const EBlockType BlockType, UMaterial* Material);

	UPROPERTY(EditAnywhere)
	EBlockType BlockType;

	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent* ProceduralMeshComponent;

	// Material of the quad.
	UPROPERTY(EditAnywhere)
	UMaterial* Material;

	// Offset of the quad from zero vector.
	UPROPERTY(EditAnywhere)
	FVector Offset = FVector(0);

	// Radius of the will be created quads.
	UPROPERTY(EditAnywhere)
	FVector CubeRadius = FVector(50.0f);

	// This is purely for combining more than one quads.
	// Mesh section group is incremented by one and represents a group for quad sides. Ex : MeshSectionGroup = 1, quad Mesh Sections = 7,8,9,10,11,12
	UPROPERTY(EditAnywhere)
	int32 MeshSectionGroup = 0;
};

/*
 * EVoxelQuadFace
 *
 * Enum that holds quad face.
 */
UENUM()
enum class EVoxelQuadFace : uint8
{
	None = 0 UMETA(Hidden),
	Front = 1 << 0,
	Back = 1 << 1,
	Right = 1 << 2,
	Left = 1 << 3,
	Up = 1 << 4,
	Down = 1 << 5,
	All = Front | Back | Right | Left | Up | Down
};

ENUM_CLASS_FLAGS(EVoxelQuadFace);

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

	// This constructor doesn't really construct it, what it really does is setting crucial variables.
	FVoxelQuad(UProceduralMeshComponent* ProceduralMeshComponent, const EVoxelQuadFace QuadFace, const int32 MeshSection = 0);

	// Generate the actual quad.
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
