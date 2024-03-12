// Copy Rigts are in Team UniqueTurtle. 

#include "CoreMinimal.h"
#include "CommonStruct.generated.h"

#pragma region Character Customizing
USTRUCT(BlueprintType)
struct FCustomizationProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnatomyHeadProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnatomyBodyProfile
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnatomyProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	FAnatomyBodyProfile Body;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	FAnatomyHeadProfile Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame)
	FCustomizationProfile Customzation;
};
#pragma endregion
