#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <random>
#include <stdio.h> 


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
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Draw Board"); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}
