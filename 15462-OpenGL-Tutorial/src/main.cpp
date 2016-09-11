#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

// Based on the code from programming-technique.blogspot.com

using namespace std;

bool colorMode;
bool redFirst;

float t = 0.0f;
float dt = 0.001f;

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
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
}
//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The field of view angle, in degrees, in the y direction
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
	
	//GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	//GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glTranslatef(cos(t), 0.0f, -7.0f);  // Move right and into the screen
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(t*100, 1, 0, 0);
	glRotatef(t * 50, 0, 1, 0);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
	
	glutSwapBuffers(); //Send the 3D scene to the screen

	t += dt;
	glutPostRedisplay();
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
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop(); //Start the main loop
	return 0;
}