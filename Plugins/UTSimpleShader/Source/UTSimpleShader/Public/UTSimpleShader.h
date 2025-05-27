// Copyright 2024. Unique Turtle. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FUTSimpleShaderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
