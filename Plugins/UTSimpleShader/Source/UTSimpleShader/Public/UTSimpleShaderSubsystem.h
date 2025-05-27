// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UTSimpleShaderSubsystem.generated.h"

class FViewExtension;

/**
 * 
 */
UCLASS()
class UTSIMPLESHADER_API UUTSimpleShaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	TSharedPtr<FViewExtension,ESPMode::ThreadSafe> ShaderTest;
};
