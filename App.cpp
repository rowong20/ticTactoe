#include "App.h"
#include <stdlib.h>
//TODO:
// Create another screen when someone wins?
// Keep track of Single/Multiplayer
// Create AI to play tic tac toe
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
	Rect rect1(.5, 0, .05, .3), rect2(-.5, 0, .05, .3), rect3(.61,0,.05,.3);
	list.push_back(rect1);
	list.push_back(rect2);
	list.push_back(rect3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			entries.push_back(new stateArea(-0.66 + 0.66*j, 0.66 - 0.66*i));
		}
	}
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
	if (choose2p == false&& compplayer==false)
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
		//manage states
		if (choose2p == true) {
			for (int i = 0; i < 9; i++)
			{
				if (within[i] == 1)
				{
					if (player) {
						if (entries.at(i)->isEmpty()) {
							entries.at(i)->shape = 1;
							player = false;
						}
					}
					else {
						if (entries.at(i)->isEmpty()) {
							entries.at(i)->shape = 2;
							player = true;
						}
					}
				}
				entries.at(i)->draw();
			}
		}
		else if (compplayer == true)//computer logic
		{
			for (int i = 0; i < 9; i++)
			{
				if (player)
				{
					if (within[i] == 1) {
						if (entries.at(i)->isEmpty()) {
							cout <<"Entering at "<< i << ": " << entries.at(i)->shape << endl;
							entries.at(i)->shape = 1;
							entries.at(i)->unoccupied = false;
							player = false;
						}
					}
				}
				if (!player)
				{
					foundNumber = false;
					while (!foundNumber)
					{
						test = rand()%9;
						if (entries.at(test)->isEmpty()) {
							cout << "Entering at " << i << ": " << test << endl;
							entries.at(test)->shape = 2;
							player = true;
							foundNumber = true;
						}
					}
				}
				cout <<i<<": "<< entries.at(i)->shape << endl;
				entries.at(i)->draw();
			}
		}
		for(int i =0;i<8;i+=3)//Checking rows for winners
		{
			//o is 1, x is 2, so if sum is 3 or 6 there is winner. 
			if ((entries.at(i)->shape==entries.at(i+1)->shape)&& (entries.at(i + 1)->shape==entries.at(i+2)->shape)&& entries.at(i + 1)->shape==1)
			{
				cout << "Player 1 wins! "<<endl;
				break;
			}
			else if ((entries.at(i)->shape == entries.at(i + 1)->shape&& entries.at(i + 1)->shape == entries.at(i + 2)->shape) && entries.at(i + 1)->shape == 2)
			{
				cout << "Player 2 wins!" << endl;
				break;
			}
		}
		for (int i = 0; i<3; i++)//Checking columns for winners
		{
			//o is 1, x is 2, so if sum is 3 or 6 there is winner. 
			if ((entries.at(i)->shape == entries.at(i + 3)->shape) && (entries.at(i + 3)->shape == entries.at(i + 6)->shape) && entries.at(i)->shape == 1)
			{
				cout << "Player 1 wins! " << endl;
				break;
			}
			else if ((entries.at(i)->shape == entries.at(i + 3)->shape&& entries.at(i + 3)->shape == entries.at(i + 6)->shape) && entries.at(i)->shape == 2)
			{
				cout << "Player 2 wins!" << endl;
				break;
			}
		}
		//Checking Diagonals
		if ((entries.at(0)->shape == entries.at(4)->shape) && (entries.at(4)->shape == entries.at(8)->shape) && entries.at(0)->shape == 1)
		{
			cout << "Player 1 wins! " << endl;
		}
		else if ((entries.at(0)->shape == entries.at(4)->shape) && (entries.at(4)->shape == entries.at(8)->shape) && entries.at(0)->shape == 2)
		{
			cout << "Player 2 wins!" << endl;
		}
		//Checking Diagonals
		if ((entries.at(2)->shape == entries.at(4)->shape) && (entries.at(4)->shape == entries.at(6)->shape) && entries.at(2)->shape == 1)
		{
			cout << "Player 1 wins! " << endl;
		}
		else if ((entries.at(2)->shape == entries.at(4)->shape) && (entries.at(4)->shape == entries.at(6)->shape) && entries.at(2)->shape == 2)
		{
			cout << "Player 2 wins!" << endl;
		}
	}

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
	
	if (choose2p == false&& compplayer==false) {//choose between 1/2 players
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(0).contains(mouseLoc) || list.at(2).contains(mouseLoc)) {
				cout << "Chosen 2p!" << endl;
				choose2p = true;
			}
			else if (list.at(1).contains(mouseLoc))
			{
				cout << "Chosen computer!" << endl;
				compplayer = true;
			}
		}
	}
	else{//if mouse is clicked within a button, keep track in within array.
		for (int i = 0; i < entries.size(); i++)
		{
			if (entries[i]->contains(mouseLoc)) {
				//cout << "Mouse is within cell" << i << endl;
				within[i] = 1;
			}
			else
				within[i] = 0;
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
