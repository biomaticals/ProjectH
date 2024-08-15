// Copyright 2024. Unique Turtle. All rights reserved.

#include "UTAssetEditor.h"
#include "AssetToolsModule.h"
#include "EnumKeyDataTableFactory.h"

#define LOCTEXT_NAMESPACE "FUTAssetEditorModule"

void FUTAssetEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_EnumKeyDataTable()));
}

void FUTAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUTAssetEditorModule, UTAssetEditor)