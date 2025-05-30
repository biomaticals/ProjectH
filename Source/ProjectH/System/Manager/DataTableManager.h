// Copyright 2025. Unique Turtle. All rights reserved.

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
	bool UpdatePresetCustomizationProfiles();

	UFUNCTION()
	TMap<EAnatomy, FAnatomyProfile> GetAvailableAnatomyProfiles();

	UFUNCTION()
	TMap<FName, FCustomizationProfileMetaData> GetPresetCustomizationProfiles();

	UFUNCTION(BlueprintCallable)
	void SetNeedUpdateAnatomyProfiles();

	UFUNCTION(BlueprintCallable)
	void SetNeedUpdatePresetCustomizationProfiles();

	UFUNCTION(BlueprintCallable)
	UDataTable* GetDefaultSkinTexturesDataTable(){return DefaultSkinTexturesDataTable;}

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterCustomization")
	UDataTable* AnatomyProfilesDataTable; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterCustomization")
	UDataTable* PresetCustomizationProfilesDataTable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterCustomization")
	UDataTable* DefaultSkinTexturesDataTable;

private:
	UPROPERTY(Transient)
	TMap<EAnatomy, FAnatomyProfile> AvailableAnatomyProfiles;

	UPROPERTY(Transient)
	TMap<FName, FCustomizationProfileMetaData> PresetCustomizationProfiles;

	UPROPERTY(Transient)
	bool NeedUpdatAnatomyProfiles = true;

	UPROPERTY(Transient)
	bool NeedUpdatePresetCustomizationProfiles = true;
#pragma endregion
};