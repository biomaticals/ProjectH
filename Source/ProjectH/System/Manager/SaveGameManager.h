// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API USaveGameManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool SaveGame(TArray<UObject*> Objects, FString Slot);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool LoadGame(TArray<UObject*> Objects, FString Slot);

};