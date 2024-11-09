#include <GL/glut.h>
#include <iostream>

// the below code is for both drawing a sun and drawing a triangle or a quadrilateral of any kind

void tooth0() {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0.0, 1.0);
    glEnd();
}


void tooth1(double r) {
    double rad = 6.0 * 3.1416 / 180.0,
        sin6 = r * sin(rad), cos6 = r * cos(rad);

    glPushMatrix();
    glTranslatef(cos6, -sin6, 0.0);
    glScalef(2.0 * sin6, 2.0 * sin6, 1.0);
    tooth0();
    glPopMatrix();
}


void gear(double r) {
    glPushMatrix();
    for (int i = 1; i <= 30; ++i) {
        tooth1(r);
        glRotatef(12.0, 0.0, 0.0, 1.0);
    }
}


void move() {
    float speed = 0.0001;
    static int oldTime = clock(), newTime;

    newTime = clock();
    double deg = (newTime - oldTime) * speed;

    oldTime = newTime;

    glutPostRedisplay;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //tooth0();
    //tooth1(0.2);
    gear(0.5);
    move();


    //glBegin(GL_LINE_STRIP);
    //glColor3f(0.0, 0.0, 1.0);
    //glVertex2f(0.0, 0.0);
    //glVertex2f(0.2, 0.2);
    //glVertex2f(0.6, 0.2);
    //glVertex2f(0.6, 0.8);
    //glVertex2f(0.2, 0.8);
    //glVertex2f(0.0, 1.0);
    //glEnd();


    


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
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Simple Scene");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}