// Copy Rigts are in Team UniqueTurtle. 

#pragma once

#include "CoreMinimal.h"
 
FORCEINLINE static FString EnumToString(int32 Value, const TCHAR* EnumType)
{
	UEnum* Enum =  FindObject<UEnum>(nullptr, EnumType);
	return Enum ? Enum->GetNameStringByIndex(static_cast<int32>(Value)) : FString();
}