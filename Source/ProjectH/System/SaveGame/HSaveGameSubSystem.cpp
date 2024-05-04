// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/SaveGame/HSaveGameSubSystem.h"
#include "GameFramework/GameStateBase.h"
#include "EngineUtils.h"
#include "ProjectH.h"
#include "System/HGameSingleton.h"
#include "System/SaveGame/HSaveGame.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"
#include "GameFramework/AsyncActionHandleSaveGame.h"
#include "System/Manager/SaveGameManager.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UHSaveGameSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnSaveCompleted.Unbind();
	OnLoadCompleted.Unbind();

	OnSaveCompleted.BindUObject(this, &UHSaveGameSubSystem::OnSaved);
	OnLoadCompleted.BindUObject(this, &UHSaveGameSubSystem::OnLoaded);
}

void UHSaveGameSubSystem::Deinitialize()
{
	Super::Deinitialize();

	if(OnSaveCompleted.IsBound())
	{
		OnSaveCompleted.Unbind();
	}

	if (OnLoadCompleted.IsBound())
	{
		OnLoadCompleted.Unbind();
	}
}

void UHSaveGameSubSystem::OnSaved(const FString& SlotName, const int32 UserIndex, bool Success)
{
	if(Success)
	{
		UT_LOG(HSaveGameLog, Log, TEXT("%d 유저의 %s 슬롯에 세이브게임을 저장했습니다."), UserIndex, *SlotName);
	}
	else
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%d 유저의 %s 슬롯에 세이브게임을 저장하는데 실패했습니다."), UserIndex, *SlotName);
	}

}

void UHSaveGameSubSystem::OnLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	UT_LOG(HSaveGameLog, Log, TEXT("%d 유저의 %s 슬롯으로 세이브게임을 불러왔습니다."), UserIndex, *SlotName);

	UHSaveGame* HSaveGame = Cast<UHSaveGame>(SaveGame);
	if (HSaveGame == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%s 슬롯의 세이브게임이 HSaveGame이 아닙니다."), *SlotName);
		return;
	}

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if (Actor == NULL || Actor->Implements<UHSaveGameObjectInterface>() == false)
		{
			continue;
		}

		bool Found = false;
		FString ID = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectID(Actor);
		FHSaveGameObjectData FoundData;
		for (FHSaveGameObjectData& Data : HSaveGame->HSaveGameData.ObjectData)
		{
			if (Data.IsValid() == false)
			{
				continue;
			}

			if (ID == Data.ID)
			{
				Found = true;
				FoundData = Data;
				
				FMemoryReader MemReader(Data.ByteData);
				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				Actor->Serialize(Ar);
				Actor->SetActorTransform(Data.Transform);
				break;
			}
		}

		if (Found)
		{
			HSaveGame->HSaveGameData.ObjectData.Remove(FoundData);
			continue;
		}
		else
		{
			//	
		}
	}

	if (HSaveGame->HSaveGameData.ObjectData.IsEmpty() == false)
	{
		//
	}
}

bool UHSaveGameSubSystem::HSaveGametoSlot(UObject* WorldContextObject, const FString& SlotName, const int32 UserIndex)
{
	if (GetWorld() == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("월드가 없습니다."));
		return false;
	}


	if (SlotName.IsEmpty())
	{
		UT_LOG(HSaveGameLog, Error, TEXT("슬롯이름이 비었습니다."));
		return false;
	}

	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("월드에 GameState가 존재하지 않습니다."));
		return false;
	}

	for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray)
	{
		//TODO
		//PlayerState->SavePlayerState
	}

	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::CreateSaveGameObject(UHSaveGame::StaticClass()));
	check(HSaveGame);

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;

		if (Actor && Actor->Implements<UHSaveGameObjectInterface>())
		{
			FHSaveGameObjectData Data;
			Data.ID = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectID(Actor);
			Data.ObjectClass = Actor->GetClass();
			Data.Transform = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectTransform(Actor);

			FMemoryWriter MemWriter(Data.ByteData);
			FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
			Ar.ArIsSaveGame = true;
			Actor->Serialize(Ar);
			check(Data.IsValid());

			IHSaveGameObjectInterface::Execute_OnObjectSaving(Actor);

			HSaveGame->HSaveGameData.ObjectData.Add(Data);
		}
	}

	UGameplayStatics::AsyncSaveGameToSlot(HSaveGame, SlotName, UserIndex, OnSaveCompleted);
	return true;
}

bool UHSaveGameSubSystem::HLoadGameFromSlot(const FString& SlotName, const int32 UserIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex) == false)
	{
		UT_LOG(HSaveGameLog, Warning, TEXT("%s 슬롯에 세이브게임이 없습니다."), *SlotName);
		return false;
	}

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, UserIndex, OnLoadCompleted);

	return true;
}

