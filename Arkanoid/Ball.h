#pragma once
#include "labengine.h"
#include "Object.h"
#include <cmath>
#include "Blocks.h"
#include "Ñarriage.h"

#define BALL_RADIUS 10
#define BALL_SPEED_X 3
#define BALL_SPEED_Y 3
#define HEALTH 3
#define MAX_SPEED 6
#define MIN_SPEED 1

enum Side {
	LEFT, RIGHT, UP, DOWN
};

class Bonus;

class Ball : public Object {
private:
	int radius;
	SpeedVec speed;
	bool free;
	int offset;
public:
	Ball(int x, int y) :Object(x, y), radius(BALL_RADIUS), speed(BALL_SPEED_X, BALL_SPEED_Y), free(false), offset(0) {}
	void Hit(int side);
	void ResizeSpeed(int change);
	void ResizeRadius(int change);
	void DrowBall();
	int UpdatePos(Table &tab, Carriage &carriage, vector<Bonus*> &newBonus);
	int GetRadius();
	void Cling(int offset_);
	void Start();
	bool InGame();
	void SetStartConfig();
	virtual int GetLeftBorder();
	virtual int GetRightBorder();
	virtual int GetUpperBorder();
	virtual int GetLowerBorder();
};