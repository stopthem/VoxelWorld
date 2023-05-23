// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshExBlueprintFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"
#include "VoxelWorld/Mesh/VoxelQuad.h"

void UMeshExBlueprintFunctionLibrary::CreateProceduralCube(const FVoxelMeshParameters& VoxelMeshParameters, const EVoxelQuadFace QuadFaces)
{
	check(VoxelMeshParameters.ProceduralMeshComponent);

	check(VoxelMeshParameters.Material);

	auto GenerateQuad = [&](EVoxelQuadFace QuadFace)
	{
		const int32 MeshSection = 6 * VoxelMeshParameters.MeshSectionGroup + UKismetMathLibrary::Log(static_cast<int32>(QuadFace), 2);

		// First we fill crucial parameters with the constructor.
		FVoxelQuad Quad(VoxelMeshParameters.ProceduralMeshComponent, QuadFace, MeshSection);

		// Then we generate the quad.
		Quad.GenerateMesh(VoxelMeshParameters.Material, VoxelMeshParameters.Offset, VoxelMeshParameters.CubeRadius);
	};

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Front))
	{
		GenerateQuad(EVoxelQuadFace::Front);
	}

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Back))
	{
		GenerateQuad(EVoxelQuadFace::Back);
	}

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Right))
	{
		GenerateQuad(EVoxelQuadFace::Right);
	}

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Left))
	{
		GenerateQuad(EVoxelQuadFace::Left);
	}

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Up))
	{
		GenerateQuad(EVoxelQuadFace::Up);
	}

	if (EnumHasAnyFlags(QuadFaces, EVoxelQuadFace::Down))
	{
		GenerateQuad(EVoxelQuadFace::Down);
	}
}
