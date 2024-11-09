#include <GL/glut.h>
#include <vector>

// Struct to store points
struct Point {
    float x, y;
};

// Vector to store line segments
std::vector<Point> points;
bool isDragging = false;

// Initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);          // Set drawing color to black
    glPointSize(2.0);                  // Set point size for clearer drawing
    glLineWidth(2.0);                  // Set line width
    gluOrtho2D(0, 800, 600, 0);        // Set coordinate system (0,0) to (800,600)
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw all points as lines
    glBegin(GL_LINE_STRIP);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glFlush();
}

// Mouse function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            points.push_back({ static_cast<float>(x), static_cast<float>(y) });
            glutPostRedisplay();
        }
        else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
}

// Mouse motion function
void mouseMotion(int x, int y) {
    if (isDragging) {
        points.push_back({ static_cast<float>(x), static_cast<float>(y) });
        glutPostRedisplay();
    }
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Mouse Drag to Draw");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
