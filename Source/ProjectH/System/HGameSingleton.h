// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HGameSingleton.generated.h"

class UDataTableManager;
class USaveGameManager;

#define DATATABLE_MANAGER() {UHGameSingleton::GetHGameSingleton()->DataTableManager;}
#define SAVEGAME_MANAGER() {UHGameSingleton::GetHGameSingleton()->SaveGameManager;}

/**
 * 
 */
UCLASS()
class PROJECTH_API UHGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UHGameSingleton(const FObjectInitializer& ObjectInitializer);
	~UHGameSingleton();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHGameSingleton* GetHGameSingleton();

protected:
	bool CreateManagers();
	void DestroyManagers();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDataTableManager* GetDataTableManager(){return DataTableManager;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USaveGameManager* GetSaveGameManager(){return SaveGameManager;}

private:
	UPROPERTY(Transient)
	TObjectPtr<UDataTableManager> DataTableManager;

	UPROPERTY(Transient)
	TObjectPtr<USaveGameManager> SaveGameManager;
	

	bool ManagersCreated;
};
