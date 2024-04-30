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
		UT_LOG(HSaveGameLog, Log, TEXT("%d ������ %s ���Կ� ���̺������ �����߽��ϴ�."), UserIndex, *SlotName);
	}
	else
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%d ������ %s ���Կ� ���̺������ �����ϴµ� �����߽��ϴ�."), UserIndex, *SlotName);
	}

}

void UHSaveGameSubSystem::OnLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	UT_LOG(HSaveGameLog, Log, TEXT("%d ������ %s �������� ���̺������ �ҷ��Խ��ϴ�."), UserIndex, *SlotName);

	UHSaveGame* HSaveGame = Cast<UHSaveGame>(SaveGame);
	if (HSaveGame == NULL)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%s ������ ���̺������ HSaveGame�� �ƴմϴ�."), *SlotName);
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
				FoundData = Data;

				Actor->SetActorTransform(Data.Transform);

				FMemoryReader MemReader(Data.ByteData);
				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				Actor->Serialize(Ar);

				Found = true;
			}
		}

		if (Found)
		{
			HSaveGame->HSaveGameData.ObjectData.Remove(FoundData);
			break;
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
		UT_LOG(HSaveGameLog, Warning, TEXT("%s ���Կ� ���̺������ �����ϴ�."), *SlotName);
		return false;
	}

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, UserIndex, OnLoadCompleted);

	return true;
}

