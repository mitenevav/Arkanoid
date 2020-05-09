#pragma once
#include <cmath>
struct Point {
	int x;
	int y;
	Point(int x_, int y_) : x(x_), y(y_) {}
};
struct SpeedVec {
	int vX;
	int vY;
	SpeedVec(int speed) :vX((int)((double)speed/sqrt(2))), vY(-(int)((double)speed / sqrt(2))) {}
	SpeedVec(int speedX, int speedY) : vX(speedX), vY(speedY) {};
};

class Object {
protected:
	Point position;
public:
	Object(int x, int y) :position(x, y) {}
	virtual int GetLeftBorder() = 0;
	virtual int GetRightBorder() = 0;
	virtual int GetUpperBorder() = 0;
	virtual int GetLowerBorder() = 0;
	int GetX();
	int GetY();
	virtual ~Object() {}
};