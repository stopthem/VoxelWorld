// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshExBlueprintFunctionLibrary.h"

#include "VoxelWorld/Mesh/VoxelQuad.h"

void UMeshExBlueprintFunctionLibrary::CreateProceduralCube(UProceduralMeshComponent* ProceduralMeshComponent, UMaterial* Material, const FVector& Offset, const FVector& CubeRadius)
{
	check(ProceduralMeshComponent);

	check(Material);

	FVoxelQuad FrontQuad(ProceduralMeshComponent, EVoxelQuadFace::Front);
	FrontQuad.GenerateMesh(Material, Offset, CubeRadius);

	FVoxelQuad BackQuad(ProceduralMeshComponent, EVoxelQuadFace::Back);
	BackQuad.GenerateMesh(Material, Offset, CubeRadius);

	FVoxelQuad RightQuad(ProceduralMeshComponent, EVoxelQuadFace::Right);
	RightQuad.GenerateMesh(Material, Offset, CubeRadius);

	FVoxelQuad LeftQuad(ProceduralMeshComponent, EVoxelQuadFace::Left);
	LeftQuad.GenerateMesh(Material, Offset, CubeRadius);

	FVoxelQuad UpQuad(ProceduralMeshComponent, EVoxelQuadFace::Up);
	UpQuad.GenerateMesh(Material, Offset, CubeRadius);

	FVoxelQuad DownQuad(ProceduralMeshComponent, EVoxelQuadFace::Down);
	DownQuad.GenerateMesh(Material, Offset, CubeRadius);
}
