// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/Manager/SaveGameManager.h"
#include "Common/CommonStruct.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectH.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "System/SaveGame/HSaveGame.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"

bool USaveGameManager::WriteSaveGameObjectData(UObject* InObject, FHSaveGameObjectData& InData)
{
	if (InObject && InObject->Implements<UHSaveGameObjectInterface>())
	{
		InData.ID = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectKey(InObject);
		InData.ObjectClass = InObject->GetClass();
		if (InData.ObjectClass->IsChildOf(AActor::StaticClass()))
		{
			InData.Transform = Cast<AActor>(InObject)->GetTransform();
		}

		IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(InObject, InData);
		
		FMemoryWriter MemWriter(InData.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		InObject->Serialize(Ar);

		for (UObject* SaveGameObjectChildren : IHSaveGameObjectInterface::Execute_GetHSaveGameObjectChildren(InObject))
		{
			WriteSaveGameObjectChildData(InObject, InData);
		}
	}
}

bool USaveGameManager::WriteSaveGameObjectChildData(UObject* InObject, FHSaveGameObjectData& InData)
{
	if (InObject && InObject->Implements<UHSaveGameObjectInterface>())
	{
		IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(InObject, InData);

		for (UObject* SaveGameObjectChildren : IHSaveGameObjectInterface::Execute_GetHSaveGameObjectChildren(InObject))
		{
			WriteSaveGameObjectChildData(InObject, InData);
		}

		InData.bProcessed = true;
	}
}