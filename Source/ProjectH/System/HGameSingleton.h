// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HGameSingleton.generated.h"

class UDataTableManager;
class USaveGameManager;

#define DATATABLE_MANAGER() UHGameSingleton::GetHGameSingleton()->DataTableManager
 
/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTH_API UHGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UHGameSingleton(const FObjectInitializer& ObjectInitializer);
	~UHGameSingleton();
	static UHGameSingleton* GetHGameSingleton();

protected:
	bool CreateManagers();
	void DestroyManagers();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UDataTableManager* GetDataTableManager(const UObject* WorldContextObject);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UDataTableManager> DataTableManagerClass;

public:
	UPROPERTY(Transient)
	TObjectPtr<UDataTableManager> DataTableManager;
	
private:
	bool ManagersCreated;
};
