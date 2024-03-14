// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"

#define UT_LOG(CategoryName, Verbosity, Format, ...) \
	UE_LOG(CategoryName, Verbosity, TEXT("%s(%n)"), __FUNCTION__, __LINE__) \
	UE_PRIVATE_LOG(PREPROCESSOR_NOTHING, constexpr, CategoryName, Verbosity, Format, ##__VA_ARGS__)


DECLARE_LOG_CATEGORY_EXTERN(HLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HCharacterLog, Log, All);