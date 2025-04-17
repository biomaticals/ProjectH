// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/Manager/HAssetManager.h"

DEFINE_LOG_CATEGORY(HAssetManagerLog);

UHAssetManager& UHAssetManager::Get()
{
	UAssetManager* Singleton = GEngine->AssetManager;

	if (UHAssetManager* HAssetManager = Cast<UHAssetManager>(Singleton))
	{
		return *HAssetManager;
	}
	else
	{
		UE_LOG(HAssetManagerLog, Error, TEXT("Engine's 'Asset Manager' is not a UHAssetManager. Asset Manager doesn't work."));
		return *NewObject<UHAssetManager>();
	}
} 