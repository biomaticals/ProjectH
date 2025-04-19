// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "3D CG With OpenGL by biomatic", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // demo
    bool show_demo_window = true;

    bool ShowMainWindow = true;
    bool ShowSubWindow = true;
    bool ShowSelectorWindow = true;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

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
        ImGui::SetNextWindowSize(ImVec2(3.f * MainViewport->Size.x / 4.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
		ImGui::Begin("MainWindow", &ShowMainWindow, CoreWindowFlags);
        MainWindow = ImGui::GetCurrentWindow();
		ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(MainViewport->WorkPos.x, MainViewport->Size.y / 2.f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(3.f * MainViewport->Size.x / 4.f, MainViewport->Size.y / 2.f), ImGuiCond_Always);
        ImGui::Begin("SubWindow", &ShowSubWindow, CoreWindowFlags);
        
        SubWindow = ImGui::GetCurrentWindow();
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(3.f * MainViewport->Size.x / 4.f, MainViewport->WorkPos.y), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(MainViewport->Size.x / 4.f, MainViewport->Size.y), ImGuiCond_Always);
        ImGui::Begin("SelectorWindow", &ShowSelectorWindow, CoreWindowFlags);
        SelectorWindow = ImGui::GetCurrentWindow();
        DrawSelectorWindow();
        ImGui::End();

        // 2. Main Menu
        static FWindowData WindowData;
        if(WindowData.ShowIntroduction) 
        {
            ShowIntroduction(&WindowData.ShowIntroduction);
        }

        ShowMainMenuBar(&WindowData);

        // remain this for R&D
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static void ShowMainMenuBar(FWindowData* MainMenuBarData)
{
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::MenuItem("Introduction", nullptr, &MainMenuBarData->ShowIntroduction);
        ImGui::EndMainMenuBar();
    }
}