// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameManager.generated.h"

struct FHSaveGameData;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API USaveGameManager : public UObject
{
	GENERATED_BODY()

public:
	bool WriteSaveGameObjectData(UObject* InObject, FHSaveGameObjectData& InData);

private:
	bool WriteSaveGameObjectChildData(UObject* InChild, FHSaveGameObjectData& InData);

};