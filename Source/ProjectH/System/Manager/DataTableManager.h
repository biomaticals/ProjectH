// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTH_API UDataTableManager : public UObject
{
	GENERATED_BODY()
	
public:
	void ValidateDataTables();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterCustomization")
	UDataTable* CharacterCustomizationDataTable;
};