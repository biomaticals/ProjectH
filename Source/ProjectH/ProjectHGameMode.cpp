// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectHGameMode.h"
#include "ProjectHCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectHGameMode::AProjectHGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
