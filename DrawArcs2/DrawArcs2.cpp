#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265358979323846;

// Function to draw an arc between two angles with given radius and center
void drawArc(float cx, float cy, float radius, float start_angle, float end_angle, int num_segments) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= num_segments; i++) {
        float theta = start_angle + i * (end_angle - start_angle) / num_segments;
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw an AND gate
void drawAndGate(float x, float y) {
    // Left rectangle
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + 0.4f);
    glVertex2f(x, y + 0.4f);
    glVertex2f(x + 0.3f, y + 0.4f);
    glVertex2f(x + 0.3f, y + 0.4f);
    glVertex2f(x + 0.3f, y);
    glVertex2f(x + 0.3f, y);
    glVertex2f(x, y);
    glEnd();

    // Right arc
    drawArc(x + 0.3f, y + 0.2f, 0.2f, -PI / 2, PI / 2, 30);

    // Input and output lines
    glBegin(GL_LINES);
    glVertex2f(x - 0.1f, y + 0.3f); // Top input
    glVertex2f(x, y + 0.3f);
    glVertex2f(x - 0.1f, y + 0.1f); // Bottom input
    glVertex2f(x, y + 0.1f);
    glVertex2f(x + 0.5f, y + 0.2f); // Output
    glVertex2f(x + 0.3f, y + 0.2f);
    glEnd();
}

// Function to draw an OR gate
void drawOrGate(float x, float y) {
    // Left curved arc
    drawArc(x, y + 0.2f, 0.4f, -PI / 6, PI / 6, 30);

    // Right curved arc
    drawArc(x + 0.4f, y + 0.2f, 0.2f, -PI / 2, PI / 2, 30);

    // Bottom and top arcs
    drawArc(x, y + 0.2f, 0.45f, PI / 6, -PI / 6, 30);

    // Input and output lines
    glBegin(GL_LINES);
    glVertex2f(x - 0.15f, y + 0.3f); // Top input
    glVertex2f(x + 0.05f, y + 0.3f);
    glVertex2f(x - 0.15f, y + 0.1f); // Bottom input
    glVertex2f(x + 0.05f, y + 0.1f);
    glVertex2f(x + 0.6f, y + 0.2f);  // Output
    glVertex2f(x + 0.4f, y + 0.2f);
    glEnd();
}

// Function to draw an XOR gate
void drawXorGate(float x, float y) {
    // Additional arc for XOR
    drawArc(x - 0.05f, y + 0.2f, 0.4f, -PI / 6, PI / 6, 30);

    // OR gate shape
    drawOrGate(x, y);
}

// Function to draw a NOT gate
void drawNotGate(float x, float y) {
    // Triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x, y + 0.4f);
    glVertex2f(x + 0.3f, y + 0.2f);
    glEnd();

    // Circle for NOT gate output
    float radius = 0.05f;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 30; i++) {
        float theta = 2.0f * PI * float(i) / float(30);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + 0.35f + dx, y + 0.2f + dy);
    }
    glEnd();

    // Input and output lines
    glBegin(GL_LINES);
    glVertex2f(x - 0.1f, y + 0.2f); // Input
    glVertex2f(x, y + 0.2f);
    glVertex2f(x + 0.35f + radius, y + 0.2f); // Output
    glVertex2f(x + 0.5f, y + 0.2f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the gates at different positions
    drawAndGate(-0.8f, 0.5f);
    drawOrGate(-0.8f, 0.0f);
    drawXorGate(-0.8f, -0.5f);
    drawNotGate(0.2f, -0.5f);

    glFlush();
}

// Initialize OpenGL
void initOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glColor3f(0.0, 0.0, 0.0);          // Set drawing color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Logic Gates");

    initOpenGL();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
