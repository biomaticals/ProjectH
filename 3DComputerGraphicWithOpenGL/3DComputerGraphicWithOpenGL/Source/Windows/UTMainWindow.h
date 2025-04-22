// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "UTWindow.h"

class UTMainWindow : public UTWindow
{
public:
	UTMainWindow(const std::string& Title, int Width, int Height);
	virtual ~UTMainWindow();

	virtual void RenderUI() override;

public:
	bool ShowInputWindow = true;
	bool ShowDescriptionWindow = true;
	bool ShowSelectorWindow = true;
	bool bShowIntroduction = true;

	// remain for r&d
	bool show_demo_window = true;

private:
	const ImGuiWindow* InputWindow = nullptr;
	const ImGuiWindow* DescriptionWindow = nullptr;
	const ImGuiWindow* SelectorWindow = nullptr;
};