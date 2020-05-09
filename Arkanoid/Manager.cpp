#include "Manager.h"

void Arkanoid::Die()
{
	life--;
}

void Arkanoid::AddLife()
{
	life++;
}

int Arkanoid::GetLife()
{
	return life;
}

void Arkanoid::MakeBlocks()
{
	int y = BLOCK_HEIGHT / 2;
	for (int i = 0; i < NUM_LINES; ++i) {
		int x = BLOCK_WIDTH / 2;

		for (int j = 0; j < NUM_COLUMNS; ++j) {

			if (rand() < RAND_MAX / 2) {
				blocks.push_back(Block(x, y));
			}
			else {
				movBlocks.push_back(MovableBlock(x, y));
			}

			x += BLOCK_WIDTH;
		}
		y += BLOCK_HEIGHT;
	}
}

void Arkanoid::PressButton(labkey_t key)
{
	switch (key) {
	case LABKEY_RIGHT:
		carriage.ShiftRight();
		break;
	case LABKEY_LEFT:
		carriage.ShiftLeft();
		break;
	case LABKEY_UP:
		ball.Start();
		break;
	default:
		break;
	}
}

void Arkanoid::UpdateAllPosition()
{
	table.Update(blocks, movBlocks);
	score += ball.UpdatePos(table, carriage, newBonus);
	for (unsigned i = 0; i < movBlocks.size(); ++i) {
		if (movBlocks[i].GetStrenght() > 0) {
			movBlocks[i].UpdatePos(table);
		}
	}
	for (unsigned i = 0; i < flyBonus.size(); ++i) {
		flyBonus[i]->UpdatePos();
	}
}

void Arkanoid::AddNewBonus()
{
	for (unsigned i = 0; i < newBonus.size(); ++i) {
		flyBonus.push_back(newBonus[i]);
	}
	newBonus.clear();
}

void Arkanoid::UpdateBonus()
{
	vector<Bonus*> supp;
	for (unsigned i = 0; i < flyBonus.size(); ++i) {
		if (flyBonus[i]->Collision(carriage)) {
			flyBonus[i]->Apply(*this);
			activeBonus.push_back(flyBonus[i]);
		}
		else if (flyBonus[i]->GetUpperBorder() < carriage.GetLowerBorder()) {
			supp.push_back(flyBonus[i]);
		}
		else {
			delete flyBonus[i];
			flyBonus[i] = nullptr;
		}
	}
	flyBonus = supp;
	supp.clear();
}

void Arkanoid::DeleteOldBonus()
{
	vector<Bonus*> supp;
	for (unsigned i = 0; i < activeBonus.size(); ++i) {
		activeBonus[i]->UpdateTime();
		if (activeBonus[i]->GetTime() < 0) {
			activeBonus[i]->Ñancel(*this);
			delete activeBonus[i];
			activeBonus[i] = nullptr;
		}
		else {
			supp.push_back(activeBonus[i]);
		}
	}
	activeBonus = supp;
	supp.clear();
}

void Arkanoid::DrawAll()
{
	LabClear();

	for (unsigned i = 0; i < blocks.size(); ++i) {
		if (blocks[i].GetStrenght() > 0) {
			blocks[i].DrowBlock();
		}
	}
	for (unsigned i = 0; i < movBlocks.size(); ++i) {
		if (movBlocks[i].GetStrenght() > 0) {
			movBlocks[i].DrowBlock();
		}
	}
	for (unsigned i = 0; i < flyBonus.size(); ++i) {
		flyBonus[i]->DrowBonus();
	}
	ball.DrowBall();
	carriage.DrowCarriage();
	LabDrawFlush();
}

bool Arkanoid::Status()
{
	if (!ball.InGame()) {
		Die();
		if (GetLife()) {
			MakeStartConfig();
		}
		else {
			return false;
		}
	}
	return true;
}

void Arkanoid::MakeStartConfig()
{
	carriage.SetStartConfig();
	ball.SetStartConfig();
}
