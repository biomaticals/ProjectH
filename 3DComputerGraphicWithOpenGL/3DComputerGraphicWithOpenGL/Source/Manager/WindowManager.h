// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "Windows/UTMainWindow.h"
#include "Windows/UTOutputWindow.h"

#define WINDOW_MANAGER WindowManager::GetWindowManager()
#define MAIN_WINDOW WindowManager::GetWindowManager()->GetMainWindow()
#define OUTPUT_WINDOW WindowManager::GetWindowManager()->GetOutputWindow()

class WindowManager
{
protected:
	WindowManager();
	~WindowManager();

public:
	static WindowManager* GetWindowManager();
	UTMainWindow* GetMainWindow() const;
	UTOutputWindow* GetOutputWindow() const;

	static void Destroy();
	void CreateMainWindow();
	void CreateOutputWindow();
	void HideOutputWindow(bool bHide = true);
	void DestroyMainWindow();
	void DestroyOutputWindow();
	void Update();

private:
	static WindowManager* Instance;
	UTMainWindow* MainWindow;
	UTOutputWindow* OutputWindow;
};
