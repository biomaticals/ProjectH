// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameManager.generated.h"

// Code Generation for USaveGameManager::WriteObjectProperty
#define CHECK_AND_WRITE_PROPERTY(Object, ObjectData, PropertyType) \
{\
	if(ObjectData.Type.Equals(#PropertyType))\
	{\
		if(PropertyType* ValueAddress = Property->ContainerPtrToValuePtr<PropertyType>(Object))\
		{\
			WriteObjectProperty_Internal<PropertyType>(ObjectData, ValueAddress);\
		}\
	}\
}\

// Code Generation for USaveGameManager::ReadObjectProperty
#define CHECK_AND_READ_PROPERTY(Object, ObjectData, PropertyType) \
{\
	if(ObjectData.Type.Equals(#PropertyType))\
	{\
		if(PropertyType* ValueAddress = Property->ContainerPtrToValuePtr<PropertyType>(Object))\
		{\
			ReadObjectProperty_Internal<PropertyType>(ObjectData, ValueAddress);\
		}\
	}\
}\

struct FHSaveGameData;
struct FHSaveGameObjectData;
struct FHSaveGamePropertyData;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API USaveGameManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGameManager")
	bool WriteSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& SlotName, const int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "SaveGameManager")
	bool ReadSaveGameObjectsToSlot(TArray<UObject*> Objects, const FString& SlotName, const int32 UserIndex);

public:
	static bool WriteObjectProperty(UPARAM(Ref) FHSaveGameObjectData& SaveGameObjectData, UObject* Object, FString InPropertyName);
	static bool WriteObjectNonProperty(UPARAM(Ref) FHSaveGameObjectData& SaveGameOjbectData, UObject* Object, FString Key, FString Value);
	static bool ReadObjectProperty(UPARAM(Ref) FHSaveGameObjectData& SaveGameObjectData, UObject* Object);

private:
	bool WriteSaveGameObjectsChildData(UObject* ChildObject, FHSaveGameData& SaveGameData, UObject* ParentObject = nullptr);
	
	template<typename ObjectType>
	static void WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, ObjectType* ValueAddress);

	template<typename ObjectType>
	static void ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, ObjectType* ValueAddress);
};

template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, int32* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, float* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, double* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FName* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FText* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FString* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FVector* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FVector2D* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FRotator* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FQuat* ValueAddress);
template<> void USaveGameManager::WriteObjectProperty_Internal(UPARAM(Ref) FHSaveGamePropertyData& PropertyData, FTransform* ValueAddress);

template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, int32* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, float* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, double* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FName* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FText* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FString* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FVector* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FVector2D* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FRotator* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FQuat* ValueAddress);
template<> void USaveGameManager::ReadObjectProperty_Internal(UPARAM(Ref) const FHSaveGamePropertyData& PropertyData, FTransform* ValueAddress);