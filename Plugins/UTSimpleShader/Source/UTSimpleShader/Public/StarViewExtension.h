// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "StarShader.h"
#include "SceneViewExtension.h"
#include "RenderResource.h"

class UTSIMPLESHADER_API FStarViewExtension : public FSceneViewExtensionBase
{
public:

	FStarViewExtension(const FAutoRegister& AutoRegister);
	//~ Begin FSceneViewExtensionBase Interface
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {}
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	virtual void SubscribeToPostProcessingPass(EPostProcessingPass Pass, const FSceneView& InView, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;
	//~ End FSceneViewExtensionBase Interface
protected:

	template <typename TShaderClass>
	static void AddFullscreenPass(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* GlobalShaderMap,
		FRDGEventName&& PassName,
		const TShaderRef<TShaderClass>& PixelShader,
		typename TShaderClass::FParameters* Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState = nullptr,
		FRHIRasterizerState* RasterizerState = nullptr,
		FRHIDepthStencilState* DepthStencilState = nullptr,
		uint32 StencilRef = 0);

	template <typename TShaderClass>
	static void DrawFullscreenPixelShader(
		FRHICommandList& RHICmdList,
		const FGlobalShaderMap* GlobalShaderMap,
		const TShaderRef<TShaderClass>& PixelShader,
		const typename TShaderClass::FParameters& Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState = nullptr,
		FRHIRasterizerState* RasterizerState = nullptr,
		FRHIDepthStencilState* DepthStencilState = nullptr,
		uint32 StencilRef = 0);

	static inline void DrawFullScreenStar(FRHICommandList& RHICmdList, uint32 InstanceCount) 
	{
		RHICmdList.SetStreamSource(0, GStarVertexBuffer.VertexBufferRHI, 0);
		RHICmdList.DrawIndexedPrimitive(
			GStarIndexBuffer.IndexBufferRHI,
			/*BaseVertexIndex=*/ 0,
			/*MinIndex=*/ 0,
			/*NumVertices=*/ 11,
			/*StartIndex=*/ 0,
			/*NumPrimitives=*/ 10,
			/*NumInstances=*/ InstanceCount);
	}

	FScreenPassTexture StarPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);

public:
	static void RenderStar
	(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* ViewShaderMap,
		const FIntRect& View,
		const FScreenPassTexture& InSceneColor
	);

};

