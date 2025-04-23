// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>

class UTWindow 
{
public:
    UTWindow(const std::string& Title, int Width, int Height);
    virtual ~UTWindow();
    virtual void NewFrame();
    virtual void RenderDrawData();

    bool ShouldClose() const;
    bool IsVisible() const;
    bool IsFocused() const;
    bool IsMinimized() const;

    GLFWwindow* GetGLFWWindow() const;
    ImGuiContext* GuiContext;

private:
    void SetupGLFWWindow();
    void InitImGui();

private:
    GLFWwindow* GLFWWindow;
    std::string Title;
    int Width;
    int Height;
};
static void FocusCallback(GLFWwindow* Window, int Focused);