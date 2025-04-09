// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "iostream"
#include "GL/glut.h"
#include <stdio.h>

#include "ImgUtil.h"

// Static Linked Library
#include "OutsideStaticMath.h"
#include "InsideStaticMath.h"

// Dynamic Linked Library
#include "InsideDynamicMath.h"
#include "OutsideDynamicMath.h"

#include "GLFW"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutMainLoop();
	return 0;
}