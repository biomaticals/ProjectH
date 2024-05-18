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
		UE_LOG(HAssetManagerLog, Error, TEXT("엔진의 AssetManager가 UHAssetManager 가 아닙니다. 에셋 매니저가 제대로 작동하지 않습니다."));
		return *NewObject<UHAssetManager>(); // never calls this
	}
} 