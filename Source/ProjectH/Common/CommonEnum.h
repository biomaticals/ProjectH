// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.generated.h"

#pragma region Character Customization
UENUM(BlueprintType)
enum class EAnatomy
{
	HumanFemaleAdult,
	HumanFemaleChild,
	HumanMaleAdult,
	HumanMaleChild,

	MetahumanFemaleTalNRW,
	MetahumanMaleTalNRW,
	
	DwarfFemaleAdult,
	DwarfFemaleChild,
	DwarfMaleAdult,
	DwarfMaleChild,
	
	ElfFemaleAdult,
	ElfFemaleChild,
	ElfMaleAdult,
	ElfMaleChild,

	OrcFemaleAdult,
	OrcFemaleChild,
	OrcMaleAdult,
	OrcMaleChild,
};

UENUM(BlueprintType)
enum class ECharacterCustomizationInitializationBehavior
{
	None,
	UseCurrentProfile,
	UseProfileToLoad,
	OpenCharacterEditorWithCurrentProfile,
	OpenCharacterEditorWithProfileToLoad,
};
#pragma endregion
