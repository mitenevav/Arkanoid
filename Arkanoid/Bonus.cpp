#include "Bonus.h"
#include "Manager.h"

enum {
	ADD_LIFE = 1, INCREASE_SPEED, REDUCE_SPEED, INCREASE_CARRIAGE, REDUCE_CARRIAGE, TRAMPOLINE, INCREASE_BALL, ADD_VELCRO
};


void Bonus::UpdateTime()
{
	time--;
}

int Bonus::GetTime()
{
	return time;
}

void Bonus::Apply(Arkanoid &arkanoid)
{
}

void Bonus::Ñancel(Arkanoid &arkanoid)
{
}

void Bonus::DrowBonus()
{
	LabSetColor(LABCOLOR_MAGENTA);
	LabDrawCircle(position.x, position.y, radius);
}

void Bonus::UpdatePos()
{
	position.y += speed;
}

bool Bonus::Collision(Carriage & carriage)
{
	if (carriage.GetUpperBorder() < GetLowerBorder() &&
		GetRightBorder() > carriage.GetLeftBorder() && GetLeftBorder() < carriage.GetRightBorder()) {
		return true;
	}
	return false;
}

int Bonus::GetLeftBorder()
{
	return position.x - radius;
}

int Bonus::GetRightBorder()
{
	return position.x + radius;
}

int Bonus::GetUpperBorder()
{
	return position.y - radius;
}

int Bonus::GetLowerBorder()
{
	return position.y + radius;
}

void BonusAddLife::Apply(Arkanoid &arkanoid)
{
	arkanoid.AddLife();
}

void BonusAddLife::Ñancel(Arkanoid &arkanoid)
{
}

void BonusIncreaseSpeed::Apply(Arkanoid &arkanoid)
{
	arkanoid.ball.ResizeSpeed(DELTA_SPEED);
}

void BonusIncreaseSpeed::Ñancel(Arkanoid &arkanoid)
{
}

void BonusReduceSpeed::Apply(Arkanoid &arkanoid)
{
	arkanoid.ball.ResizeSpeed(-DELTA_SPEED);
}

void BonusReduceSpeed::Ñancel(Arkanoid &arkanoid)
{
}

void BonusIncreaseCarriage::Apply(Arkanoid &arkanoid)
{
	arkanoid.carriage.ResizeWidth(DELTA_WIDTH);
}

void BonusIncreaseCarriage::Ñancel(Arkanoid &arkanoid)
{
}

void BonusReduceCarriage::Apply(Arkanoid &arkanoid)
{
	arkanoid.carriage.ResizeWidth(-DELTA_WIDTH);
}

void BonusReduceCarriage::Ñancel(Arkanoid &arkanoid)
{
}

void BonusTrampoline::Apply(Arkanoid &arkanoid)
{
	arkanoid.blocks.push_back(Block(5, LabGetWidth(), LabGetWidth() / 2, LabGetHeight() - 5, 1, 0));
}

void BonusTrampoline::Ñancel(Arkanoid &arkanoid)
{
}

void BonusIncreaseBall::Apply(Arkanoid &arkanoid)
{
	arkanoid.ball.ResizeRadius(DELTA_RADIUS);
}

void BonusIncreaseBall::Ñancel(Arkanoid &arkanoid)
{
	arkanoid.ball.ResizeRadius(-DELTA_RADIUS);
}

void BonusAddVelcro::Apply(Arkanoid &arkanoid)
{
	arkanoid.carriage.AddVelcro(VALCRO);
}

void BonusAddVelcro::Ñancel(Arkanoid &arkanoid)
{
}


Bonus* GetNewBonus(int x, int y, int numBonus) {
	Bonus* bonus;
	switch (numBonus)
	{
	case ADD_LIFE:
		bonus = new BonusAddLife(x, y);
		break;
	case INCREASE_SPEED:
		bonus = new BonusIncreaseSpeed(x, y);
		break;
	case REDUCE_SPEED:
		bonus = new BonusReduceSpeed(x, y);
		break;
	case INCREASE_CARRIAGE:
		bonus = new BonusIncreaseCarriage(x, y);
		break;
	case REDUCE_CARRIAGE:
		bonus = new BonusReduceCarriage(x, y);
		break;
	case TRAMPOLINE:
		bonus = new BonusTrampoline(x, y);
		break;
	case INCREASE_BALL:
		bonus = new BonusIncreaseBall(x, y);
		break;
	case ADD_VELCRO:
		bonus = new BonusAddVelcro(x, y);
		break;
	default:
		bonus = nullptr;
		break;
	}
	return bonus;
}