#include <GL/glut.h>
#include <iostream>

// the below code is for both drawing a sun and drawing a triangle or a quadrilateral of any kind


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

    // Draw sun
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 25; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(25);
        float dx = 0.4 * cosf(angle);
        float dy = 0.4 * sinf(angle);
        glVertex2f(0.0 + dx, 0.0 + dy);
    }
    glEnd();

    // Draw sun rays
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    for (int i = 0; i < 15; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(15);
        float dx = 0.9 * cosf(angle);
        float dy = 0.9 * sinf(angle);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0 + dx, 0.0 + dy);
    }
    glEnd();

    glFlush();
};


void init() {
    //glClearColor(0.5, 0.8, 1.0, 1.0); // Sky blue background
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Simple Scene");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}