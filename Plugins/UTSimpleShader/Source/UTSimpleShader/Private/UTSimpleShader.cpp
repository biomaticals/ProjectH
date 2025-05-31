// Copyright 2025. Unique Turtle. All rights reserved.

#include "UTSimpleShader.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FUTSimpleShaderModule"

void FUTSimpleShaderModule::StartupModule()
{
	FString PluginBaseDirectory = IPluginManager::Get().FindPlugin(TEXT("UTSimpleShader"))->GetBaseDir();
	FString PluginShaderDirectory = FPaths::Combine(PluginBaseDirectory, TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/UTSimpleShader"), PluginShaderDirectory);
}

void FUTSimpleShaderModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUTSimpleShaderModule, UTSimpleShader)