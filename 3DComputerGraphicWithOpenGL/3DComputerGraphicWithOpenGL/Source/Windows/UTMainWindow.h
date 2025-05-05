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

	virtual void NewFrame() override; 
	virtual void RenderUI();
	virtual void RenderDrawData() override;
	virtual void Initialize() override;

	ImGuiContext* GetGuiContext() const;

private:
	void DrawInputWindow();
	void DrawSelectorWindow();
	void DrawDescriptionWindow();

	void ShowIntroductionWindow(bool* bOpen);

public:
	bool ShowInputWindow = true;
	bool ShowDescriptionWindow = true;
	bool ShowSelectorWindow = true;
	bool bShowIntroduction = true;

	// remain for r&d
	bool show_demo_window = true;

private:
	ImGuiContext* GuiContext = nullptr;
	const ImGuiWindow* InputWindow = nullptr;
	const ImGuiWindow* DescriptionWindow = nullptr;
	const ImGuiWindow* SelectorWindow = nullptr;
};