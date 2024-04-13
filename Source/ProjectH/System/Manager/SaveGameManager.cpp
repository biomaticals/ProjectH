// Copyright 2024. Unique Turtle. All rights reserved.


#include "System/Manager/SaveGameManager.h"
#include "Common/CommonStruct.h"
#include "Kismet/GameplayStatics.h"
#include "System/SaveGame/HSaveGame.h"
#include "System/SaveGame/HSaveGameObjectInterface.h"
#include "ProjectH.h"

bool USaveGameManager::WriteSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& SlotName, const int32 UserIndex)
{	
	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::CreateSaveGameObject(UHSaveGame::StaticClass()));

	for (UObject* Object : Objects)
	{
		if (Object && Object->Implements<UHSaveGameObjectInterface>())
		{
			FHSaveGameObjectData NewSaveGameObjectData;

			NewSaveGameObjectData.ObjectClass = Object->GetClass();
			NewSaveGameObjectData.ID = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectKey(Object);
			IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(Object, NewSaveGameObjectData);
			HSaveGame->HSaveGameData.ObjectData.AddUnique(NewSaveGameObjectData);

			TArray<UObject*> ObjectChildren = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectChildren(Object);
			for (UObject* ObjectChild : ObjectChildren)
			{
				if(ObjectChild)
				{
					WriteSaveGameObjectsChildData(ObjectChild, HSaveGame->HSaveGameData, Object);
				}
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(HSaveGame, SlotName, UserIndex);

	return true;	
}

bool USaveGameManager::ReadSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& SlotName, const int32 UserIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex) == false)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%s is invalid SlotName. (UserIndex = %d)"), *SlotName, UserIndex);
		return false;
	}

	UHSaveGame* HSaveGame = Cast<UHSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

	if (HSaveGame == nullptr)
	{
		UT_LOG(HSaveGameLog, Fatal, TEXT(" % s is exist, but load failed. (UserIndex = %d)"), *SlotName, UserIndex);
		return false;
	}

	for (UObject* Object : Objects)
	{
		if (Object && Object->Implements<UHSaveGameObjectInterface>())
		{
			const FString& ObjectKey = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectKey(Object);
			FHSaveGameObjectData* FoundObjectData = HSaveGame->HSaveGameData.ObjectData.FindByPredicate([&ObjectKey](const FHSaveGameObjectData& ObjectData){return ObjectData.ID.Equals(ObjectKey);});
			
			if (FoundObjectData)
			{
				IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(Object, *FoundObjectData);
			}
		}
	}

	return true;
}

bool USaveGameManager::WriteSaveGameObjectsChildData(UObject* Object, FHSaveGameData& SaveGameData, UObject* ParentObject)
{
	if(Object == nullptr)
		return false;

	if(Object->Implements<UHSaveGameObjectInterface>() == false)
		return false;

	FHSaveGameObjectData NewSaveGameObjectData;

	NewSaveGameObjectData.ObjectClass = Object->GetClass();
	NewSaveGameObjectData.ID = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectKey(Object);
	NewSaveGameObjectData.ParentSaveGameObject = ParentObject;
	IHSaveGameObjectInterface::Execute_WriteSaveGameObjectData(Object, NewSaveGameObjectData);
	SaveGameData.ObjectData.AddUnique(NewSaveGameObjectData);

	TArray<UObject*> ObjectChildren = IHSaveGameObjectInterface::Execute_GetHSaveGameObjectChildren(Object);
	for (UObject* ObjectChild : ObjectChildren)
	{
		if (ObjectChild)
		{
			WriteSaveGameObjectsChildData(ObjectChild, SaveGameData, Object);
		}
	}

	return true;
}

bool USaveGameManager::WriteObjectProperty(UPARAM(Ref) FHSaveGameObjectData& SaveGameObjectData, UObject* Object, FString InPropertyName)
{
	if (ensureAlways(Object) == false)
		return false;

	if (ensureAlways(SaveGameObjectData.ObjectClass == Object->GetClass()) == false)
		return false;

	FProperty* Property = Object->GetClass()->FindPropertyByName(*InPropertyName);

	if (ensureAlways(Property) == false)
		return false;

	int32 Index = SaveGameObjectData.PropertyDataList.AddDefaulted();
	FHSaveGamePropertyData& PropertyData = SaveGameObjectData.PropertyDataList[Index];
	PropertyData.Name = Property->GetName();
	PropertyData.Type = Property->GetCPPType();

	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, int32);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, float);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, double);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FName);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FText);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FString);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FVector);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FVector2D);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FRotator);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FQuat);
	CHECK_AND_WRITE_PROPERTY(Object, PropertyData, FTransform);

	return true;
}

bool USaveGameManager::ReadObjectProperty(UPARAM(Ref) FHSaveGameObjectData& SaveGameObjectData, UObject* Object)
{
	if(Object == nullptr)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("Try to read invalid object."));
		return false;
	}
	

	if (SaveGameObjectData.IsValid() == false)
	{
		UT_LOG(HSaveGameLog, Error, TEXT("%s's ObjectData is invalid."), *Object->GetName());
		return false;
	}

	for(FHSaveGamePropertyData& PropertyData : SaveGameObjectData.PropertyDataList)
	{
		if (FProperty* Property = SaveGameObjectData.ObjectClass->FindPropertyByName(FName(PropertyData.Name)))
		{
			CHECK_AND_READ_PROPERTY(Object, PropertyData, int32);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, float);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, double);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FName);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FText);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FString);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FVector);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FVector2D);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FRotator);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FQuat);
			CHECK_AND_READ_PROPERTY(Object, PropertyData, FTransform);
		}
	}

	return true;
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, int32* ValueAddress)
{
	PropertyData.Value = FString::Printf(TEXT("%d"), ValueAddress);
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, float* ValueAddress)
{
	PropertyData.Value = FString::Printf(TEXT("%f"), ValueAddress);
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, double* ValueAddress)
{
	PropertyData.Value = FString::Printf(TEXT("%f"), ValueAddress);
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FName* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FText* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FString* ValueAddress)
{
	PropertyData.Value = *ValueAddress;
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FVector* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FVector2D* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FRotator* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FQuat* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FTransform* ValueAddress)
{
	PropertyData.Value = *(*ValueAddress).ToString();
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, int32* ValueAddress)
{
	*ValueAddress = FCString::Atoi(*PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, float* ValueAddress)
{
	*ValueAddress = FCString::Atof(*PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, double* ValueAddress)
{
	*ValueAddress = FCString::Atod(*PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FName* ValueAddress)
{
	*ValueAddress = *PropertyData.Value;
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FText* ValueAddress)
{
	*ValueAddress = FText::FromString(PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FString* ValueAddress)
{
	*ValueAddress = PropertyData.Value;
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FVector* ValueAddress)
{
	ValueAddress->InitFromString(PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FVector2D* ValueAddress)
{
	ValueAddress->InitFromString(PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FRotator* ValueAddress)
{
	ValueAddress->InitFromString(PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FQuat* ValueAddress)
{
	ValueAddress->InitFromString(PropertyData.Value);
}

template<>
void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FTransform* ValueAddress)
{
	ValueAddress->InitFromString(PropertyData.Value);
}