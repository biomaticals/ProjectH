// Copyright 2025. Unique Turtle. All rights reserved.

#include "StarShader.h"
#include "Shader.h"
#include "VertexFactory.h"

IMPLEMENT_SHADER_TYPE(, FStarVS, TEXT("/UTSimpleShader/Star.usf"), TEXT("StarVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FStarPS, TEXT("/UTSimpleShader/Star.usf"), TEXT("StarPS"), SF_Pixel);

TGlobalResource<FStarVertexBuffer> GStarVertexBuffer;
TGlobalResource<FStarIndexBuffer> GStarIndexBuffer;
TGlobalResource<FStarVertexDeclaration> GStarVertexDeclaration;