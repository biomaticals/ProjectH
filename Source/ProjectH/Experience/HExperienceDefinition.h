// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/PrimaryAssetLabel.h"
#include "HExperienceDefinition.generated.h"

class UAssetPackage;

/**
 * 
 */
UCLASS()
class PROJECTH_API UHExperienceDefinition : public UPrimaryAssetLabel
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	TArray<TSubclassOf<UAssetPackage>> GetAssetsToLoad() { return AssetsToLoad;}

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<UAssetPackage>> AssetsToLoad;
};
