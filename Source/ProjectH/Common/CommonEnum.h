// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.generated.h"
 
#pragma region Character Customization
UENUM(BlueprintType)
enum class EAnatomy : uint8
{
	Default, 

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
ENUM_RANGE_BY_COUNT(EAnatomy, (uint8)EAnatomy::OrcMaleChild + 1);

UENUM(BlueprintType)
enum class ECharacterCustomizationInitializationBehavior : uint8
{
	UseCurrentProfile,
	UseProfileToLoad,
	OpenCharacterEditorWithCurrentProfile,
	OpenCharacterEditorWithProfileToLoad,
};

UENUM(BlueprintType)
enum class ECCDACollection : uint8
{
	Smith,
	Gardener,
};

UENUM(BlueprintType)
enum class EHGender : uint8
{
	Female,
	Male,
};

UENUM(BlueprintType)
enum class EGeneration : uint8
{
	Adult,
	Child,
};

UENUM(BlueprintType)
enum class ERace : uint8
{
	Human,
	MetaHuman,
	Drawf,
	Elf,
	Orc,
};

UENUM(BlueprintType)
enum class EApparelType : uint8
{
	Hat,
	UpperBody,
	Hands,
	LowerBody,
	Feet,
};

UENUM(BlueprintType)
enum class ECharacterCustomizationProfileType : uint8
{
	SavedProfile,
	PresetProfile,
	NotFound,
};
#pragma endregion
