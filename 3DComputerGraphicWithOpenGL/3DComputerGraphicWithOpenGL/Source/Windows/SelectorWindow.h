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
	const bool HasSelectedExampleChanged() const;

public:
	bool bDraw = true;

private:
	bool bSelectedExampleChanged;
#pragma endregion
};