#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

// Based on the code from programming-technique.blogspot.com

using namespace std;

bool colorMode;
bool redFirst;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
		colorMode = !colorMode;
		glutPostRedisplay();
		break;
	case 'r':
		redFirst = !redFirst;
		glutPostRedisplay();
		break;
	case 27: //Escape key
		exit(0);
	}
}
//Initializes 3D rendering
void initRendering() {
	colorMode = false;
	redFirst = true;
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}
//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(0,                  //The camera angle
		(double)w / (double)h, //The width-to-height ratio
		1.0,                   //The near z clipping coordinate
		200.0);                //The far z clipping coordinate
}
//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	if (!colorMode)
		glColor3f(1.0, 1.0, 1.0);

	if (colorMode)
		glColor3f(0.255, 0.412, 0.882);
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	//Trapezoid
	glVertex3f(-0.7f, -1.5f, -5.0f);
	glVertex3f(0.7f, -1.5f, -5.0f);
	glVertex3f(0.7f, -0.5f, -5.0f);
	glVertex3f(-0.7f, -0.5f, -5.0f);
	glEnd(); //End quadrilateral coordinates

	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	//Triangle
	if (colorMode)
		glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.5f, 0.5f, -5.0f);
	if (colorMode)
		glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0f, 1.5f, -5.0f);
	if (colorMode)
		glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.5f, 0.5f, -5.0f);
	glEnd(); //End triangle coordinates

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawScene2D()
{
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0.0, 0.0);
	//glVertex3f(-2, -1, 0);
	glVertex2f(-2, -1);
	//glColor3f(0.0, 1.0, 0.0);
	//glVertex3f(1, -1, 0);
	glVertex2f(1, -1);
	//glColor3f(0.0, 0.0, 1.0);
	//glVertex3f(0, 2, 0);
	glVertex2f(0, 2);
	glEnd();
	glPopMatrix();

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawGreenSquare() 
{
	glColor4f(0.5, 1, 0.5, 0.5); // alpha!!!

	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(-0.25, 0.25, 0);
	glBegin(GL_QUADS);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
	glEnd();
	glPopMatrix();
}

void drawRedSquare()
{
	glColor4f(1, 0.5, 0.5, 0.5); // alpha!!!

	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(0.25, -0.25, 0);
	glBegin(GL_QUADS);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
	glEnd();
	glPopMatrix();
}

void drawSceneAlpha()
{
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // many possible blend modes here!

	if (redFirst)
	{
		drawRedSquare();
		glTranslatef(0, 0, -0.01);
		drawGreenSquare();
	}
	else
	{
		drawGreenSquare();
		glTranslatef(0, 0, -0.01);
		drawRedSquare();
	}

	glDisable(GL_BLEND);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800); //Set the window size
	//Create the window
	glutCreateWindow("15-462 OpenGL Tutorial");
	initRendering(); //Initialize rendering
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawSceneAlpha);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop(); //Start the main loop
	return 0;
}