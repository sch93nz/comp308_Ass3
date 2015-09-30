//---------------------------------------------------------------------------
//
// Copyright (c) 2015 Taehyun Rhee, Joshua Scott, Ben Allen
//
// This software is provided 'as-is' for assignment of COMP308 in ECS,
// Victoria University of Wellington, without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
//----------------------------------------------------------------------------

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "comp308.hpp"
#include "imageLoader.hpp"
#include "shaderLoader.hpp"
#include "geometry.hpp"

using namespace std;
using namespace comp308;


// Global variables
//
GLuint g_winWidth  = 640;
GLuint g_winHeight = 480;
GLuint g_mainWindow = 0;


// Projection values
//
float g_fovy = 20.0;
float g_znear = 0.1;
float g_zfar = 1000.0;


// Mouse controlled Camera values
//
bool g_mouseDown = false;
vec2 g_mousePos;
float g_yRotation = 0;
float g_xRotation = 0;
float g_zoomFactor = 1.0;


// Scene information
////
//GLuint g_texture = 0;
GLuint g_texture1 = 0;
GLuint g_shader = 0;
bool g_useShader = false;


// Objects to be rendered
//
Geometry *ball;
Geometry *box;
Geometry *bunny;
Geometry *sphere;
Geometry *table;
Geometry *teapot;
Geometry *torus;


// Sets up where and what the light is
// Called once on start up
//
void initLight() {
	float direction[]	  = {0.0f, 0.0f, 1.0f, 0.0f};
	float diffintensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
	float ambient[]       = {0.2f, 0.2f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffintensity);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);


	glEnable(GL_LIGHT0);
}








void initShader() {
	g_shader = makeShaderProgram("work/res/shaders/shaderDemo.vert", "work/res/shaders/shaderDemo.frag");
}


// Sets up where the camera is in the scene
// Called every frame
//
void setUpCamera() {
	// Set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_fovy, float(g_winWidth) / float(g_winHeight), g_znear, g_zfar);

	// Set up the view part of the model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -50 * g_zoomFactor);
	glRotatef(g_xRotation, 1, 0, 0);
	glRotatef(g_yRotation, 0, 1, 0);
}


// Draw function
//
void draw() {

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Enable flags for normal rendering
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	setUpCamera();


	// Without shaders
	//
	if (!g_useShader) {


	glPushMatrix();
		box->renderGeometry();
			glPopMatrix();
			glPushMatrix();
		bunny->renderGeometry();
		glPopMatrix();
			glPushMatrix();
		table->renderGeometry();
		glPopMatrix();
			glPushMatrix();
		torus->renderGeometry();
		glPopMatrix();
			glPushMatrix();
		ball->renderGeometry();
		glPopMatrix();
			glPushMatrix();
		teapot->renderGeometry();
        glPopMatrix();
		glFlush();

	// With shaders (no lighting)
	//
	} else {

		//// Texture setup
		////

		//// Enable Drawing texures
		//glEnable(GL_TEXTURE_2D);
		//// Set the location for binding the texture
		//glActiveTexture(GL_TEXTURE0);
		//// Bind the texture
		//glBindTexture(GL_TEXTURE_2D, g_texture);

		//// Use the shader we made
		//glUseProgram(g_shader);

		//// Set our sampler (texture0) to use GL_TEXTURE0 as the source
		//glUniform1i(glGetUniformLocation(g_shader, "texture0"), 0);
		glPushMatrix();
		glTranslatef(2.5, 2.5,0);
		box->renderGeometry();
		glPopMatrix();

		//// Render a single square as our geometry
		//// You would normally render your geometry here
		//glBegin(GL_QUADS);
		//glNormal3f(0.0, 0.0, 1.0);
		//glTexCoord2f(0.0, 0.0);
		//glVertex3f(-5.0, -5.0, 0.0);
		//glTexCoord2f(0.0, 1.0);
		//glVertex3f(-5.0, 5.0, 0.0);
		//glTexCoord2f(1.0, 1.0);
		//glVertex3f(5.0, 5.0, 0.0);
		//glTexCoord2f(1.0, 0.0);
		//glVertex3f(5.0, -5.0, 0.0);
		//glEnd();
		glFlush();

		// Unbind our shader
		glUseProgram(0);

	}


	// Disable flags for cleanup (optional)
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);

	// Move the buffer we just drew to the front
	glutSwapBuffers();

	// Queue the next frame to be drawn straight away
	glutPostRedisplay();
}


// Reshape function
//
void reshape(int w, int h) {
    if (h == 0) h = 1;

	g_winWidth = w;
	g_winHeight = h;

    // Sets the openGL rendering window to match the window size
    glViewport(0, 0, g_winWidth, g_winHeight);
}


// Keyboard callback
// Called once per button state change
//
void keyboardCallback(unsigned char key, int x, int y) {
	cout << "Keyboard Callback :: key=" << key << ", x,y=(" << x << "," << y << ")" << endl;
	// YOUR CODE GOES HERE
	// ...
}


// Special Keyboard callback
// Called once per button state change
//
void specialCallback(int key, int x, int y) {
	cout << "Special Callback :: key=" << key << ", x,y=(" << x << "," << y << ")" << endl;
	// YOUR CODE GOES HERE
	// ...
}


// Mouse Button Callback function
// Called once per button state change
//
void mouseCallback(int button, int state, int x, int y) {
	cout << "Mouse Callback :: button=" << button << ", state=" << state << ", x,y=(" << x << "," << y << ")" << endl;
	// YOUR CODE GOES HERE
	// ...
	switch(button){

		case 0: // left mouse button
			g_mouseDown = (state==0);
			g_mousePos = vec2(x, y);
			break;

		case 2: // right mouse button
			if (state==0)
				g_useShader = !g_useShader;
			break;

		case 3: // scroll foward/up
			g_zoomFactor /= 1.1;
			break;

		case 4: // scroll back/down
			g_zoomFactor *= 1.1;
			break;
	}
}


// Mouse Motion Callback function
// Called once per frame if the mouse has moved and
// at least one mouse button has an active state
//
void mouseMotionCallback(int x, int y) {
	cout << "Mouse Motion Callback :: x,y=(" << x << "," << y << ")" << endl;
	// YOUR CODE GOES HERE
	// ...
	if (g_mouseDown) {
		vec2 dif = vec2(x,y) - g_mousePos;
		g_mousePos = vec2(x,y);
		g_yRotation += 0.3 * dif.x;
		g_xRotation += 0.3 * dif.y;
	}
}



//Main program
//
int main(int argc, char **argv) {



	if(argc != 1){
		cout << "No arguments expected" << endl;
		exit(EXIT_FAILURE);
	}

	// Initialise GL, GLU and GLUT
	glutInit(&argc, argv);

	// Setting up the display
	// - RGB color model + Alpha Channel = GLUT_RGBA
	// - Double buffered = GLUT_DOUBLE
	// - Depth buffer = GLUT_DEPTH
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	// Initialise window size and create window
	glutInitWindowSize(g_winWidth, g_winHeight);
	g_mainWindow = glutCreateWindow("COMP308 Assignment 3");


	// Initilise GLEW
	// must be done after creating GL context (glutCreateWindow in this case)
	GLenum err = glewInit();
	if (GLEW_OK != err) { // Problem: glewInit failed, something is seriously wrong.
		cerr << "Error: " << glewGetErrorString(err) << endl;
		abort(); // Unrecoverable error
	}

	cout << "Using OpenGL " << glGetString(GL_VERSION) << endl;
	cout << "Using GLEW " << glewGetString(GLEW_VERSION) << endl;



	// Register functions for callback
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialCallback);

	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotionCallback);

	initLight();
	initShader();


	string _table = "work/res/assets/table.obj";
	string _bunny = "work/res/assets/bunny.obj";
	string _teapot = "work/res/assets/teapot.obj";
	string _ball = "work/res/assets/sphere.obj";
	string _box = "work/res/assets/box.obj";
	string _torus = "work/res/assets/torus.obj";

	table = new Geometry(_table);
	table->loadTexture("work/res/textures/wood.jpg");
	table->changeScale(vec3(1.2, 1.2, 1.2));

	bunny = new Geometry(_bunny);
	bunny->translate(vec3(0, 0.5, 0));
	bunny->setAmbient(vec3(0.25,0.20725,0.20725));
	bunny->setDiffuse(vec3(1,0.829,0.829));
	bunny->setSpecular(vec3(0.296648,0.296648,0.296648));
	bunny->setShine(0.088);

	//bunny->rotate(vec4(0, 1, 0, 180));

	teapot = new Geometry(_teapot);
	teapot->translate(vec3(-5.5, 0.45, -5.5));
    teapot->setAmbient(vec3(0.054,0.127,0.2125));
    teapot->setDiffuse(vec3(0.18144,0.4284,0.714));
    teapot->setSpecular(vec3(0.166721,0.271906,0.393548));
    teapot->setShine(0.2);

	ball = new Geometry(_ball);
	ball->translate(vec3(-5.5, 2, 5.5));
	ball->setAmbient(vec3(0.2125,0.1275,0.054));
	ball->setDiffuse(vec3(0.714,0.4284,0.18144));
	ball->setSpecular(vec3(0.393548,0.271906,0.166721));
	ball->setShine(0.2);

	box = new Geometry(_box);
	box->loadTexture("work/res/textures/brick.jpg");
	box->changeScale(vec3(2, 2, 2));
	box->rotate(vec4(0, 1, 0, 180));
	box->translate(vec3(-5.5, 2.5, 5.5));

	torus = new Geometry(_torus);
	torus->translate(vec3(5.5, 1.05, 5.5));
	torus->setAmbient(vec3(0.0,0.0,0.0));
	torus->setDiffuse(vec3(0.5,0.0,0.0));
	torus->setSpecular(vec3(0.7,0.6,0.6));
	torus->setShine(0.25);
	// Loop required by GLUT
	// This will not return until we tell GLUT to finish
	glutMainLoop();

	  delete table;
	  delete bunny;
	  delete teapot;
	  delete box;
	  delete torus;



	// Don't forget to delete all pointers that we made
	return 0;
}
