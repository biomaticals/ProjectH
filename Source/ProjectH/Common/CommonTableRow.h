// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common/CommonStruct.h"
#include "CommonTableRow.generated.h"
 
 #pragma region CharacterCustomization
USTRUCT(BlueprintType)
struct FAnatomyProfile : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	bool IsValid()
	{
		return Body.AnimInstanceClass != nullptr && Body.Mesh != nullptr;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAnatomyBaseBodyProfile Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAnatomyHeadProfile> Heads;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCustomizationProfile Customization;
};
#pragma endregion

USTRUCT(BlueprintType)
struct FSkinTextureSetDefaultTexture : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FSkinTextureSetDefaultTexture()
	{

	}

	UTexture* Texture;
};
