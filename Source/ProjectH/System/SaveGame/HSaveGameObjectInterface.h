// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HSaveGameObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHSaveGameObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTH_API IHSaveGameObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	const FString GetHSaveGameObjectKey() const;

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	const TArray<UObject*> GetHSaveGameObjectChildren() const;

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	bool WriteSaveGameObjectData(FHSaveGameObjectData& SaveGameObjectData);

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	bool ReadSaveGameObjectData(FHSaveGameObjectData& SaveGameObjectData);
};
