#include <iostream>
#include <fstream>
#include <string>
#include <gl/glut.h>

using namespace std;

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.9f, 0.9f, 0.9f, 0.0);
	glColor3f(1, 0, 0);
	glFlush();
}

int screenWidth = 640;  int screenHeight = 480;
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("HT First OGL Program");

	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}





