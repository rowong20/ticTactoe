#ifndef App_hpp
#define App_hpp
#define PI 3.14159265
#include "GlutApp.h"
#include "Vec.h"
#include <vector>
using namespace std;
struct Rect {
	float x;
	float y;
	float width;
	float height;
	Rect()
	{
		x = 0;
		y = 0;
	}
	Rect(float i, float j, float wide, float tall)
	{
		x = i;
		y = j;
		width = wide;
		height = tall;
	}
	bool contains(Vec coords)
	{
		if (coords.x<x || coords.x>(x + width))
			return false;
		else if (coords.y > y || coords.y < (y - height))
			return false;
		else
			return true;
	}
};
struct stateArea {
	float x;
	float y;
	bool occupied;
	stateArea()
	{
		occupied = false;
		x = 0;
		y = 0;
	}
	stateArea(float inx, float iny)
	{
		occupied = false;
		x = inx;
		y = iny;
	}
	void drawO()
	{
		occupied = true;
		vector<Vec*> points;
		Vec center(x, y);
		generateCircleData(points, center, .2, 30);
		glBegin(GL_LINES);
		for (int i = 0; i < points.size(); i++)
		{
			glVertex2f(points[i]->getX(),points[i]->getY());
		}
		glEnd();
	}
	void generateCircleData(vector<Vec*> &points, Vec center, float radius, int resolution) {
		// Clear the points vector to make sure it's empty before you start
		points.clear();
		float theta, ntheta, x, y, nx, ny;
		for (int i = 0; i<resolution; i++)
		{
			theta = (2 * PI / resolution)*i;
			ntheta = (2 * PI / resolution)*(i + 1);
			x = radius*(float)cos(theta);
			y = radius*(float)sin(theta);
			nx = radius*(float)cos(ntheta);
			ny = radius*(float)sin(ntheta);
			points.push_back(new Vec(x + center.getX(), y + center.getY()));
			points.push_back(new Vec(nx + center.getX(), ny + center.getY()));
		}
	}
	void drawX()
	{
		occupied = true;
		vector<Vec*> points;
		Vec center(x, y);
		generateXData(points, center);
		glBegin(GL_LINES);
		for (int i = 0; i < points.size(); i++)
		{
			glVertex2f(points[i]->getX(), points[i]->getY());
		}
		glEnd();
	}
	void generateXData(vector<Vec*> &points, Vec center) {
		// Clear the points vector to make sure it's empty before you start
		points.clear();
		points.push_back(new Vec(0.2 + center.getX(), 0.2 + center.getY()));
		points.push_back(new Vec(-0.2 + center.getX(), -0.2 + center.getY()));
		points.push_back(new Vec(0.2 + center.getX(), -0.2 + center.getY()));
		points.push_back(new Vec(-0.2 + center.getX(), 0.2 + center.getY()));
	}
	bool isEmpty()
	{
		return occupied;

	}
};

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
	bool choose=false;
	int within[3] = { 0,0,0 };
	vector<Rect> list;
	vector<stateArea*> entries;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
};

#endif