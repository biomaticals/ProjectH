// Copy Rigts are in Team UniqueTurtle. 


#include "System/HGameSingleton.h"
#include "System/Manager/DataTableManager.h"

UHGameSingleton::UHGameSingleton(const FObjectInitializer& ObjectInitializer)
	: ManagersCreated(false)
{

}

UHGameSingleton::~UHGameSingleton()
{
	DestroyManagers();
}

UHGameSingleton* UHGameSingleton::GetHGameSingleton()
{
	if(GEngine == NULL)
		return NULL;

	if(GEngine->GameSingleton == NULL)
		return NULL;

	UHGameSingleton* Instance = Cast<UHGameSingleton>(GEngine->GameSingleton);
	if (Instance == NULL)
		return NULL;

	if (Instance->IsValidLowLevel() == false)
		return NULL;
	
	if(CreateManagers() == false)
		return NULL;
	
	return Instance;
}

bool UHGameSingleton::CreateManagers()
{
	if(ManagersCreated)
		return true;

	if (DataTableManager == NULL)
	{
		DataTableManager = NewObject<UDataTableManager>(this, UDataTableManager::StaticClass());
	}

	ManagersCreated = true;
	return true;
}

void UHGameSingleton::DestroyManagers()
{
	if (DataTableManager)
	{
		DataTableManager = NULL;
	}
}
