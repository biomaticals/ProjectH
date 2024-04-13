// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
#include "Common/HelperLibrary.h"

#define UT_LOG(CategoryName, Verbosity, Format, ...) \
	UE_LOG(CategoryName, Verbosity, TEXT("%hs(%d)"), __FUNCTION__, __LINE__) \
	UE_PRIVATE_LOG(PREPROCESSOR_NOTHING, constexpr, CategoryName, Verbosity, Format, ##__VA_ARGS__)

#define CHECK_REPLIACTE_COMPONENT() UKismetSystemLibrary::IsStandalone(this) == false && IsA(UActorComponent::StaticClass()) && Cast<UActorComponent>(this)->GetIsReplicated()

DECLARE_LOG_CATEGORY_EXTERN(HLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HCharacterLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HCharacterCustomizationLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HSaveGameLog, Log, All);