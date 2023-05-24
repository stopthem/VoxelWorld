// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelQuad.h"

#include "ProceduralMeshComponent.h"


FVoxelBlockParameters::FVoxelBlockParameters()
	: BlockType(EBlockType::Dirt), ProceduralMeshComponent(nullptr), Material(nullptr)
{
}

FVoxelBlockParameters::FVoxelBlockParameters(UProceduralMeshComponent* ProceduralMeshComponent, const EBlockType BlockType, UMaterial* Material)
	: BlockType(BlockType), ProceduralMeshComponent(ProceduralMeshComponent), Material(Material)
{
}

FVoxelQuad::FVoxelQuad()
	: QuadFace(EVoxelQuadFace::Front)
{
}

FVoxelQuad::FVoxelQuad(UProceduralMeshComponent* ProceduralMeshComponent, const EVoxelQuadFace QuadFace, const int32 MeshSection)
{
	this->ProceduralMeshComponent = ProceduralMeshComponent;
	this->QuadFace = QuadFace;
	this->MeshSection = MeshSection;
}

void FVoxelQuad::GenerateMesh(UMaterial* Material, const FVector& Offset, const FVector& CubeRadius)
{
	check(ProceduralMeshComponent);

	check(Material);

	EmptyArrays();

	const FProcMeshTangent TangentSetup(0.0f, 1.0f, 0.0f);

	int32 TriangleIndexCount = 0;
	int32 Point1 = TriangleIndexCount++; // Forward Top Right
	int32 Point2 = TriangleIndexCount++; // Forward Bottom Right
	int32 Point3 = TriangleIndexCount++; // Forward Top Left
	int32 Point4 = TriangleIndexCount++; // Forward Bottom Left

	FVector VerticesRotationAxis;
	float VerticesRotationAngle;

	auto SetRotationAxisAndAngle = [&](const FVector& Axis, const float Angle)
	{
		VerticesRotationAxis = Axis;
		VerticesRotationAngle = Angle;
	};

	// Circle through every EVoxelQuadFace and set their axis and angles.
	if (QuadFace == EVoxelQuadFace::Back)
	{
		SetRotationAxisAndAngle(FVector::UpVector, 180.0f);
	}
	else if (QuadFace == EVoxelQuadFace::Right)
	{
		SetRotationAxisAndAngle(FVector::UpVector, 90.0f);
	}
	else if (QuadFace == EVoxelQuadFace::Left)
	{
		SetRotationAxisAndAngle(FVector::DownVector, 90.0f);
	}
	else if (QuadFace == EVoxelQuadFace::Up)
	{
		SetRotationAxisAndAngle(FVector::LeftVector, 90.0f);
	}
	else if (QuadFace == EVoxelQuadFace::Down)
	{
		SetRotationAxisAndAngle(FVector::RightVector, 90.0f);
	}

	TArray FrontVertices =
	{
		FVector(CubeRadius.X, CubeRadius.Y, CubeRadius.Z), // Forward Top Right
		FVector(CubeRadius.X, CubeRadius.Y, -CubeRadius.Z), // Forward Bottom Right
		FVector(CubeRadius.X, -CubeRadius.Y, CubeRadius.Z), // Forward Top Left
		FVector(CubeRadius.X, -CubeRadius.Y, -CubeRadius.Z), // Forward Bottom Left
	};

	// Think of this like a cube face rotating around the 0,0,0 point in the axis with angle.
	TArray RotatedVertices =
	{
		FrontVertices[0].RotateAngleAxis(VerticesRotationAngle, VerticesRotationAxis), // Rotated Top Right
		FrontVertices[1].RotateAngleAxis(VerticesRotationAngle, VerticesRotationAxis), // Rotated Bottom Right
		FrontVertices[2].RotateAngleAxis(VerticesRotationAngle, VerticesRotationAxis), // Rotated Top Left
		FrontVertices[3].RotateAngleAxis(VerticesRotationAngle, VerticesRotationAxis), // Rotated Bottom Left
	};

	Vertices = {
		RotatedVertices[3] + Offset,
		RotatedVertices[2] + Offset,
		RotatedVertices[1] + Offset,
		RotatedVertices[0] + Offset,
	};

	Triangles =
	{
		Point1,
		Point2,
		Point3,
		Point4,
		Point3,
		Point2
	};

	// Top Left - Bottom Right x Top Left - Top Right
	const FVector QuadNormal = FVector::CrossProduct(Vertices[2] - Vertices[1], Vertices[2] - Vertices[0]).GetSafeNormal();

	for (int i = 0; i < 4; ++i)
	{
		Normals.Add(QuadNormal);

		Tangents.Add(TangentSetup);

		Colors.Add(FLinearColor::Yellow);
	}

	UVs =
	{
		FVector2D(0.0f, 1.0f),
		FVector2D(0.0f, 0.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(1.0f, 0.0f),
	};

	ProceduralMeshComponent->CreateMeshSection_LinearColor(MeshSection, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
	ProceduralMeshComponent->SetMaterial(MeshSection, Material);
}

void FVoxelQuad::EmptyArrays()
{
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	UVs.Empty();
	Colors.Empty();
	Tangents.Empty();
}
