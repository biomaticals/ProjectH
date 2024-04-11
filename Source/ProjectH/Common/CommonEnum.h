// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.generated.h"

#pragma region Character Customization
UENUM(BlueprintType)
enum class EAnatomy : uint8
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

ENUM_RANGE_BY_COUNT(EAnatomy, EAnatomy::OrcMaleChild);

UENUM(BlueprintType)
enum class ECharacterCustomizationInitializationBehavior : uint8
{
	None,
	UseCurrentProfile,
	UseProfileToLoad,
	OpenCharacterEditorWithCurrentProfile,
	OpenCharacterEditorWithProfileToLoad,
};

UENUM(BlueprintType)
enum class ECCDACollection
{
	Smith,
	Gardener,
};

UENUM(BlueprintType)
enum class EGender
{
	Female,
	Male,
};

UENUM(BlueprintType)
enum class EGeneration
{
	Adult,
	Child,
};

UENUM(BlueprintType)
enum class ERace
{
	Human,
	MetaHuman,
	Drawf,
	Elf,
	Orc,
};

UENUM(BlueprintType)
enum class EApparelType
{
	Hat,
	UpperBody,
	Hands,
	LowerBody,
	Feet,
};

UENUM(BlueprintType)
enum class ECharacterCustomizationProfileType
{
	SavedProfile,
	PresetProfile,
	NotFound,
};
#pragma endregion
