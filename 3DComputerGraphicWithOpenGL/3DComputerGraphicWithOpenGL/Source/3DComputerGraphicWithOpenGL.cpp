// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"

int main(int, char**)
{
	//glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	IMGUI_CHECKVERSION();

	MainWindow = new UTMainWindow("3D CG With OpenGL by biomatic", 1280, 720);
	if(MainWindow == nullptr)
		return 1;

	OutputWindow = new UTWindow("Output", 640, 360);
	if(OutputWindow == nullptr)
		return 1;

	glfwMakeContextCurrent(MainWindow->GetGLFWWindow());
    ImGui::SetCurrentContext(MainWindow->GuiContext);
    ImGui_ImplOpenGL3_Init(glsl_version); // Only Mainwindow
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_InitForOpenGL(MainWindow->GetGLFWWindow(), true);

	glfwSwapInterval(1);
	while (MainWindow->ShouldClose() == false)
	{
		MainWindow->NewFrame();
		MainWindow->RenderUI();
		MainWindow->RenderDrawData();

		if (OutputWindow->ShouldClose() == false)
		{
			OutputWindow->NewFrame();
			OutputWindow->RenderUI();
			OutputWindow->RenderDrawData();
		}
		else
		{
			
		}

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}