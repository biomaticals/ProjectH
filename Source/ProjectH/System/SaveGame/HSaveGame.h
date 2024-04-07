// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HSaveGame.generated.h"

struct FHSaveGameData;

/**
 * 
 */
UCLASS()
class PROJECTH_API UHSaveGame : public ULocalPlayerSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FHSaveGameData> HSaveGameDataList;
};
