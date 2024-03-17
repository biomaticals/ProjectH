// Copy Rigts are in Team UniqueTurtle. 

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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bDebug;
};
