// Copyright 2024. Unique Turtle. All rights reserved.

#include "UTSimpleShader.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FUTSimpleShaderModule"

void FUTSimpleShaderModule::StartupModule()
{
	const FString PluginBaseDirectory = IPluginManager::Get().FindPlugin(TEXT("UTSimpleShader"))->GetBaseDir();
	const FString PluginShaderDirectory = FPaths::Combine(PluginBaseDirectory, TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/CustomShaders"), PluginShaderDirectory);
}

void FUTSimpleShaderModule::ShutdownModule()
{


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUTSimpleShaderModule, UTSimpleShader)