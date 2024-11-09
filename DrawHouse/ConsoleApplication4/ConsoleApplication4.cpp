#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the house base using GL_POLYGON
    glColor3f(0.7f, 0.2f, 0.0f); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();

    // Draw the roof using GL_POLYGON
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(-0.55f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.55f, 0.0f);
    glEnd();

    // Draw the door using GL_POLYGON
    glColor3f(0.4f, 0.2f, 0.1f); // Dark brown color
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glEnd();

    // Draw the window using GL_POLYGON
    glColor3f(0.4f, 0.2f, 0.1f); // Dark brown color
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple House using GL_POLYGON");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    //return 0;
}