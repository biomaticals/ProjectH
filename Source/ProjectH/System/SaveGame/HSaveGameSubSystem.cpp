// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/SaveGame/HSaveGameSubSystem.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectH.h"
#include "System/HGameSingleton.h"
#include "System/SaveGame/HSaveGame.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"

bool UHSaveGameSubSystem::SaveGametoSlot(FString SlotName)
{
	if (GetWorld() == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("���尡 �����ϴ�."));
		return false;
	}


	if (SlotName.IsEmpty())
	{
		UT_LOG(HSaveGameLog, Error, TEXT("�����̸��� ������ϴ�."));
		return false;
	}

	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("���忡 GameState�� �������� �ʽ��ϴ�."));
		return false;
	}

	for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray)
	{
		//TODO
		//PlayerState->SavePlayerState
	}

	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::CreateSaveGameObject(UHSaveGame::StaticClass()));
	check(HSaveGame)

	const TArray<ULevel*> Levels = GetWorld()->GetLevels();
	for (ULevel* Level : Levels)
	{
		if(Level == NULL)
			continue;

		for (AActor* Actor : Level->Actors)
		{
			if (Actor && Actor->Implements<UHSaveGameObjectInterface>())
			{
				FHSaveGameObjectData Data;
				SAVEGAME_MANAGER()->WriteSaveGameObjectData(Actor, Data);
				
				check(Data.IsValid())

				
			}
		}
	}
	
	for (UObject* Object : SaveGameObjects)
	{
		if (Object && Object->Implements<UHSaveGameObjectInterface>())
		{
			FHSaveGameObjectData Data;
			IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(Object, Data);
		}
	}
	
	
	

	
}