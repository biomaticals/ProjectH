// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HGameSingleton.generated.h"

class UDataTableManager;

#define DATATABLE_MANAGER() {UHGameSingleton::GetHGameSingleton()->DataTableManager;}

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
	UHGameSingleton* GetHGameSingleton();

protected:
	bool CreateManagers();
	void DestroyManagers();

private:
	UPROPERTY(Transient)
	TObjectPtr<UDataTableManager> DataTableManager;

	bool ManagersCreated;
};
