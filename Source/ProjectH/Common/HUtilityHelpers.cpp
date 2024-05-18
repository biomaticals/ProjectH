// Copyright 2024. Unique Turtle. All rights reserved.

#include "HUtilityHelpers.h"

FString HUtilityHelpers::EnumToString(int32 Value, const TCHAR* EnumType)
{
	UEnum* Enum = FindObject<UEnum>(nullptr, EnumType);
	return Enum ? Enum->GetNameStringByIndex(static_cast<int32>(Value)) : FString();
}