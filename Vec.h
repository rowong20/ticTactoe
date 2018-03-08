
#ifndef VEC_H
#define VEC_H
using namespace std;

struct Vec {
	float x;
	float y;
	Vec()
	{
		x = 0;
		y = 0;
	}
	Vec(float i, float j)
	{
		x = i;
		y = j;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	void add(Vec num)
	{
		x += num.x;
		y += num.y;
	}
	void print()
	{
		cout << "(" << x << ", " << y << ")";
	}
};


#endif // VEC_H
