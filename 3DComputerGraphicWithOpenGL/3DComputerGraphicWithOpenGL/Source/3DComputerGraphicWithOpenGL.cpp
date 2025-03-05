// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "iostream"
#include "GL/glut.h"
#include <stdio.h>

// DynamicLibrary
#include "MathLibrary.h"
#include "DynamicMathLibrary.h"

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
    MathLibrary::fibonacci_init(1,1);
    int Result2 = MathLibrary::fibonacci_index();
    printf("MathLibrary's fibonacci index is %d", Result2);

    DynamicMathLibrary::fibonacci_init(1, 1);
    // Write out the sequence values until overflow.
    do {
        std::cout << DynamicMathLibrary::fibonacci_index() << ": "
            << DynamicMathLibrary::fibonacci_current() << std::endl;
    } while (DynamicMathLibrary::fibonacci_next());
    // Report count of values written before overflow.
    std::cout << DynamicMathLibrary::fibonacci_index() + 1 <<
        " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << std::endl;
 
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