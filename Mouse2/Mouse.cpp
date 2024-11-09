#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <random>
#include <stdio.h> 

/*
const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480;


void board(int r, int c) {

	for (int i = 0; i < r; i += 20) {
		for (int j = 0; j < c; j += 20) {

			if ((i + j) % 2 == 0) // if i + j is even
				glColor3f(0.6, 0.6, 0.6);
			else
				glColor3f(0.2, 0.2, 0.2);

			glBegin(GL_LINE_STRIP);
			glVertex2i(i, j); // draw the chimney
			glVertex2i(i, j + 20);
			glVertex2i(i + 20, j + 20);
			glVertex2i(i + 20, j);
			glVertex2i(i, j);
			glEnd();

		}

	}

	glFlush();

}

void myMovedMouse(int mouseX, int mouseY)
{
	int x = mouseX; //grab the mouse position
	int y = screenHeight – mouseY; // flip it as usual
	int brushSize = 20;
	glRecti(x, y, x + brushSize, y + brushSize);
	glFlush();
}



void handleKeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC key to quit
		exit(0);
		break;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glBegin(GL_LINE_LOOP);



	board(100, 100);

	glFlush(); // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("my first attempt"); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	glutMotionFunc(myMovedMouse);
	glutKeyboardFunc(handleKeyPress);
	myInit();
	glutMainLoop(); // go into a perpetual loop
}*/

#include <GL/glut.h>
#include <vector>

// Define a simple Point struct
struct Point {
	float x, y;
};

// Vector to store points where we click
std::vector<Point> points;

// Initialize OpenGL settings
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0); // Set background to white
	glPointSize(5.0); // Set the size of points
}

// Display function to render all points
void display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
	glColor3f(0.0, 0.0, 0.0); // Set point color to black

	glBegin(GL_POINTS);
	for (const auto& point : points) {
		glVertex2f(point.x, point.y); // Draw each point
	}
	glEnd();

	glFlush(); // Render now
}

// Mouse callback function
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Map the window coordinates to OpenGL coordinates
		float xpos = (float)x / (glutGet(GLUT_WINDOW_WIDTH) / 2.0f) - 1.0f;
		float ypos = 1.0f - (float)y / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);

		// Add point to the vector
		points.push_back({ xpos, ypos });

		// Request display update
		glutPostRedisplay();
	}
}

// Main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mouse Click to Draw Points");

	init(); // Call our initialization function
	glutDisplayFunc(display); // Set display callback
	glutMouseFunc(mouse); // Set mouse callback

	glutMainLoop(); // Enter the event-processing loop
	return 0;
}

