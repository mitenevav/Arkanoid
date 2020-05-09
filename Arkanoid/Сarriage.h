#pragma once
#include "labengine.h"
#include "Object.h"


#define CARR_HEIGHT 10
#define CARR_WIDTH 100
#define CARR_SPEED 20
#define MIN_WIDTH 50
#define MAX_WIDTH 250
class Carriage : public Object {
private:
	int height;
	int width;
	int speed;
	int velcro;
public:
	Carriage(int x, int y) : Object(x, y), height(CARR_HEIGHT), width(CARR_WIDTH), speed(CARR_SPEED), velcro(0) {}
	void ShiftLeft();
	void ShiftRight();
	void ResizeWidth(int delta);
	void DrowCarriage();
	int GetWidth();
	int GetHeight();
	void SetStartConfig();
	void AddVelcro(int change);
	bool Sticky();
	void IncreaseVelcro();
	virtual int GetLeftBorder();
	virtual int GetRightBorder();
	virtual int GetUpperBorder();
	virtual int GetLowerBorder();
};