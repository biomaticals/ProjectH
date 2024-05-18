// Copyright 2024. Unique Turtle. All rights reserved.


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
	
	if(Instance->CreateManagers() == false)
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

UDataTableManager* UHGameSingleton::GetDataTableManager(const UObject* WorldContextObject)
{
	if(WorldContextObject == NULL)
		return NULL;

	if(WorldContextObject->GetOuter() == NULL)
		return NULL;

	if (UHGameSingleton* HGameSington = GetHGameSingleton())
	{
		return HGameSington->DataTableManager;
	}

	return NULL;
}