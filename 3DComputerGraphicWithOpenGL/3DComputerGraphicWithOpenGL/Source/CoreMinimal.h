// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <format>

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

const static char* glsl_version = "#version 130";
const static ImVec4 ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);