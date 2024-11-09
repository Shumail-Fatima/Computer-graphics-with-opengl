#include <GL/glut.h>
#include <cmath>

// Function to draw a small rectangle (arm)
void drawArm() {
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, -0.3f);
    glVertex2f(-0.05f, -0.3f);
    glEnd();
}

// Function to draw a large rectangle (shoulder)
void drawShoulder() {
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.6f, -0.1f);
    glVertex2f(-0.6f, -0.1f);
    glEnd();
}

// Function to draw a circle (head)
void drawHead() {
    int numSegments = 100;
    float radius = 0.15f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw the body (trapezoid shape)
void drawBody() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.45f, 0.0f);
    glVertex2f(0.45f, 0.0f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(-0.3f, -0.5f);
    glEnd();
}

// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the head
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f);  // Position for the head
    drawHead();
    glPopMatrix();

    // Draw the shoulder
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);  // Position for the shoulder
    drawShoulder();
    glPopMatrix();

    // Draw the left arm
    glPushMatrix();
    glTranslatef(-0.55f, 0.4f, 0.0f);  // Position for the left arm
    drawArm();
    glPopMatrix();

    // Draw the right arm
    glPushMatrix();
    glTranslatef(0.55f, 0.4f, 0.0f);  // Position for the right arm
    drawArm();
    glPopMatrix();

    // Draw the body
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);  // Position for the body
    drawBody();
    glPopMatrix();

    // Draw the rotated figure below the first one
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);  // Move the figure down
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // Rotate the figure 180 degrees
    drawBody();
    glPopMatrix();


    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    glColor3f(0.0f, 0.0f, 0.0f);           // Black color for the shapes
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Figure Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
