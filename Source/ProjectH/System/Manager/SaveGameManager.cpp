// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/Manager/SaveGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "System/SaveGame/HSaveGame.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"

bool USaveGameManager::WriteSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& Slot, const int32 UserIndex)
{	
	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::CreateSaveGameObject(UHSaveGame::StaticClass()));

	for (UObject* Object : Objects)
	{
		
	}

	return true;
}

bool USaveGameManager::ReadSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& Slot, const int32 UserIndex)
{
	return true;
}