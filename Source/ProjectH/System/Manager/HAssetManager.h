// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HAssetManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HAssetManagerLog, Log, All);

/**
 * 
 */
UCLASS()
class PROJECTH_API UHAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UHAssetManager& Get();
};
