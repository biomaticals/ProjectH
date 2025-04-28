// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

int main(int, char**)
{
	//glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	IMGUI_CHECKVERSION();

	CreateMainWindow();
	CreateOutputWindow(true);

	glfwMakeContextCurrent(MainWindow->GetGLFWWindow());
    ImGui::SetCurrentContext(MainWindow->GuiContext);
    ImGui_ImplOpenGL3_Init(glsl_version); // Only Mainwindow
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_InitForOpenGL(MainWindow->GetGLFWWindow(), true);

	glfwSwapInterval(1);
	while (MainWindow->ShouldClose() == false)
	{
		glfwPollEvents();
		
		MainWindow->NewFrame();
		MainWindow->RenderUI();
		MainWindow->RenderDrawData();

		if (OutputWindow)
		{
			if (OutputWindow->ShouldClose() == false)
			{
				OutputWindow->NewFrame();
				OutputWindow->RenderUI();
				OutputWindow->RenderDrawData();
			}
			else
			{
				DestroyOutputWindow();
			}
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	delete MainWindow;
	MainWindow = nullptr;

	return 0;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void CreateMainWindow()
{
	GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
	int MonitorWidth = Mode->width;
	int MonitorHeight = Mode->height;

	int MainWindowWidth = MonitorWidth * 5 / 10;
	int MainWindowHeight = MonitorHeight * 8 / 10;

	MainWindow = new UTMainWindow("3D CG With OpenGL by biomatic", MainWindowWidth, MainWindowHeight);
	if(MainWindow == nullptr)
		return;

	int MainWindowPositionX = MonitorWidth * 1 / 10;
	int MainWindowPositionY = MonitorHeight * 1 / 10;
	glfwSetWindowPos(MainWindow->GetGLFWWindow(), MainWindowPositionX, MainWindowPositionY);
}

void CreateOutputWindow(bool bHide = true)
{
	GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* Mode = glfwGetVideoMode(Monitor);
	int MonitorWidth = Mode->width;
	int MonitorHeight = Mode->height;
	int OutputWindowWidth = MonitorWidth * 3 / 10;
	int OutputWindowHeight = MonitorHeight * 8 / 10;
	OutputWindow = new UTOutputWindow("Output", OutputWindowWidth, OutputWindowHeight);
	if(OutputWindow == nullptr)
		return;

	int OutputWindowPositionX = MonitorWidth * 6 / 10;
	int OutputWindowPositionY = MonitorHeight * 1 / 10;
	glfwSetWindowPos(OutputWindow->GetGLFWWindow(), OutputWindowPositionX, OutputWindowPositionY);
	if(bHide)
		glfwHideWindow(OutputWindow->GetGLFWWindow());
}

void DestroyMainWindow()
{
	delete MainWindow;
	MainWindow = nullptr;
}

void DestroyOutputWindow()
{
	delete OutputWindow;
	OutputWindow = nullptr;
}