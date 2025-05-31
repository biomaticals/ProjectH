// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "GlobalShader.h"
#include "ShaderParameterMacros.h"
#include "ShaderParameters.h"
#include "RenderResource.h"
#include "RHI.h"
#include "ShaderParameterStruct.h"
#include "Containers/DynamicRHIResourceArray.h"

struct FColorVertex
{
public:
	FVector2f Position;
	FVector4f Color;
};

class FStarVertexBuffer : public FVertexBuffer
{
public:
	void InitRHI(FRHICommandListBase& RHICmcList) override 
	{
		TResourceArray<FColorVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
		Vertices.SetNumUninitialized(10);

		for (int i = 0; i < 10; i++)
		{
			float Angle = i * 36.f;
			float Radius = i % 2 == 0 ? 0.75f : 0.5f;
			Vertices[i].Position = FVector2f(Radius * FMath::Cos(FMath::DegreesToRadians(Angle)), Radius * FMath::Sin(FMath::DegreesToRadians(Angle)));

			float Hue = FMath::Fmod(i * 36.f, 360.f) / 360.f;
			Vertices[i].Color = FLinearColor::MakeFromHSV8(Hue, 255, 255);
		}

		FRHIResourceCreateInfo CreateInfo(TEXT("FStarVertexBuffer"), &Vertices);
		// Create Vertex Buffer
		// Since this is Statically allocated once to the GPU, we don't need to lock it on the Render Thread to wait for it to be dealt with.
		VertexBufferRHI = RHICmcList.CreateVertexBuffer(Vertices.GetResourceDataSize(), EBufferUsageFlags::Static, CreateInfo);

	}
};
extern UTSIMPLESHADER_API TGlobalResource<FStarVertexBuffer> GStarVertexBuffer;
class FStarIndexBuffer : public FIndexBuffer
{
public:
	/** Initialize the RHI for this rendering resource */
	void InitRHI(FRHICommandListBase& RHICmdList) override
	{
		const uint32 Indices[] =
		{
			0, 1, 2,
			0, 5, 4,
			0, 4, 3,
			0, 3, 2,
			0, 2, 1,
			1, 6, 5,
			2, 7, 6,
			3, 8, 7,
			4, 9, 8,
			5, 10, 9
		};

		TResourceArray<uint32, INDEXBUFFER_ALIGNMENT> IndexBuffer;
		uint32 NumIndices = UE_ARRAY_COUNT(Indices);
		IndexBuffer.AddUninitialized(NumIndices);
		FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint32));
		// RHICreateIndexBuffer
		FRHIResourceCreateInfo CreateInfo(TEXT("FStarIndexBuffer"), &IndexBuffer);
		IndexBufferRHI = RHICmdList.CreateIndexBuffer(sizeof(uint32), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);

	}
};
extern UTSIMPLESHADER_API TGlobalResource<FStarIndexBuffer> GStarIndexBuffer;

/*Define a Render Resource for our buffer, since the draw primitive uses it*/
/** The filter vertex declaration resource type. */
class FStarVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	/** Destructor. */
	virtual ~FStarVertexDeclaration() {}

	virtual void InitRHI(FRHICommandListBase& RHICmdList)
	{
		FVertexDeclarationElementList Elements;
		uint32 Stride = sizeof(FColorVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FColorVertex, Position), VET_Float2, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FColorVertex, Color), VET_Float4, 1, Stride));
		VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
	}

	virtual void ReleaseRHI()
	{
		VertexDeclarationRHI.SafeRelease();
	}
};
extern UTSIMPLESHADER_API TGlobalResource<FStarVertexDeclaration> GStarVertexDeclaration;

// Defined here so we can access it in View Extension.
BEGIN_SHADER_PARAMETER_STRUCT(FStarVSParams,)
	//SHADER_PARAMETER_STRUCT_ARRAY(FStarVertParams,Verticies)
	//RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()
class FStarVS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FStarVS);
	SHADER_USE_PARAMETER_STRUCT(FStarVS, FGlobalShader)
	using FParameters = FStarVSParams;
	
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}
};

BEGIN_SHADER_PARAMETER_STRUCT(FStarPSParams,)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FStarPS: public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FStarPS);
	using FParameters = FStarPSParams;
	SHADER_USE_PARAMETER_STRUCT(FStarPS, FGlobalShader)
};