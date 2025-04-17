// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "HSaveGameSubsystem.generated.h"

/**
 *  
 */
UCLASS()
class PROJECTH_API UHSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void OnSaved(const FString& SlotName, const int32 UserIndex, bool Success);
	void OnLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	bool HSaveGametoSlot(UObject* WorldContextObject, const FString& SlotName, const int32 UserIndex);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	bool HLoadGameFromSlot(const FString& SlotName, const int32 UserIndex);

public:
	FAsyncSaveGameToSlotDelegate OnSaveCompleted;	
	FAsyncLoadGameFromSlotDelegate OnLoadCompleted;
};
