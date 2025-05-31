// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HSaveGameObjectInterface.generated.h"


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

public:
	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	const FString GetHSaveGameObjectID() const;

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	const FTransform GetHSaveGameObjectTransform() const;

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	void OnObjectSaving();

	UFUNCTION(BlueprintNativeEvent, Category = "HSaveGameObjectInterface")
	void OnObjectLoading();
};
 