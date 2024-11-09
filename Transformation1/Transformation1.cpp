#include <cmath>
#include <gl/glut.h>
#define PI 3.141592

void display(void);
void drawWind(void);
void drawwindmill(void);
void drawplane();
void drawlandscape();
void drawfire();     // Draw fire effect
void drawsmoke();    // Draw smoke effect
void Timer(int value);
void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

// Global variables for animation
float windAngle = 0.0f;       // Rotation angle of windmill blades
float planePosX = 245.0f;     // X position of the plane
float planePosY = 200.0f;     // Y position of the plane, starting higher for a better trajectory
float planeAngle = -5.0f;     // Initial rotation angle of the plane, angled downwards
bool crashed = false;         // Flag to check if the plane has crashed

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawlandscape();  // Draw landscape first to set background
    drawwindmill();   // Draw the windmill
    drawplane();      // Draw the plane

    glutSwapBuffers();
}

void drawWind() // Single blade
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(0.0, 0.0); // Center of rotation
    glVertex2f(15.0, 30.0); // Adjusted blade size
    glVertex2f(35.0, 30.0);
    glEnd();
}

void drawwindmill() // Complete windmill with rotating blades
{
    // Draw windmill body first
    glPushMatrix();
    glColor3f(0.6, 0.6, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();
    glPopMatrix();

    // Draw windmill blades
    glPushMatrix();
    glTranslatef(125.0, 100.0, 0.0); // Move to the windmill's top center for blade rotation
    glRotatef(windAngle, 0.0, 0.0, 1.0); // Rotate the blades

    // Draw 4 blades rotating around the pivot
    drawWind(); // Blade 1
    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawWind(); // Blade 2
    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawWind(); // Blade 3
    glRotatef(90.0, 0.0, 0.0, 1.0);
    drawWind(); // Blade 4

    glPopMatrix(); // Restore transformation matrix to avoid affecting other objects
}

void Timer(int value)
{
    // Update variables for animation
    windAngle += 5.0f;  // Increase rotation angle for windmill blades
    if (windAngle >= 360.0f)
        windAngle = 0.0f;

    // Update the plane's position if it hasn't crashed yet
    if (!crashed) {
        planePosX -= 1.5f;  // Move plane to the left
        planePosY -= 1.2f;  // Move plane downwards faster
        planeAngle -= 0.5f; // Rotate plane more as it descends

        // Check if the plane has hit the ground (ground level at Y = 50.0)
        if (planePosY <= 50.0f) {
            planePosY = 50.0f;  // Set plane on ground
            crashed = true;     // Stop movement
        }
    }

    display();
    glutTimerFunc(30, Timer, 1);  // Register the timer callback again
}

void drawplane()
{
    glPushMatrix();
    glTranslatef(planePosX, planePosY, 0.0); // Move plane according to position
    glRotatef(planeAngle, 0.0, 0.0, 1.0);   // Rotate plane according to angle

    // Draw the main body of the plane
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 10.0);
    glVertex2f(-30.0, 0.0);
    glEnd();

    // Draw the wing of the plane
    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-1.0, -2.0);
    glVertex2f(-1.0, 5.0);
    glVertex2f(-17.0, 5.0);
    glEnd();

    // Draw fire and smoke if the plane has crashed
    if (crashed) {
        drawfire();   // Draw fire at the front of the plane
        drawsmoke();  // Draw smoke slightly above the fire
    }

    glPopMatrix();
}

void drawfire()
{
    // Position fire at the front of the crashed plane
    glPushMatrix();
    glTranslatef(-15.0f, 0.0f, 0.0f); // Position fire directly on the plane's nose
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color for fire
    glVertex2f(0.0, 0.0);
    glVertex2f(-5.0, 10.0);
    glVertex2f(5.0, 10.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.5, 0.0); // Orange color for fire
    glVertex2f(0.0, 5.0);
    glVertex2f(-4.0, 15.0);
    glVertex2f(4.0, 15.0);
    glEnd();
    glPopMatrix();
}

void drawsmoke()
{
    // Position smoke directly above the fire
    glPushMatrix();
    glTranslatef(-15.0f, 10.0f, 0.0f); // Position smoke slightly above the fire
    glColor3f(0.5, 0.5, 0.5); // Gray color for smoke
    for (int i = 0; i < 5; i++) {
        glBegin(GL_POLYGON);
        float angle;
        int numVertices = 20;
        for (int j = 0; j < numVertices; j++) {
            angle = 2.0f * PI * j / numVertices;
            glVertex2f(cos(angle) * (5.0f + (rand() % 5)) + (i * 3), sin(angle) * (5.0f + (rand() % 5)));
        }
        glEnd();
    }
    glPopMatrix();
}

void drawlandscape()
{
    glPushMatrix();
    // Draw a box of grass
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(250.0, 0.0);
    glVertex2f(250.0, 50.0);
    glVertex2f(0.0, 50.0);
    glVertex2f(0.0, 0.0);
    glEnd();

    // Draw mountains
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.6);
    glVertex2f(250.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(200.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(150.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(200.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(150.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);

    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(150.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(100.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(50.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(50.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(0.0, 50.0);
    glEnd();

    glPopMatrix();
}

void init()
{
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Plane Crash Simulation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, Timer, 1);
    glutMainLoop();
}