// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

struct FIntroductionWindowData
{
	FIntroductionWindowData()
	{

	}

	~FIntroductionWindowData()
	{

	}

	static const char* WindowName;

public:
	void Draw(bool* bOpen);
};

static void ShowIntroduction(bool* bOpen)
{
    FIntroductionWindowData IntroductionWindow{};
    IntroductionWindow.Draw(bOpen);
};