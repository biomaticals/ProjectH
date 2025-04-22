// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include <string>

class UTWindow 
{
public:
    UTWindow(const std::string& title, int width, int height);
    ~UTWindow();

    void InitImGui();
    void NewFrame();
    void RenderUI();
    void RenderDrawData();

    bool ShouldClose() const;
    void PollEvents();

private:
    GLFWwindow* GLFWWindow;
    std::string Title;
    int Width;
    int Height;

    void SetupGLFWWindow();
};
