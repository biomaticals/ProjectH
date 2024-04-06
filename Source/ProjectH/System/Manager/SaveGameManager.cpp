// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/Manager/SaveGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "System/HSaveGame.h"

bool USaveGameManager::SaveGame(TArray<UObject*> Objects, FString Slot)
{
	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::CreateSaveGameObject(UHSaveGame::StaticClass()));


	return true;
}

bool USaveGameManager::LoadGame(TArray<UObject*> Objects, FString Slot)
{
	return true;
}