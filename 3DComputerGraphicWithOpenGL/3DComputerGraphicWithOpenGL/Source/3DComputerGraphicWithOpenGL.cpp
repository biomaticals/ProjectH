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
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(.1f);
    glutSolidSphere(2.f, 5, 3);
    glutWireTorus(1.f, 3.f, 5, 3);
    glutSolidCone(5.f, 10.f, 5, 3);
    glutWireIcosahedron();
    glutSolidTeapot(5);
    glFlush();
}

int main(int argc, char** argv)
{
    const double a = 2.f;
    const double b = 5.f;

    double Result1 = OutsideStaticMath::Arithmetic::Add(a, b);
    std::printf("OutsideStaticMath : %f + %f = %f\n", a, b, Result1);

    double Result2 = InsideStaticMath::Arithmetic::Subtract(a, b);
    std::printf("InsideStaticMath : %f - %f = %f\n", a, b, Result2);

    double Result3 = OutsideDynamicMath::Multiply(a, b);
    std::printf("OutsideDynamicMath : %f * %f = %f\n", a, b, Result3);

    double Result4 = OutsideDynamicMath::Divide(a, b);
    std::printf("InsideDynamicMath : %f * %f = %f\n", a, b, Result4);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(2560, 1440);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}