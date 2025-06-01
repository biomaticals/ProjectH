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
		Vertices.SetNumUninitialized(11);

		for (int i = 0; i < 11; i++)
		{
			if (i == 0)
			{
				Vertices[i].Position = FVector2f(0.f, 0.f);
				Vertices[i].Color = FLinearColor::White;
			}
			else
			{
				const int point = i - 1;
				float Angle = 90.f + point * 36.f;
				float Radius = point % 2 == 0 ? 0.75f : 0.5f;
				Vertices[i].Position = FVector2f(Radius * FMath::Cos(FMath::DegreesToRadians(Angle)), Radius * FMath::Sin(FMath::DegreesToRadians(Angle)));

				float Hue = FMath::GetMappedRangeValueClamped<float>(TRange<float>(0, 360), TRange<float>(0, 255), Angle);
				Vertices[i].Color = FLinearColor::MakeFromHSV8(Hue, 255, 255);
			}
		}

		FRHIResourceCreateInfo CreateInfo(TEXT("FStarVertexBuffer"), &Vertices);
		VertexBufferRHI = RHICmcList.CreateVertexBuffer(Vertices.GetResourceDataSize(), EBufferUsageFlags::Static, CreateInfo);

	}
};
extern UTSIMPLESHADER_API TGlobalResource<FStarVertexBuffer> GStarVertexBuffer;
class FStarIndexBuffer : public FIndexBuffer
{
public:
	void InitRHI(FRHICommandListBase& RHICmdList) override
	{
		const uint32 Indices[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 9,
			0, 9, 10,
			0, 10, 1
		};

		TResourceArray<uint32, INDEXBUFFER_ALIGNMENT> IndexBuffer;
		uint32 NumIndices = UE_ARRAY_COUNT(Indices);
		IndexBuffer.AddUninitialized(NumIndices);
		FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint32));
		FRHIResourceCreateInfo CreateInfo(TEXT("FStarIndexBuffer"), &IndexBuffer);
		IndexBufferRHI = RHICmdList.CreateIndexBuffer(sizeof(uint32), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};
extern UTSIMPLESHADER_API TGlobalResource<FStarIndexBuffer> GStarIndexBuffer;

class FStarVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;
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

BEGIN_SHADER_PARAMETER_STRUCT(FStarVSParams,)
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