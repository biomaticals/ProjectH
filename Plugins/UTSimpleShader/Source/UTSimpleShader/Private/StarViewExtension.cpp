// Copyright 2025. Unique Turtle. All rights reserved.

#include "StarViewExtension.h"
#include "StarShader.h"
#include "PixelShaderUtils.h"
#include "PostProcess/PostProcessing.h"
#include "PostProcess/PostProcessMaterial.h"
#include "SceneTextureParameters.h"
#include "ShaderParameterStruct.h"

DECLARE_GPU_DRAWCALL_STAT(StarPass);

FStarViewExtension::FStarViewExtension(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{

}

void FStarViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	
}

void FStarViewExtension::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
		
}

void FStarViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass Pass, const FSceneView& InView, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	if (Pass == EPostProcessingPass::Tonemap)
	{
		InOutPassCallbacks.Add(FAfterPassCallbackDelegate::CreateRaw(this, &FStarViewExtension::StarPass_RenderThread));
	}
}

FScreenPassTexture FStarViewExtension::StarPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs)
{
	FScreenPassTexture SceneColor(InOutInputs.GetInput(EPostProcessMaterialInput::SceneColor));

	FScreenPassRenderTarget Output = InOutInputs.OverrideOutput;

	// OverrideOutput이 제공면, 이는 후처리의 마지막 패스임을 의미합니다.
	// 씬 컬러에서 읽고 쓰는 것은 지원되지 않기 때문에 이 작업이 필요합니다. (적어도 UE에서는 지원하지 않습니다.)
	// OverrideOutput은 또한 PostProcessing.cpp의 패스 시퀀스가 이것이 마지막 패스임을 알 수 있도록 필요합니다. 그래야 다음 프레임에서 씬 컬러로 잘못된 텍스처를 얻지 않습니다.
	if (!Output.IsValid())
	{
		Output = FScreenPassRenderTarget::CreateFromInput(GraphBuilder, SceneColor, View.GetOverwriteLoadAction(), TEXT("OverrideSceneColorTexture"));
	}

	RDG_GPU_STAT_SCOPE(GraphBuilder, StarPass)
	RDG_EVENT_SCOPE(GraphBuilder, "StarPass");
	
	if (EnumHasAllFlags(SceneColor.Texture->Desc.Flags, TexCreate_ShaderResource) && EnumHasAnyFlags(SceneColor.Texture->Desc.Flags,  TexCreate_RenderTargetable | TexCreate_ResolveTargetable))
	{
		const FIntRect ViewInfo = static_cast<const FViewInfo&>(View).ViewRect;
		const FGlobalShaderMap* ViewShaderMap = static_cast<const FViewInfo&>(View).ShaderMap;
		RenderStar(GraphBuilder,ViewShaderMap,ViewInfo,SceneColor);
	}
	
	return MoveTemp(SceneColor);
}

void FStarViewExtension::RenderStar
(
FRDGBuilder& GraphBuilder,
const FGlobalShaderMap* ViewShaderMap,
const FIntRect& ViewInfo,
const FScreenPassTexture& InSceneColor)
{
	FStarPSParams* PassParams = GraphBuilder.AllocParameters<FStarPSParams>();
	PassParams->RenderTargets[0] = FRenderTargetBinding(InSceneColor.Texture, ERenderTargetLoadAction::ELoad);

	TShaderMapRef<FStarPS> PixelShader(ViewShaderMap);

	AddFullscreenPass<FStarPS>(GraphBuilder,
		ViewShaderMap,
		RDG_EVENT_NAME("StarPass"),
		PixelShader,
		PassParams,
		ViewInfo);
	
}

template <typename TShaderClass>
void FStarViewExtension::AddFullscreenPass(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* GlobalShaderMap,
		FRDGEventName&& PassName,
		const TShaderRef<TShaderClass>& PixelShader,
		typename TShaderClass::FParameters* Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState,
		FRHIRasterizerState* RasterizerState,
		FRHIDepthStencilState* DepthStencilState,
		uint32 StencilRef)
{
	check(PixelShader.IsValid());
	ClearUnusedGraphResources(PixelShader, Parameters);

	GraphBuilder.AddPass(
		Forward<FRDGEventName>(PassName),
		Parameters,
		ERDGPassFlags::Raster,
		[Parameters, GlobalShaderMap, PixelShader, Viewport, BlendState, RasterizerState, DepthStencilState, StencilRef](FRHICommandList& RHICmdList)
	{
			FStarViewExtension::DrawFullscreenPixelShader<TShaderClass>(RHICmdList, GlobalShaderMap, PixelShader, *Parameters, Viewport, 
			BlendState, RasterizerState, DepthStencilState, StencilRef);
	});
}

template <typename TShaderClass>
	void FStarViewExtension::DrawFullscreenPixelShader(
		FRHICommandList& RHICmdList, 
		const FGlobalShaderMap* GlobalShaderMap,
		const TShaderRef<TShaderClass>& PixelShader,
		const typename TShaderClass::FParameters& Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState,
		FRHIRasterizerState* RasterizerState,
		FRHIDepthStencilState* DepthStencilState,
		uint32 StencilRef)
{
	check(PixelShader.IsValid());
	RHICmdList.SetViewport((float)Viewport.Min.X, (float)Viewport.Min.Y, 0.0f, (float)Viewport.Max.X, (float)Viewport.Max.Y, 1.0f);

	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	TShaderMapRef<FStarVS> VertexShader(GlobalShaderMap);
	
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GStarVertexDeclaration.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BlendState = BlendState ? BlendState : GraphicsPSOInit.BlendState;
	GraphicsPSOInit.RasterizerState = RasterizerState ? RasterizerState : GraphicsPSOInit.RasterizerState;
	GraphicsPSOInit.DepthStencilState = DepthStencilState ? DepthStencilState : GraphicsPSOInit.DepthStencilState;
	
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, StencilRef);
	SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), Parameters);
	DrawFullScreenStar(RHICmdList, 1);
}
