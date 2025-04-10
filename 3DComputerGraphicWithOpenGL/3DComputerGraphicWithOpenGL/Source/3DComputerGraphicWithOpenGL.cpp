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
    // glfw 초기화
    glfwInit();
 
    // window 만들기 (width, height, title, monitor, share)
    GLFWwindow* window = glfwCreateWindow(640, 480, "Inyong", 0, 0);
    
    // context는 그리기 위한 내용을 담고 있음
    // window가 두개이면 context가 두개일수도 있음
    // 그러면 어떤 context로 그릴지 정해줘야 함
    glfwMakeContextCurrent(window);
 
    // 사용자가 window 창을 닫을 때까지
    while (!glfwWindowShouldClose(window)) {
        // window 그려주기
        render(window);
 
        // 마우스 움직이는 것. 이런것들 들고와서 필요한 window한테 보내주기
        glfwPollEvents();
    }
 
    // window가 닫혔을 경우 끝내자
    glfwDestroyWindow(window);
    glfwTerminate();
}
 
void render(GLFWwindow* window) { }