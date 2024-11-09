#include <GL/glut.h>
#include <iostream>

// the below code is for both drawing a sun and drawing a triangle or a quadrilateral of any kind


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*
    glColor3f(0.25, 1.0, 0.25);
    GLfloat angle, raioX = 0.3f, raioY = 0.3f;
    GLfloat circle_points = 100;
    GLfloat circle_angle = 3.1415926f / 2.0f;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= circle_points; i++) {
        GLfloat current_angle = circle_angle * i / circle_points;
        glVertex2f(0.5 + cos(current_angle) * raioX, 0.5 + sin(current_angle) * raioY);
    }
    glEnd();*/


    // change raioX and raioY for diff arc radius. for now this results for arc to be drawn also outside of the 
    // viewport window but originally it is drawn completely on world window 
    glColor3f(0.25, 1.0, 0.25);
    GLfloat angle, raioX = 0.4f, raioY = 0.4f;
    GLfloat circle_points = 100.0f;

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i < circle_points; i++) {
        angle = 0.5f * 3.1415926f * i / circle_points;
        glVertex2f(0.5 + cos(angle) * raioX, 0.5 + sin(angle) * raioY);

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