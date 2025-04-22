// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "Windows/IntroductionWindow.h"
#include "Windows/SelectorWindow.h"

static GLFWwindow* MainWindow = nullptr;
static GLFWwindow* OutputWindow = nullptr;

const static ImGuiWindow* InputWindow = nullptr;
const static ImGuiWindow* DescriptionWindow = nullptr;
const static ImGuiWindow* SelectorWindow = nullptr;

int main(int, char**);

static void glfw_error_callback(int error, const char* description);


static void InitMainWindow();
static void InitOutputWindow();

static void ShowMainMenuBar(FWindowData* MainMenuBarData);

const static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

