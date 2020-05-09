#include "Ñarriage.h"
#include "Manager.h"

void Carriage::ShiftLeft()
{
	if (GetLeftBorder() - speed > 0)position.x -= speed;
	else position.x = width / 2;
}

void Carriage::ShiftRight()
{
	if (GetRightBorder() + speed < LabGetWidth())position.x += speed;
	else position.x = LabGetWidth() - width / 2;
}

void Carriage::ResizeWidth(int delta)
{
	width += delta;
	if (width <= MIN_WIDTH)width = MIN_WIDTH;
	else if (width >= MAX_WIDTH)width = MAX_WIDTH;
}

void Carriage::DrowCarriage()
{
	LabSetColor(LABCOLOR_WHITE);
	LabDrawRectangle(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2);
}


int Carriage::GetWidth()
{
	return width;
}

int Carriage::GetHeight()
{
	return height;
}

void Carriage::SetStartConfig()
{
	position.x = CARR_START_X;
	position.y = CARR_START_Y;
	width = CARR_WIDTH;
}

void Carriage::AddVelcro(int change)
{
	velcro += change;
}

bool Carriage::Sticky()
{
	if (velcro)return true;
	return false;
}

void Carriage::IncreaseVelcro()
{
	velcro--;
}

int Carriage::GetLeftBorder()
{
	return position.x - width / 2;
}

int Carriage::GetRightBorder()
{
	return position.x + width / 2;
}

int Carriage::GetUpperBorder()
{
	return position.y - height / 2;
}

int Carriage::GetLowerBorder()
{
	return position.y + height / 2;
}
