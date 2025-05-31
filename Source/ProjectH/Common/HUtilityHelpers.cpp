// Copyright 2025. Unique Turtle. All rights reserved.
 
#include "HUtilityHelpers.h"
  
FString HUtilityHelpers::EnumToString(int32 Value, const TCHAR* EnumType)
{
	UEnum* Enum = FindObject<UEnum>(nullptr, EnumType);
	return Enum ? Enum->GetNameStringByIndex(static_cast<int32>(Value)) : FString();
}

int32 HUtilityHelpers::NameHasher(const FName& Name)
{
	return StringHasher(Name.ToString());
}

int32 HUtilityHelpers::StringHasher(const FString& String)
{
	int32 Sum = String.Len();
	for (auto It = String.CreateConstIterator(); It; It++)
	{
		Sum += *It * It.GetIndex();
	}

	return Sum;
}