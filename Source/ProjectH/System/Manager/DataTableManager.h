// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/CommonEnum.h"
#include "Common/CommonTableRow.h"
#include "DataTableManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTH_API UDataTableManager : public UObject
{
	GENERATED_BODY()
	
public:
	void ValidateDataTables();


#pragma region CharacterCustomization
public:
	UFUNCTION()
	bool UpdateAvailableAnatomyProfiles();

	UFUNCTION()
	TMap<EAnatomy, FAnatomyProfile> GetAvailableAnatomyProfiles();

	UFUNCTION(BlueprintCallable)
	void SetNeedUpdateAnatomyProfiles();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterCustomization")
	UDataTable* AnatomyProfilesDataTable; 

private:
	UPROPERTY(Transient)
	TMap<EAnatomy, FAnatomyProfile> AvailableAnatomyProfiles;

	UPROPERTY(Transient)
	bool NeedUpdatAnatomyProfiles = false;
#pragma endregion
};