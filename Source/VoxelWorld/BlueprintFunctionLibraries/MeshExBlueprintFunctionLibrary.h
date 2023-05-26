// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshExBlueprintFunctionLibrary.generated.h"

enum class EBlockType : uint8;
class UProceduralMeshComponent;
/*
 * FVoxelBlockParameters
 *
 * Holds variables about Voxel Mesh.
 */
USTRUCT(BlueprintType)
struct FVoxelBlockParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EBlockType BlockType;

	// Offset of the quad from zero vector.
	UPROPERTY(EditAnywhere)
	FVector Offset = FVector(0);

	// Radius of the will be created quads.
	UPROPERTY(EditAnywhere)
	FVector CubeRadius = FVector(50.0f);
};

/*
 * FVoxelMeshParameters
 *
 * Holding information about crucial mesh parameters.
 */
USTRUCT()
struct FVoxelMeshParameters
{
	GENERATED_BODY()

public:
	TArray<FVector> Vertices;

	TArray<int32> Triangles;

	TArray<FVector> Normals;

	TArray<FProcMeshTangent> Tangents;

	TArray<FVector2D> UVs;

	void AppendOtherMeshParameters(const FVoxelMeshParameters& OtherVoxelMeshParams);
};

/*
 * EVoxelQuadFace
 *
 * Enum that holds quad face.
 */
UENUM(meta=(BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))
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

ENUM_CLASS_FLAGS(EVoxelQuadFace)

/**
 * UMeshExBlueprintFunctionLibrary
 *
 * Utility functions for meshes.
 */
UCLASS(BlueprintType)
class UMeshExBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FVoxelMeshParameters CalculateProceduralCube(const FVoxelBlockParameters& VoxelBlockParameters, EVoxelQuadFace QuadFaces = EVoxelQuadFace::All, const int32 VertexCount = 0);

	static FVoxelMeshParameters CalculateQuad(int32 VertexCount, EVoxelQuadFace QuadFaceToCalculate, const FVector& Offset, const FVector& CubeRadius = FVector(50.0f));
};
