#pragma once
#include "Ball.h"

#define DELTA_SPEED 1
#define DELTA_WIDTH 10
#define DELTA_RADIUS 3
#define TIME 500
#define VALCRO 1
#define BONUS_SPEED 2

class Arkanoid;


Bonus* GetNewBonus(int x, int y, int numBonus);

class Bonus : public Object {
protected:
	int time;
	int radius;
	int speed;
public:
	Bonus(int x, int y, int time_) :Object(x, y), radius(BALL_RADIUS), speed(BONUS_SPEED), time(time_) {}
	Bonus(int x, int y) :Object(x, y), radius(BALL_RADIUS), speed(BONUS_SPEED), time(0) {}
	virtual ~Bonus() {}
	void UpdateTime();
	int GetTime();
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);

	void DrowBonus();
	void UpdatePos();
	bool Collision(Carriage &carriage);
	int GetLeftBorder();
	int GetRightBorder();
	int GetUpperBorder();
	int GetLowerBorder();
};

class BonusAddLife : public Bonus {
public:
	BonusAddLife(int x, int y) :Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusIncreaseSpeed : public Bonus {
public:
	BonusIncreaseSpeed(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusReduceSpeed : public Bonus {
public:
	BonusReduceSpeed(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusIncreaseCarriage : public Bonus {
public:
	BonusIncreaseCarriage(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusReduceCarriage : public Bonus {
public:
	BonusReduceCarriage(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusTrampoline : public Bonus {
public:
	BonusTrampoline(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusIncreaseBall : public Bonus {
public:
	BonusIncreaseBall(int x, int y) : Bonus(x, y, TIME) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};
class BonusAddVelcro : public Bonus {
public:
	BonusAddVelcro(int x, int y) : Bonus(x, y) {}
	virtual void Apply(Arkanoid &arkanoid);
	virtual void Ñancel(Arkanoid &arkanoid);
};