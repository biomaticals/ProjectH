// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HSaveGameSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UHSaveGameSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	bool SaveGametoSlot(FString SlotName);
	
	
private:
	TArray<TObjectPtr<UObject>> SaveGameObjects;

};
