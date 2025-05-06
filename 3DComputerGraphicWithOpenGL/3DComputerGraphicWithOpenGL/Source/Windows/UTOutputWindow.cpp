// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "UTOutputWindow.h"
#include "Manager/ResourceManager.h"

UTOutputWindow::UTOutputWindow(const std::string& Title, int Width, int Height)
	: UTWindow(Title, Width, Height)
{
	Initialize();
}

UTOutputWindow::~UTOutputWindow()
{

}

void UTOutputWindow::RenderDrawData()
{
	
}

//void UTOutputWindow::SetSelectedExampleCodeData(unsigned int InPart, unsigned int /InChapter,/ unsigned int InSection, unsigned int InCodeIndex)
//{
//	ExampleCodeData.Part = InPart;
//	ExampleCodeData.Chapter = InChapter;
//	ExampleCodeData.Section = InSection;
//	ExampleCodeData.CodeIndex = InCodeIndex;
//
//	ExampleCodeData.Title = RESOURCE_MANAGER->FindTitleContext(InPart, InChapter, /InSection,/ InCodeIndex).c_str();
//	ExampleCodeData.DrawFunction = 
//	ExampleCodeData.Description = ExampleCodeData.Title;
//}
//
//void UTOutputWindow::MyDisplay5_2()
//{
//	int display_w, display_h;
//	glfwGetFramebufferSize(GetGLFWWindow(), &display_w, &display_h);
//	glViewport(0, 0, display_w, display_h);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_POLYGON);
//	glVertex3f(-0.5f, -0.5f, 0.f);
//	glVertex3f(0.5f, -0.5, 0.f);
//	glVertex3f(0.5f, 0.5f, 0.f);
//	glVertex3f(-0.5f, 0.5f, 0.f);
//	glEnd();
//	glFlush();
//	glfwSwapBuffers(GetGLFWWindow());
//
//	__FUNCTION__
//}
