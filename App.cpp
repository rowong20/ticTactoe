#include "App.h"
//TODO:
// Fill out state structure that keeps track of X, O , Empty states
// Draw X, O when clicked
// Keep track of Single/Multiplayer
// Condition to Win
// Create AI to play tic tac toe
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
	Rect rect1(.5, 0, .05, .3), rect2(-.5, 0, .05, .3), rect3(.61,0,.05,.3);
	list.push_back(rect1);
	list.push_back(rect2);
	list.push_back(rect3);
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Initial screen, two buttons displayed for single or two player if button chosen time to play
	if (choose == false)
	{
		for (int i = 0; i < list.size(); i++)
		{
			glBegin(GL_POLYGON);
			glVertex2f(list.at(i).x, list.at(i).y);
			glVertex2f(list.at(i).x + list.at(i).width, list.at(i).y);
			glVertex2f(list.at(i).x + list.at(i).width, list.at(i).y - list.at(i).height);
			glVertex2f(list.at(i).x, list.at(i).y - list.at(i).height);
			glEnd();
		}
	}
	else
	{
		//Tic tac toe board
		glBegin(GL_LINES);
		glColor3d(1.0, 1.0, 1.0);

		glVertex2f(-0.33f, 1.0f);
		glVertex2f(-0.33f, -1.0f);

		glVertex2f(0.33f, 1.0f);
		glVertex2f(0.33f, -1.0f);

		glVertex2f(1.0f, -0.33f);
		glVertex2f(-1.0f, -0.33f);

		glVertex2f(1.0f, 0.33f);
		glVertex2f(-1.0f, 0.33f);
		glEnd();
		//create states
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++) {
				entries.push_back(new stateArea(-0.66 + 0.66*i, -0.66 + 0.66*j));
			}
		}
		//test
		for (int i = 0; i < 9; i++)
		{
			entries[i]->drawX();
		}
	}
    // Draw a yellow cross
	/*
    glColor3d(1.0, 1.0, 0.0);
    
    glBegin(GL_LINES);
    
    glVertex2f(mx - 0.05f, my);
    glVertex2f(mx + 0.05f, my);
    
    glVertex2f(mx, my - 0.05f);
    glVertex2f(mx, my + 0.05f);
    
    glEnd();
    */
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
	Vec mouseLoc(mx, my);
	//if mouse is clicked within a button, keep track in within array.
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i).contains(mouseLoc)) {
			choose = true;
		}
	}
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
