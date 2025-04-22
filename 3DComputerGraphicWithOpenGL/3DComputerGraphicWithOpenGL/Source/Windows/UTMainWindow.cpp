// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTMainWindow.h"
#include "SelectorWindow.h"
#include "IntroductionWindow.h"

UTMainWindow::UTMainWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
{
}

UTMainWindow::~UTMainWindow()
{

}

void UTMainWindow::RenderUI()
{
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = true;
	static bool no_resize = true;
	static bool no_collapse = true;
	static bool no_close = true;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags CoreWindowFlags = 0;
	if (no_titlebar)        CoreWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       CoreWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           CoreWindowFlags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            CoreWindowFlags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          CoreWindowFlags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        CoreWindowFlags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             CoreWindowFlags |= ImGuiWindowFlags_NoNav;
	if (no_background)      CoreWindowFlags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  CoreWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   CoreWindowFlags |= ImGuiWindowFlags_UnsavedDocument;

	// 1. Windows
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
	ImGui::Begin("InputWindow", &ShowInputWindow, CoreWindowFlags);
	InputWindow = ImGui::GetCurrentWindow();
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->Size.y / 2.f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
	ImGui::Begin("DescriptionWindow", &ShowDescriptionWindow, CoreWindowFlags);

	DescriptionWindow = ImGui::GetCurrentWindow();
	ImGui::End();

	static FSelectorWindowData SelecWindowData;

	ImGui::SetNextWindowPos(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(4.f * MainViewport->Size.x / 10.f, MainViewport->Size.y), ImGuiCond_Always);
	ImGui::Begin("SelectorWindow", &ShowSelectorWindow, CoreWindowFlags);
	SelectorWindow = ImGui::GetCurrentWindow();
	SelecWindowData.Draw(&SelecWindowData.bDraw);
	ImGui::End();

	// 2. Main Menu
	static FWindowData WindowData;
	if (WindowData.bShowIntroduction)
	{
		ShowIntroduction(&WindowData.bShowIntroduction);
	}

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::MenuItem("Introduction", nullptr, &WindowData.bShowIntroduction);
		ImGui::EndMainMenuBar();
	}

	//remain this for R&D
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
}

