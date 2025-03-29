// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "iostream"
#include "GL/glut.h"
#include <stdio.h>

// Static Linked Library
#include "OutsideStaticMath.h"
#include "InsideStaticMath.h"

// Dynamic Linked Library
#include "InsideDynamicMath.h"
#include "OutsideDynamicMath.h"

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("[코드 5-2] 흑색 바탕에 백색 사각형 그리기 1");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}