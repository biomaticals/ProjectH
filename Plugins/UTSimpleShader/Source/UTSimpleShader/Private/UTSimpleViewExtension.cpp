// Copyright 2024. Unique Turtle. All rights reserved.

#include "UTSimpleViewExtension.h"
#include "SceneViewExtension.h"
//#include "TriangleShader.h"
#include "PixelShaderUtils.h"
#include "PostProcess/PostProcessing.h"
#include "PostProcess/PostProcessMaterial.h"
#include "SceneTextureParameters.h"
#include "ShaderParameterStruct.h"

DECLARE_GPU_DRAWCALL_STAT(StarPass);

FUTSimpleViewExtension::FUTSimpleViewExtension(const FAutoRegister& AutoRegister)
	: FSceneViewExtensionBase(AutoRegister)
{

}

void FUTSimpleViewExtension::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray&
InOutPassCallbacks, bool bIsPassEnabled)
{
	if (Pass == EPostProcessingPass::Tonemap)
	{
	
	}
}