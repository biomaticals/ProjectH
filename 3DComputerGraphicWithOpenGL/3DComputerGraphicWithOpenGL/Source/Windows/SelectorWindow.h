// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include "Common.h"

struct FSelectorWindowData
{
public:
	FSelectorWindowData();
	~FSelectorWindowData();

	void Draw(bool* bOpen);

public:
	bool bDraw;

private:
	std::list<FSampleCodeData> CodeDataList;


#pragma region File Resource
public:
	const std::string FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int SampleCode);

private:
	const std::filesystem::path TableOfContentsPath;
#pragma endregion
};