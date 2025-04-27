// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "Windows/UTMainWindow.h"
#include "Windows/UTOutputWindow.h"
#include "Windows/IntroductionWindow.h"
#include "Windows/SelectorWindow.h"

static UTMainWindow* MainWindow = nullptr;
static UTWindow* OutputWindow = nullptr;

int main(int, char**);

static void glfw_error_callback(int error, const char* description);

