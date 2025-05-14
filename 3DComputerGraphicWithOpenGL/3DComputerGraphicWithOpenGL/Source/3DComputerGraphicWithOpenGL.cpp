// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "3DComputerGraphicWithOpenGL.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "Manager/ResourceManager.h"
#include "Manager/WindowManager.h"


void UpdateManager()
{
	
	RESOURCE_MANAGER->Update();
}

int main(int, char**)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	IMGUI_CHECKVERSION();

	WINDOW_MANAGER->CreateMainWindow();
	WINDOW_MANAGER->CreateOutputWindow();

	glfwMakeContextCurrent(MAIN_WINDOW->GetGLFWWindow());
	ImGui::SetCurrentContext(MAIN_WINDOW->GetGuiContext());
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui_ImplGlfw_InitForOpenGL(MAIN_WINDOW->GetGLFWWindow(), true);

	if (OUTPUT_WINDOW->GetGLFWWindow())
	{
		printf("Window got focus\n");
	}

	glfwSwapInterval(1);
	while (MAIN_WINDOW->ShouldClose() == false)
	{
		UpdateManager();
		glfwPollEvents();
		
		MAIN_WINDOW->NewFrame();
		MAIN_WINDOW->RenderUI();
		MAIN_WINDOW->RenderDrawData();
	
		if (OUTPUT_WINDOW)
		{
			if (OUTPUT_WINDOW->ShouldClose() == false)
			{
				OUTPUT_WINDOW->NewFrame();
				OUTPUT_WINDOW->RenderDrawData();
			}
			else
			{
				WINDOW_MANAGER->HideOutputWindow();
			}
		}
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	
	WINDOW_MANAGER->DestroyMainWindow();
	WINDOW_MANAGER->DestroyOutputWindow();

	return 0;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}