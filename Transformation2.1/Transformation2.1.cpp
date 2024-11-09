#include <GL/glut.h>
#include <cmath>

const float DEG2RAD = 3.14159 / 180;
const float branchLength = 0.2;
const float smallBranchLength = 0.08;

void drawBranch(float length) {
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, length);
    glEnd();
}

void drawSmallBranches() {
    glPushMatrix();
    glTranslatef(0.0f, branchLength / 2, 0.0f);
    glRotatef(45, 0.0f, 0.0f, 1.0f);
    drawBranch(smallBranchLength);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, branchLength / 2, 0.0f);
    glRotatef(-45, 0.0f, 0.0f, 1.0f);
    drawBranch(smallBranchLength);
    glPopMatrix();
}

void drawSnowflakeBranch() {
    drawBranch(branchLength);
    drawSmallBranches();

    glPushMatrix();
    glTranslatef(0.0f, branchLength, 0.0f);
    drawSmallBranches();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glRotatef(i * 60, 0.0f, 0.0f, 1.0f);
        drawSnowflakeBranch();
        glPopMatrix();
    }

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    glColor3f(0.0f, 0.0f, 0.0f);           // Black color for the snowflake
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Snowflake");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}



/*
#include <GL/glut.h>
#include <cmath>

void drawSnowflake() {
    // Set the color of the snowflake
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the snowflake's arms
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++) {
        // Calculate the angle for each arm
        float angle = i * 2 * 3.141592 / 6;

        // Draw the main arm
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(angle), sin(angle));

        // Draw the smaller, angled line
        glVertex2f(cos(angle), sin(angle));
        glVertex2f(cos(angle + 3.141592 / 12), sin(angle + 3.141592 / 12));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the viewing transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the snowflake
    drawSnowflake();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Snowflake");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/

/*
void drawSnowflake() {
    // Set the color of the snowflake to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the snowflake arms
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++) {
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(i * 2 * 3.141592 / 6), sin(i * 2 * 3.141592 / 6));
    }
    glEnd();

    // Draw the snowflake branches
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++) {
        float angle = i * 2 * 3.141592 / 6 + 3.141592 / 12;
        glVertex2f(cos(i * 2 * 3.141592 / 6), sin(i * 2 * 3.141592 / 6));
        glVertex2f(cos(angle) * 0.8, sin(angle) * 0.8);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the snowflake
    drawSnowflake();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Snowflake");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}*/