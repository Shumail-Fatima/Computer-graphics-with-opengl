#include <GL/glut.h>
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw house
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(-0.4, -0.65);
    glVertex2f(0.4, -0.65);
    glVertex2f(0.4, 0.1);
    glVertex2f(-0.4, 0.1);
    glEnd();

    // Draw door
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.2, 0.1); // brown
    glVertex2f(-0.1, -0.65);
    glVertex2f(0.1, -0.65);
    glVertex2f(0.1, -0.3);
    glVertex2f(-0.1, -0.3);
    glEnd();

    // Draw window
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.2, 0.1); // brown
    glVertex2f(0.15, -0.2);
    glVertex2f(0.3, -0.2);
    glVertex2f(0.3, -0.0);
    glVertex2f(0.15, -0.0);
    glEnd();

    // Draw roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.4, 0.2, 0.1); // Brown
    glVertex2f(-0.5, 0.1);
    glVertex2f(0.5, 0.1);
    glVertex2f(0.0, 0.7);
    glEnd();

    // Draw tree trunk
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.2, 0.1); // Dark brown
    glVertex2f(-0.8, -0.65);
    glVertex2f(-0.7, -0.65);
    glVertex2f(-0.7, -0.1);
    glVertex2f(-0.8, -0.1);
    glEnd();

    // Draw tree foliage
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0); // green
    glVertex2f(-0.85, -0.3);
    glVertex2f(-0.65, -0.3);
    glVertex2f(-0.75, 0.1);
    glEnd();


    // Draw sun
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(0.8, 0.8);
    for (int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(20);
        float dx = 0.1 * cosf(angle);
        float dy = 0.1 * sinf(angle);
        glVertex2f(0.8 + dx, 0.8 + dy);
    }
    glEnd();

    // Draw sun rays
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0); // Yellow
    for (int i = 0; i < 8; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(8);
        float dx = 0.2 * cosf(angle);
        float dy = 0.2 * sinf(angle);
        glVertex2f(0.8, 0.8);
        glVertex2f(0.8 + dx, 0.8 + dy);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.5, 0.8, 1.0, 1.0); // Sky blue background
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