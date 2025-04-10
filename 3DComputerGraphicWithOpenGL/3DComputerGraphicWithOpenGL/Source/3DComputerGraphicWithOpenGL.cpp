// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.
#include <stdio.h>
#include "iostream"
#include <GLFW/glfw3.h>

// Static Linked Library
#include "OutsideStaticMath.h"
#include "InsideStaticMath.h"

// Dynamic Linked Library
#include "InsideDynamicMath.h"
#include "OutsideDynamicMath.h"
 
void render(GLFWwindow* window);
 
int main()
{
    // 한글
    glfwInit();
 
    GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);
    

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        render(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
 
void render(GLFWwindow* window) { }