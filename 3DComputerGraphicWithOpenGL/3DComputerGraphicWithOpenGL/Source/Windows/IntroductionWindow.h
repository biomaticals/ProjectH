// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "ImGui/imgui.h"

struct FIntroductionWindow
{
	FIntroductionWindow()
	{

	}

	~FIntroductionWindow()
	{

	}

	static const char* WindowName;

public:
	void Draw(bool* bOpen);
};