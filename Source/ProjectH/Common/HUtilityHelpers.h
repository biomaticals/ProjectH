// Copyright 2025. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
 
 /**
  * 
  */
class HUtilityHelpers
{
public:
	static FString EnumToString(int32 Value, const TCHAR* EnumType);
	static int32 NameHasher(const FName& Name);
	static int32 StringHasher(const FString& String);
 };
