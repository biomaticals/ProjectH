// Copyright 2025. Team Unique Turtle ; https:github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTMainWindow.h"
#include "3DComputerGraphicWithOpenGL.h"
#include "Manager/ResourceManager.h"

UTMainWindow::UTMainWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
{
	Initialize();
}

UTMainWindow::~UTMainWindow()
{

}

void UTMainWindow::NewFrame()
{
	glfwMakeContextCurrent(GetGLFWWindow());
	ImGui::SetCurrentContext(GuiContext);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
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
	
	//1. Windows
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
	float InputWindowTitleBarSize = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2;
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->WorkPos.y),ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
	ImGui::Begin("InputWindow", &ShowInputWindow, CoreWindowFlags);
	InputWindow = ImGui::GetCurrentWindow();
	DrawInputWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->Size.y / 2.f + InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->Size.y / 2.f - InputWindowTitleBarSize), ImGuiCond_Always);
	ImGui::Begin("DescriptionWindow", &ShowDescriptionWindow, CoreWindowFlags);
	DescriptionWindow = ImGui::GetCurrentWindow();
	DrawDescriptionWindow();
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(6.f * MainViewport->Size.x / 10.f, MainViewport->WorkPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(4.f * MainViewport->Size.x / 10.f, MainViewport->Size.y), ImGuiCond_Always);
	ImGui::Begin("SelectorWindow", &ShowSelectorWindow, CoreWindowFlags);
	SelectorWindow = ImGui::GetCurrentWindow();
	DrawSelectorWindow();
	ImGui::End();
	
	//2. Main Menu
	if (bShowIntroduction)
	{
		ShowIntroductionWindow(&bShowIntroduction);
	}
	
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::MenuItem("Introduction", nullptr, &bShowIntroduction);
		ImGui::EndMainMenuBar();
	}
	
	// remain this for R&D
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
}

void UTMainWindow::RenderDrawData()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();
	glFlush();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(GetGLFWWindow());
}

void UTMainWindow::Initialize()
{
	UTWindow::Initialize();
	GuiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(GuiContext);
	ImGui::StyleColorsDark();
}

ImGuiContext* UTMainWindow::GetGuiContext() const
{
	return GuiContext;
}

void UTMainWindow::DrawInputWindow()
{

}

void UTMainWindow::DrawSelectorWindow()
{
	if (ImGui::CollapsingHeader(RESOURCE_MANAGER->GetNextTitleContext().c_str()))
	{
		ImGui::Indent();
		if (ImGui::CollapsingHeader(RESOURCE_MANAGER->GetNextTitleContext().c_str()))
		{
			ImGui::Indent();
			if (ImGui::CollapsingHeader(RESOURCE_MANAGER->GetNextTitleContext().c_str()))
			{
				ImGui::Indent();
				if (ImGui::MenuItem(RESOURCE_MANAGER->GetNextTitleContext().c_str(), nullptr))
				{
					glfwShowWindow(OutputWindow->GetGLFWWindow());
				}
				ImGui::Unindent();
			}
			ImGui::Unindent();
		}
		ImGui::Unindent();
	}
	
	if (ImGui::CollapsingHeader("Part03 Graphic Pipeline"))
	{
	
	}
}

void UTMainWindow::DrawDescriptionWindow()
{

}

void UTMainWindow::ShowIntroductionWindow(bool* bOpen)
{
	const ImGuiViewport* MainViewport = ImGui::GetMainViewport();
	
	ImGuiWindowFlags WindowFlags{};
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_UnsavedDocument;
	
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkSize.x / 2.f - 400.f, MainViewport->WorkSize.y /2.f - 250.f), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(800, 500.f), ImGuiCond_Appearing);
	if (ImGui::Begin("Introduction", bOpen, WindowFlags))
	{
		ImGui::SeparatorText("3D CG With OpenGl by biomatic");
		ImGui::Text("This project was initiated to learn and practice the OpenGL API.");
		ImGui::Text("The content is adapted from a book \"3D Computer Graphics with OpenGL\".");
		ImGui::Text("Through this program, you can view and run the code examples from each part and chapter.");
		ImGui::Text("From \"Selector window\", choose part, chapter and title to proceed.");
		ImGui::Text("And then, \"Main window\" shows the codes, \"Sub window\" outputs the results.");
		ImGui::NewLine();
		ImGui::Text("To learn more about the book, please follow this link.");
		ImGui::TextLinkOpenURL("https:www.hanbit.co.kr/store/books/look.php?p_code=B1779572378");
		ImGui::NewLine();
		ImGui::Text("To access the open source for this program, please follow this link.");
		ImGui::TextLinkOpenURL("https:github.com/biomaticals/3DComputerGraphicWithOpenGL");
		ImGui::NewLine();
		ImGui::SeparatorText("biomatic");
		ImGui::Text("I am a game client programmer from Korea with 4 years of experience.");
		ImGui::NewLine();
	
	
		ImGui::Text("To visit my technical blog, please follow this link.");
		ImGui::Text("Unfortunately, the technical blog does not support English.");
		ImGui::NewLine();
		ImGui::TextLinkOpenURL("https:biomaticals.notion.site/GUI-1daed2b75184805fa19cfd4eb4be638f?pvs=4");
		ImGui::NewLine();
		ImGui::Text("To contact, please use the phone number or email address below.");
		ImGui::Text("Phone Number : +82 10 3902 8624 (Republic of Korea)");
		ImGui::Text("E-mail : biomaticals@naver.com");
		ImGui::NewLine();
	
	
		if (ImGui::Button("Close", ImVec2(-FLT_MIN, 0.f)))
		{
			*bOpen = false;
		}
	
	
		ImGui::End();
		return;
	}
	
	
	ImGui::End();
}