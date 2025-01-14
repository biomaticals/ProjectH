// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#include "iostream"
#include "GL/glut.h"

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
    // 책의 내용대로 glViewport를 명시적으로 사용하지 않은 상태로 윈도우를 조절하면 종횡비를 유지하려고 하기 때문에 왜곡이 발생하고,
    // glViewport를 명시적으로 사용하면 물체에 왜곡이 일어나지 않고 그대로 유지됨을 확인할 수 있습니다.

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