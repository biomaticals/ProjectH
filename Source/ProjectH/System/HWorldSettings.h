// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "HWorldSettings.generated.h"

class UHExperienceDefinition;

/**
 * HWorldSettings
 * 
 * 1. ExperienceDefinition
 */
UCLASS()
class PROJECTH_API AHWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
		UFUNCTION(BlueprintPure)
		TSoftClassPtr<UHExperienceDefinition> GetDefaultExperienceDefinition();
		
protected:
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSoftClassPtr<UHExperienceDefinition> DefaultExperienceDefinition;
};
