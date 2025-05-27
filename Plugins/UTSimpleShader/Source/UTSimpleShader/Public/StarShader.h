// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "ShaderParameterMacros.h"
#include "GlobalShader.h"

BEGIN_SHADER_PARAMETER_STRUCT(FStarVertexShaderParameters, )
END_SHADER_PARAMETER_STRUCT()

class FStarVertexShader : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FStarVertexShader);
	SHADER_USE_PARAMETER_STRUCT(FStarVertexShader, FGlobalShader);

	using FParameters = FStarVertexShaderParameters;

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}
}

BEGIN_SHADER_PARAMETER_STRUCT (FStarPixelShaderParameters, )
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()
class FStarPixelShader : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FStarPixelShader);
	SHADER_USE_PARAMETER_STRUCT(FStarPixelShader, FGlobalShader);

	using FParameters = FStarPixelShaderParameters;
}