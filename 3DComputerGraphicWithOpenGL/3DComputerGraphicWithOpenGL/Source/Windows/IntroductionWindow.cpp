// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "IntroductionWindow.h"

const char* FIntroductionWindow::WindowName = "Introduction";

void FIntroductionWindow::Draw(bool* bOpen)
{
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
	
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 300.f, MainViewport->WorkSize.y / 2.f - 200.f ));
	ImGui::SetNextWindowSize(ImVec2(600.f, 400.f));
	if (!ImGui::Begin(WindowName, bOpen))
	{
		ImGui::End();
		return;
	}

	ImGui::End();
}