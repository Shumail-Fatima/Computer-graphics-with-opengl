#include <GL/glut.h>
#include <string>

// Global variables to hold the display text and position
std::string displayText = "";
int windowWidth = 800;
int windowHeight = 600;

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set the background color to black
    glColor3f(1.0, 1.0, 1.0);          // Set the text color to white
    glMatrixMode(GL_PROJECTION);       // Set up the projection matrix
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);  // Orthographic projection
}

// Function to display text at a specified position
void renderBitmapString(float x, float y, void* font, const std::string& str) {
    glRasterPos2f(x, y);
    for (char c : str) {
        glutBitmapCharacter(font, c);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    // Display the text at a fixed position
    renderBitmapString(100, windowHeight / 2, GLUT_BITMAP_TIMES_ROMAN_24, displayText);

    glutSwapBuffers();  // Swap buffers for double buffering
}

// Keyboard function to handle keypresses
void keyboard(unsigned char key, int x, int y) {
    // Append the key pressed to the display text
    displayText += key;

    // Redraw the screen with the updated text
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Double buffering and RGB color mode
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL Keyboard Input");

    init();  // Call the init function to set up OpenGL

    // Register callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();  // Enter the main event loop
    return 0;
}
