#include <GL/glut.h>
#include <iostream>

using namespace std;

class Point2 {
public:
    Point2() { x = y = 0.0f; }
    Point2(float xx, float yy) { x = xx; y = yy; }
    void set(float xx, float yy) { x = xx; y = yy; }
    float getX() { return x; }
    float getY() { return y; }
    void draw()
    {
        // Set the color and size for the points
        //glColor3f(0.0, 1.0, 0.0);
        glPointSize(10.0); // Adjust the point size as needed
        glBegin(GL_POINTS);
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }

private:
    float x, y;
};


class IntRect
{
public:
    IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
    IntRect(int left, int right, int bottom, int top)
    {
        l = left; r = right; b = bottom; t = top;
    } // constructors
    void set(int left, int right, int bottom, int top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    int getl() { return l; }
    int getr() { return r; }
    int getb() { return b; }
    int gett() { return t; }
    void draw(void); // draw this rectangle using OpenGL
private:
    int l, r, b, t;
}; //end class IntRect:

void IntRect::draw(void)
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(l, b);
    glVertex2i(r, b);
    glVertex2i(r, t);
    glVertex2i(l, t);
    glEnd();
}// end IntRect::draw



class RealRect
{
public:
    RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructors
    RealRect(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    } // constructors
    void set(float left, float right, float bottom, float top)
    {
        l = left; r = right; b = bottom; t = top;
    }
    float getl() { return l; }
    float getr() { return r; }
    float getb() { return b; }
    float gett() { return t; }
    void draw(void); // draw this rectangle using OpenGL
private:
    float l, r, b, t;
}; //end class RealRect:
void RealRect::draw(void)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(l, b);
    glVertex2f(r, b);
    glVertex2f(r, t);
    glVertex2f(l, t);
    glEnd();
}// end RealRect



class Canvas {
public:
    Canvas(int width, int height);
    void setWindow(float l, float r, float b, float t);
    void setViewport(int l, int r, int b, int
        t);
    void clearScreen();
    void setBackgroundColor(float r, float g, float b);
    void setColor(float r, float g, float b);


private:
    float CP[2]; // Current Position
};

Canvas::Canvas(int width, int height)// constructor
{
    char* argv[1]; // dmmy argument list for glutInit()
    char dummyString[8];
    argv[0] = dummyString; // hook up the pointer
    int argc = 1; // to satisfy glutInit()

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Geometric Shapes"); // open the screen window
    setWindow(0, (float)width, 0, (float)height); //default world window
    setViewport(0, width, 0, height); //default viewport
    //CP.set(0.0f, 0.0f); //initialize the CP to (0,0)

    CP[0] = 0.0f;
    CP[1] = 0.0f;
}//end Canvas constructor

void Canvas::setWindow(float l, float r, float b, float t)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(l, r, b, t); //set the world window
}// end setWindow

// Changed float to int in void Canvas
void Canvas::setViewport(int l, int r, int b, int t)
{
    glViewport(l, b, r - l, t - b);
} // end setViewport


void Canvas::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}// clearScreen

void Canvas::setBackgroundColor(float r, float g, float b)
{
    glClearColor(r, g, b, 0.0);
}// end setBackgroundColor

void Canvas::setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}//edn setColor

// Function to draw a line
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Function to draw a rectangle
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a circle
void drawCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Display callback function
void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color for the shapes
    //glColor3f(1.0, 0.0, 0.0);

    // Draw a line
    glColor3f(1.0, 0.0, 0.0);
    drawLine(50, 50, 350, 350);

    // Draw a rectangle
    // glColor3f(1.0, 0.0, 0.0);
    //drawRectangle(100, 100, 200, 100);

    // Draw a circle
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(250, 250, 50);

    // Create Point2 objects
    Point2 point1(50, 50), point2(100, 100), point3(150, 150);
    glColor3f(1.0, 0.0, 0.0);
    // Draw the points
    point1.draw();
    point2.draw();
    point3.draw();

    IntRect rect1(50, 250, 50, 200);
    glColor3f(1.0, 0.0, 0.0);
    rect1.draw();

    RealRect rect2(150.5f, 350.5f, 150.5f, 300.5f);
    glColor3f(1.0, 0.0, 0.0);
    rect2.draw();

    // Flush the buffer to display the shapes
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    // Create a Canvas object
    //Canvas canvas(400, 400, "Geometric Shapes");

    Canvas canvas(400, 400);

    canvas.setBackgroundColor(135.0f/255.0, 206.0f/255.0f, 250.0f/255.0f);

    // Set the display callback function
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();

    return 0;
}