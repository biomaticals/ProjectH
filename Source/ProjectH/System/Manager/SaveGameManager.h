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
	UFUNCTION(BlueprintCallable, Category = "SaveGameManager")
	bool WriteSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& Slot, const int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "SaveGameManager")
	bool ReadSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& Slot, const int32 UserIndex);
};