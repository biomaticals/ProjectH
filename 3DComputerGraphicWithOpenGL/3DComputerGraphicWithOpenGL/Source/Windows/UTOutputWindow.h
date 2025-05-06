// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "UTWindow.h"
#include "Common.h"

class UTOutputWindow : public UTWindow
{
public:
	UTOutputWindow(const std::string& Title, int Width, int Height);
	virtual ~UTOutputWindow() override;
	virtual void RenderDrawData() override;

//public:
	//void SetSelectedExampleCodeData(unsigned int InPart, unsigned int InChapter, unsigned int InSection, unsigned int InCodeIndex);

private:
	FExampleCodeData ExampleCodeData;
};