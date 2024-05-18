// Copyright 2024. Unique Turtle. All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UHDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* Thumnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Debug")
	bool bDebug;
};