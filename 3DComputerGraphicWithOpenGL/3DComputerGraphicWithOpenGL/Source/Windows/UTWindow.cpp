// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "UTWindow.h"
#include <iostream>

UTWindow::UTWindow(const std::string& Title, int Width, int Height)
    : Title(Title), Width(Width), Height(Height)
{
    SetupGLFWWindow();
    InitImGui();
}

UTWindow::~UTWindow()
{
    glfwMakeContextCurrent(GLFWWindow);
    glfwDestroyWindow(GLFWWindow);
}

void UTWindow::NewFrame()
{
	glfwMakeContextCurrent(GetGLFWWindow());
}

void UTWindow::RenderDrawData()
{
    int display_w, display_h;
    glfwGetFramebufferSize(GLFWWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(GLFWWindow);
}

bool UTWindow::ShouldClose() const
{
    return glfwWindowShouldClose(GLFWWindow);
}

bool UTWindow::IsVisible() const
{
    return glfwGetWindowAttrib(GLFWWindow, GLFW_VISIBLE);
}

bool UTWindow::IsFocused() const
{
    return glfwGetWindowAttrib(GLFWWindow, GLFW_FOCUSED);
}

bool UTWindow::IsMinimized() const
{
    return glfwGetWindowAttrib(GLFWWindow, GLFW_ICONIFIED);
}

GLFWwindow* UTWindow::GetGLFWWindow() const
{
    return GLFWWindow;
}

void UTWindow::SetupGLFWWindow()
{
    GLFWWindow = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
    if (!GLFWWindow) 
    {
        std::cerr << "Failed to create window: " << Title << std::endl;
        exit(1);
    }
    glfwMakeContextCurrent(GLFWWindow);
    glfwSwapInterval(1);
    glViewport(0, 0, Width, Height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void UTWindow::InitImGui()
{
    glfwMakeContextCurrent(GLFWWindow);
    glfwSetWindowFocusCallback(GLFWWindow, FocusCallback);
    GuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(GuiContext);
    ImGui::StyleColorsDark();
}

void FocusCallback(GLFWwindow* Window, int Focused)
{
	if (Focused)
		printf("Window got focus\n");
	else
		printf("Window lost focus\n");
}