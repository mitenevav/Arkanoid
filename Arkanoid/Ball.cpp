#include "Ball.h"
#include "Bonus.h"
#include "Manager.h"

void Ball::Hit(int side)
{
	switch (side)
	{
	case LEFT:
		speed.vX = -speed.vX;
		break;
	case RIGHT:
		speed.vX = -speed.vX;
		break;
	case UP:
		speed.vY = -speed.vY;
		break;
	case DOWN:
		speed.vY = -speed.vY;
		break;
	default:
		break;
	}
}

void Ball::ResizeSpeed(int change)
{
	if (abs(speed.vY) < MAX_SPEED && abs(speed.vY) > MIN_SPEED) {
		speed.vX = (int)(speed.vX * (1 + (double)change / fabs(speed.vX)));
		speed.vY = (int)(speed.vY * (1 + (double)change / fabs(speed.vY)));
	}
}

void Ball::ResizeRadius(int change)
{
	radius += change;
}

void Ball::DrowBall()
{
	LabSetColor(LABCOLOR_WHITE);
	LabDrawCircle(position.x, position.y, radius);
}

int Ball::UpdatePos(Table &tab, Carriage &carriage, vector<Bonus*> &newBonus)
{
	int score = 0;

	if (!free) {
		position.x = carriage.GetX() + offset;
		position.y = carriage.GetUpperBorder() - radius;
		return score;
	}
	position.x += speed.vX;
	position.y += speed.vY;


	if (position.x - radius < 0) {
		Hit(LEFT);
		position.x = -position.x + 2 * radius;
	}
	else if (position.x + radius > LabGetWidth()) {
		Hit(RIGHT);
		position.x = 2 * LabGetWidth() - position.x - 2 * radius;
	}

	if (position.y - radius < 0) {
		Hit(UP);
		position.y = -position.y + 2 * radius;
	}


	int sectorX, sectorY;
	sectorX = position.x / tab.GetWidth();
	sectorY = position.y / tab.GetHeight();

	Bonus* ptr;

	if (speed.vY < 0) {
		if (tab.GetVec(sectorY, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX)[i]->GetLowerBorder() > position.y - radius &&
					tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder() < position.x &&
					tab.GetVec(sectorY, sectorX)[i]->GetRightBorder() > position.x &&
					tab.GetVec(sectorY, sectorX)[i]->GetY() < position.y) {

					Hit(UP);
					score += tab.GetVec(sectorY, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.y = 2 * (tab.GetVec(sectorY, sectorX)[i]->GetLowerBorder()) - position.y + 2 * radius;
				}
			}
		}
		if (sectorY - 1 >= 0 && tab.GetVec(sectorY - 1, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY - 1, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY - 1, sectorX)[i]->GetLowerBorder() > position.y - radius &&
					tab.GetVec(sectorY - 1, sectorX)[i]->GetLeftBorder() < position.x &&
					tab.GetVec(sectorY - 1, sectorX)[i]->GetRightBorder() > position.x &&
					tab.GetVec(sectorY - 1, sectorX)[i]->GetY() < position.y) {

					Hit(UP);
					score += tab.GetVec(sectorY - 1, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY - 1, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.y = 2 * (tab.GetVec(sectorY - 1, sectorX)[i]->GetLowerBorder()) - position.y + 2 * radius;
				}
			}
		}
	}
	else if (speed.vY > 0) {
		if (tab.GetVec(sectorY, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX)[i]->GetUpperBorder() < position.y + radius &&
					tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder() < position.x &&
					tab.GetVec(sectorY, sectorX)[i]->GetRightBorder() > position.x &&
					tab.GetVec(sectorY, sectorX)[i]->GetY() > position.y) {

					Hit(DOWN);
					score += tab.GetVec(sectorY, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.y = -position.y + 2 * (tab.GetVec(sectorY, sectorX)[i]->GetUpperBorder()) - 2 * radius;
				}
			}
		}
		if (sectorY + 1 < LabGetHeight() / tab.GetHeight() && tab.GetVec(sectorY + 1, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY + 1, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY + 1, sectorX)[i]->GetUpperBorder() < position.y + radius &&
					tab.GetVec(sectorY + 1, sectorX)[i]->GetLeftBorder() < position.x &&
					tab.GetVec(sectorY + 1, sectorX)[i]->GetRightBorder() > position.x &&
					tab.GetVec(sectorY + 1, sectorX)[i]->GetY() > position.y) {

					Hit(DOWN);
					score += tab.GetVec(sectorY + 1, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY + 1, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);

					}
					position.y = -position.y + 2 * (tab.GetVec(sectorY + 1, sectorX)[i]->GetUpperBorder()) - 2 * radius;
				}
			}
		}
		if (GetLowerBorder() > carriage.GetUpperBorder() && position.x > carriage.GetLeftBorder() && position.x < carriage.GetRightBorder()) {

			Hit(DOWN);
			if (carriage.Sticky()) {
				position.y = carriage.GetUpperBorder() - radius;
				free = false;
				offset = position.x - carriage.GetX();
				carriage.IncreaseVelcro();
			}
		}
	}

	if (speed.vX < 0) {
		if (tab.GetVec(sectorY, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX)[i]->GetRightBorder() > position.x - radius &&
					tab.GetVec(sectorY, sectorX)[i]->GetLowerBorder() > position.y &&
					tab.GetVec(sectorY, sectorX)[i]->GetUpperBorder() < position.y &&
					tab.GetVec(sectorY, sectorX)[i]->GetX() < position.x) {

					Hit(LEFT);
					score += tab.GetVec(sectorY, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.x = 2 * (tab.GetVec(sectorY, sectorX)[i]->GetRightBorder()) - position.x + 2 * radius;
				}
			}
		}
		if (sectorX - 1 >= 0 && tab.GetVec(sectorY, sectorX - 1).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX - 1).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX - 1)[i]->GetRightBorder() > position.x - radius &&
					tab.GetVec(sectorY, sectorX - 1)[i]->GetLowerBorder() > position.y &&
					tab.GetVec(sectorY, sectorX - 1)[i]->GetUpperBorder() < position.y &&
					tab.GetVec(sectorY, sectorX - 1)[i]->GetX() < position.x) {

					Hit(LEFT);
					score += tab.GetVec(sectorY, sectorX - 1)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX - 1)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.x = 2 * (tab.GetVec(sectorY, sectorX - 1)[i]->GetRightBorder()) - position.x + 2 * radius;
				}
			}
		}
	}
	else if (speed.vX > 0) {
		if (tab.GetVec(sectorY, sectorX).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder() < position.x + radius &&
					tab.GetVec(sectorY, sectorX)[i]->GetLowerBorder() > position.y &&
					tab.GetVec(sectorY, sectorX)[i]->GetUpperBorder() < position.y &&
					tab.GetVec(sectorY, sectorX)[i]->GetX() > position.x) {

					Hit(RIGHT);
					score += tab.GetVec(sectorY, sectorX)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.x = -position.x + 2 * (tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder()) - 2 * radius;
				}
			}
		}
		if (sectorX + 1 < LabGetWidth() / tab.GetWidth() && tab.GetVec(sectorY, sectorX + 1).size()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX + 1).size(); ++i) {
				if (tab.GetVec(sectorY, sectorX + 1)[i]->GetLeftBorder() < position.x + radius &&
					tab.GetVec(sectorY, sectorX + 1)[i]->GetLowerBorder() > position.y &&
					tab.GetVec(sectorY, sectorX + 1)[i]->GetUpperBorder() < position.y &&
					tab.GetVec(sectorY, sectorX + 1)[i]->GetX() > position.x) {

					Hit(RIGHT);
					score += tab.GetVec(sectorY, sectorX + 1)[i]->Hit();
					ptr = tab.GetVec(sectorY, sectorX + 1)[i]->GetBonus();
					if (ptr) {
						newBonus.push_back(ptr);
					}
					position.x = -position.x + 2 * (tab.GetVec(sectorY, sectorX + 1)[i]->GetLeftBorder()) - 2 * radius;
				}
			}
		}
	}
	return score;
}

int Ball::GetRadius()
{
	return radius;
}

int Ball::GetLeftBorder()
{
	return position.x - radius;
}

int Ball::GetRightBorder()
{
	return position.x + radius;
}

int Ball::GetUpperBorder()
{
	return position.y - radius;
}

int Ball::GetLowerBorder()
{
	return position.y + radius;
}

void Ball::Cling(int offset_)
{
	free = false;
	offset = offset_;
}

void Ball::Start()
{
	free = true;
}

bool Ball::InGame()
{
	if (GetLowerBorder() < LabGetHeight())return true;
	return false;
}

void Ball::SetStartConfig()
{
	position.x = BALL_START_X;
	position.y = BALL_START_Y;
	Cling(0);
	speed.vX = BALL_SPEED_X;
	speed.vY = BALL_SPEED_Y;
}