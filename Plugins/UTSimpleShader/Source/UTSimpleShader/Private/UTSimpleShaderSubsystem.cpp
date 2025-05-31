// Copyright 2025. Unique Turtle. All rights reserved.

#include "UTSimpleShaderSubsystem.h"
#include "StarViewExtension.h"
#include "SceneViewExtension.h"

void UUTSimpleShaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG(LogTemp, Warning, TEXT("Star View Extension Subsystem Init"));
	this->StarPass = FSceneViewExtensions::NewExtension<FStarViewExtension>();
}
