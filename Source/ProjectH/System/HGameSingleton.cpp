// Copyright 2025. Unique Turtle. All rights reserved.


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
	if(GEngine == nullptr)
		return nullptr;

	if(GEngine->GameSingleton == nullptr)
		return nullptr;

	UHGameSingleton* Instance = Cast<UHGameSingleton>(GEngine->GameSingleton);
	if (Instance == nullptr)
		return nullptr;

	if (Instance->IsValidLowLevel() == false)
		return nullptr;
	
	if(Instance->CreateManagers() == false)
		return nullptr;
	
	return Instance;
}

bool UHGameSingleton::CreateManagers()
{
	if(ManagersCreated)
		return true;

	if (DataTableManager == nullptr)
	{
		DataTableManager = NewObject<UDataTableManager>(this, DataTableManagerClass);
	}

	ManagersCreated = true;
	return true;
}

void UHGameSingleton::DestroyManagers()
{
	if (DataTableManager)
	{
		DataTableManager = nullptr;
	}
}

UDataTableManager* UHGameSingleton::GetDataTableManager(const UObject* WorldContextObject)
{
	if(WorldContextObject == nullptr)
		return nullptr;

	if(WorldContextObject->GetOuter() == nullptr)
		return nullptr;

	if (UHGameSingleton* HGameSington = GetHGameSingleton())
	{
		return HGameSington->DataTableManager;
	}

	return nullptr;
}