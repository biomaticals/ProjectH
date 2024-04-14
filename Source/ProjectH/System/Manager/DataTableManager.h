// Copy Rigts are in Team UniqueTurtle. 

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
	bool UpdateAvaiableAnatomyProfiles();

	UFUNCTION()
	TMap<EAnatomy, FAnatomyProfile> GetAvailableAnatomyProfiles();

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