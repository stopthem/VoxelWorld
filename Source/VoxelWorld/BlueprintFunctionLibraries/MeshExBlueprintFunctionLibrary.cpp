// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshExBlueprintFunctionLibrary.h"

#include "ProceduralMeshComponent.h"

void FVoxelMeshParameters::AppendOtherMeshParameters(const FVoxelMeshParameters& OtherVoxelMeshParams)
{
	Vertices.Append(OtherVoxelMeshParams.Vertices);
	Triangles.Append(OtherVoxelMeshParams.Triangles);
	Normals.Append(OtherVoxelMeshParams.Normals);
	UVs.Append(OtherVoxelMeshParams.UVs);
	Tangents.Append(OtherVoxelMeshParams.Tangents);
}

FVoxelMeshParameters UMeshExBlueprintFunctionLibrary::CalculateProceduralCube(const FVoxelBlockParameters& VoxelBlockParameters, const EVoxelQuadFace QuadFaces, const int32 VertexCount)
{
	FVoxelMeshParameters VoxelMeshParameters;

	// Local function to keep us from typing much more.
	auto GenerateQuad = [&](const EVoxelQuadFace CheckFace)
	{
		// If the given QuadFaces flag has the given CheckFace flag, calculate a quad accordingly.
		if (EnumHasAnyFlags(QuadFaces, CheckFace))
		{
			VoxelMeshParameters.AppendOtherMeshParameters(CalculateQuad(VertexCount + VoxelMeshParameters.Vertices.Num(), CheckFace, VoxelBlockParameters.Offset, VoxelBlockParameters.CubeRadius));
		}
	};

	GenerateQuad(EVoxelQuadFace::Front);
	GenerateQuad(EVoxelQuadFace::Back);
	GenerateQuad(EVoxelQuadFace::Right);
	GenerateQuad(EVoxelQuadFace::Left);
	GenerateQuad(EVoxelQuadFace::Up);
	GenerateQuad(EVoxelQuadFace::Down);

	return VoxelMeshParameters;
}

FVoxelMeshParameters UMeshExBlueprintFunctionLibrary::CalculateQuad(const int32 VertexCount, const EVoxelQuadFace QuadFaceToCalculate, const FVector& Offset, const FVector& CubeRadius)
{
	FVoxelMeshParameters VoxelMeshParameters;

	const FProcMeshTangent TangentSetup(0.0f, 1.0f, 0.0f);

	// Our triangle points must be unique inside ProceduralMeshComponent's vertices.
	// That's why we initialize TriangleIndexCount with VertexCount. 
	int32 TriangleIndexCount = VertexCount;
	int32 Point1 = TriangleIndexCount++; // Forward Top Right
	int32 Point2 = TriangleIndexCount++; // Forward Bottom Right
	int32 Point3 = TriangleIndexCount++; // Forward Top Left
	int32 Point4 = TriangleIndexCount++; // Forward Bottom Left

	FVector VerticesRotationAxis;
	float VerticesRotationAngle;

	// Local function to keep us from typing much more.
	auto SetRotationAxisAndAngle = [&](const FVector& Axis, const float Angle)
	{
		VerticesRotationAxis = Axis;
		VerticesRotationAngle = Angle;
	};

	// Circle through every EVoxelQuadFace and set their axis and angles.
	if (QuadFaceToCalculate == EVoxelQuadFace::Back)
	{
		SetRotationAxisAndAngle(FVector::UpVector, 180.0f);
	}
	else if (QuadFaceToCalculate == EVoxelQuadFace::Right)
	{
		SetRotationAxisAndAngle(FVector::UpVector, 90.0f);
	}
	else if (QuadFaceToCalculate == EVoxelQuadFace::Left)
	{
		SetRotationAxisAndAngle(FVector::DownVector, 90.0f);
	}
	else if (QuadFaceToCalculate == EVoxelQuadFace::Up)
	{
		SetRotationAxisAndAngle(FVector::LeftVector, 90.0f);
	}
	else if (QuadFaceToCalculate == EVoxelQuadFace::Down)
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

	VoxelMeshParameters.Vertices = {
		RotatedVertices[3] + Offset,
		RotatedVertices[2] + Offset,
		RotatedVertices[1] + Offset,
		RotatedVertices[0] + Offset,
	};

	VoxelMeshParameters.Triangles =
	{
		Point1,
		Point2,
		Point3,
		Point4,
		Point3,
		Point2
	};

	// Top Left - Bottom Right x Top Left - Top Right
	const FVector QuadNormal = FVector::CrossProduct(VoxelMeshParameters.Vertices[2] - VoxelMeshParameters.Vertices[1], VoxelMeshParameters.Vertices[2] - VoxelMeshParameters.Vertices[0]).GetSafeNormal();

	for (int i = 0; i < 4; ++i)
	{
		VoxelMeshParameters.Normals.Add(QuadNormal);

		VoxelMeshParameters.Tangents.Add(TangentSetup);
	}

	VoxelMeshParameters.UVs =
	{
		FVector2D(0.0f, 1.0f),
		FVector2D(0.0f, 0.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(1.0f, 0.0f),
	};

	return VoxelMeshParameters;
}
