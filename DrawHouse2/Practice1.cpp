#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <random>



//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a �dot� is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glBegin(GL_LINE_LOOP);
	glVertex2i(40, 40); // draw the shell of house
	glVertex2i(40, 90);
	glVertex2i(70, 120);
	glVertex2i(100, 90);
	glVertex2i(100, 40);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 100); // draw the chimney
	glVertex2i(50, 120);
	glVertex2i(60, 120);
	glVertex2i(60, 110);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 40); // draw the chimney
	glVertex2i(50, 75);
	glVertex2i(60, 75);
	glVertex2i(60, 40);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(80, 70); // draw the chimney
	glVertex2i(80, 80);
	glVertex2i(90, 80);
	glVertex2i(90, 70);
	glVertex2i(80, 70);
	glEnd();


	glFlush(); // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("my first attempt"); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}
