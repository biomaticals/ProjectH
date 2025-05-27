// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

//#include "Runtime/Engine/Public/SceneViewExtension.h"
#include "SceneViewExtension.h"
#include "RenderResource.h"

class UTSIMPLESHADER_API FUTSimpleViewExtension : public FSceneViewExtensionBase 
{
public:
	FUTSimpleViewExtension(const FAutoRegister& AutoRegister);
	//~ Begin FSceneViewExtensionBase Interface
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {}
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override{};
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const
	FPostProcessingInputs& Inputs) override;
	virtual void SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks,
	bool bIsPassEnabled)override;
};