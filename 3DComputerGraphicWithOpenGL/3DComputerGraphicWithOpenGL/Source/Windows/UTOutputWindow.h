// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "UTWindow.h"

class UTOutputWindow : public UTWindow
{
public:
    UTOutputWindow(const std::string& Title, int Width, int Height);
    virtual ~UTOutputWindow();
	virtual void RenderDrawData() override;
private:
    void MyDisplay();
};