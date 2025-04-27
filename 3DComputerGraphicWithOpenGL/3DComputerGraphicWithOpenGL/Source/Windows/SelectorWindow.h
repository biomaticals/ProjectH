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
	const FExampleCodeData GetExampleCodeData() const;

private:
	auto UpdateSelectedExample(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex);

public:
	bool bDraw = true;

private:
	std::list<FExampleCodeData> ExampleCodeDataList;
	FExampleCodeData SelectedExampleCodeData;

#pragma region File Resource
private:
	const std::string FindContext(unsigned int Part, unsigned int Chapter, unsigned int Section, unsigned int CodeIndex);

private:
	const std::filesystem::path TableOfContentsPath;
#pragma endregion
};