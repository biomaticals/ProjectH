// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "Windows/UTMainWindow.h"
#include "Windows/UTOutputWindow.h"

namespace UTG
{
	static UTMainWindow* MainWindow = nullptr;
	static UTOutputWindow* OutputWindow = nullptr; 
	
	void CreateMainWindow();
	void CreateOutputWindow(bool bHide = true);
	void DestroyMainWindow();
	void DestroyOutputWindow();
	void UpdateManager();
}

int main(int, char**);
static void glfw_error_callback(int error, const char* description);

