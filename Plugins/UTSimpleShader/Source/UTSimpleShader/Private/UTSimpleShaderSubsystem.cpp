// Copyright 2025. Unique Turtle. All rights reserved.

#include "UTSimpleShaderSubsystem.h"
#include "StarViewExtension.h"
#include "SceneViewExtension.h"

void UUTSimpleShaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG(LogTemp, Display, TEXT("UTSimpleShaderSubsystem Initialized"));
	this->StarPass = FSceneViewExtensions::NewExtension<FStarViewExtension>();
}
