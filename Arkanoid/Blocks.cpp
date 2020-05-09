#include "Blocks.h"
#include "Bonus.h"
#define IMMORTAL 4



Block::Block(int x, int y)
	: Object(x, y), height(BLOCK_HEIGHT), width(BLOCK_WIDTH), score(BLOCKS_SCORE)
{
	strength = (int)((double)rand() / RAND_MAX * 5);
	if (rand() < RAND_MAX / 3) {
		int numBonus = (int)((double)rand() / RAND_MAX * 7) + 1;
		bonus = GetNewBonus(x, y, numBonus);
	}
	else {
		bonus = nullptr;
	}
}

Block::Block(int height_, int width_, int x, int y, int strength_, int score_)
	: Object(x, y), height(height_), width(width_), strength(strength_), bonus(nullptr), score(score_)
{
}

void Block::DrowBlock()
{
	labcolor_t color;
	switch (strength)
	{
	case 1:
		color = LABCOLOR_BLUE;
		break;
	case 2:
		color = LABCOLOR_GREEN;
		break;
	case 3:
		color = LABCOLOR_YELLOW;
		break;
	case IMMORTAL:
		color = LABCOLOR_RED;
		break;
	default:
		color = LABCOLOR_WHITE;
		break;
	}
	LabSetColor(color);
	LabDrawRectangle(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2);
}

int Block::Hit()
{
	if (strength != IMMORTAL) {
		strength--;
	}
	if (strength == 0)return score;
	return 0;
}

Bonus* Block::GetBonus()
{
	Bonus* ptr = bonus;
	bonus = nullptr;
	return ptr;
}

int Block::GetStrenght()
{
	return strength;
}

int Block::GetWidth()
{
	return width;
}

int Block::GetHeight()
{
	return height;
}

int Block::GetLeftBorder()
{
	return position.x - width / 2;
}

int Block::GetRightBorder()
{
	return position.x + width / 2;
}

int Block::GetUpperBorder()
{
	return position.y - height / 2;
}

int Block::GetLowerBorder()
{
	return position.y + height / 2;
}

MovableBlock::MovableBlock(int x, int y)
	: Block(x, y), speed(BLOCKS_SPEED, 0)
{
	score = MOVBLOCKS_SCORE;
}

void MovableBlock::UpdatePos(Table &tab)
{
	int  xOld = position.x;
	position.x += speed.vX;
	int crash = 0;
	int sectorX, sectorY;
	sectorX = position.x / tab.GetWidth();
	sectorY = position.y / tab.GetHeight();


	if (speed.vX > 0) {
		for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
			if (GetRightBorder() >= tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder() &&
				position.x < tab.GetVec(sectorY, sectorX)[i]->GetX() &&
				this != tab.GetVec(sectorY, sectorX)[i]) {
				position.x = 2 * tab.GetVec(sectorY, sectorX)[i]->GetLeftBorder() - GetRightBorder() - width / 2;
				speed.vX = -speed.vX;
				crash++;
			}
		}
		if (speed.vX > 0 && sectorX + 1 < LabGetWidth() / tab.GetWidth()) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX + 1).size(); ++i) {
				if (GetRightBorder() >= tab.GetVec(sectorY, sectorX + 1)[i]->GetLeftBorder() &&
					position.x < tab.GetVec(sectorY, sectorX + 1)[i]->GetX() &&
					this != tab.GetVec(sectorY, sectorX + 1)[i]) {
					position.x = 2 * tab.GetVec(sectorY, sectorX + 1)[i]->GetLeftBorder() - GetRightBorder() - width / 2;
					speed.vX = -speed.vX;
					crash++;
				}
			}
		}
	}


	if (speed.vX < 0) {
		for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX).size(); ++i) {
			if (GetLeftBorder() <= tab.GetVec(sectorY, sectorX)[i]->GetRightBorder() &&
				position.x > tab.GetVec(sectorY, sectorX)[i]->GetX() &&
				this != tab.GetVec(sectorY, sectorX)[i]) {
				position.x = 2 * tab.GetVec(sectorY, sectorX)[i]->GetRightBorder() - GetLeftBorder() + width / 2;
				speed.vX = -speed.vX;
				crash++;
			}
		}
		if (speed.vX < 0 && sectorX - 1 >= 0) {
			for (unsigned i = 0; i < tab.GetVec(sectorY, sectorX - 1).size(); ++i) {
				if (GetLeftBorder() <= tab.GetVec(sectorY, sectorX - 1)[i]->GetRightBorder() &&
					position.x > tab.GetVec(sectorY, sectorX - 1)[i]->GetX() &&
					this != tab.GetVec(sectorY, sectorX - 1)[i]) {
					position.x = 2 * tab.GetVec(sectorY, sectorX - 1)[i]->GetRightBorder() - GetLeftBorder() + width / 2;
					speed.vX = -speed.vX;
					crash++;
				}
			}
		}
	}


	if (GetLeftBorder() < 0) {
		position.x = -GetLeftBorder() + width / 2;
		speed.vX = -speed.vX;
		crash++;
	}
	else if (GetRightBorder() > LabGetWidth()) {
		position.x = 2 * LabGetWidth() - GetRightBorder() - width / 2;
		speed.vX = -speed.vX;
		crash++;
	}
	if (crash > 1)position.x = xOld;
}


Table::Table(int height_, int width_)
	:height(height_), width(width_)
{
	for (int i = 0; i < LabGetHeight() / height; ++i) {
		vector<vector<Block*>> ptr;
		for (int j = 0; j < LabGetWidth() / width; ++j) {
			vector<Block*> p;
			ptr.push_back(p);
		}
		table.push_back(ptr);
	}
}

std::vector<Block*> Table::GetVec(int x, int y)
{
	return table[x][y];
}

void Table::Update(vector<Block> &blocks, vector<MovableBlock> &movBlocks)
{
	for (unsigned i = 0; i < table.size(); ++i) {
		for (unsigned j = 0; j < table[i].size(); ++j) {
			table[i][j].clear();
		}
	}

	for (unsigned i = 0; i < blocks.size(); ++i) {
		if (blocks[i].GetStrenght() > 0) {
			int sectorXl = (blocks[i].GetLeftBorder()) / width;
			int sectorXr = (blocks[i].GetRightBorder() - 1) / width;
			int sectorY = blocks[i].GetY() / height;
			for (int j = sectorXl; j <= sectorXr; ++j) {
				table[sectorY][j].push_back(&blocks[i]);
			}
		}
	}

	for (unsigned i = 0; i < movBlocks.size(); ++i) {
		if (movBlocks[i].GetStrenght() > 0) {
			int sectorXl = (movBlocks[i].GetLeftBorder()) / width;
			int sectorXr = (movBlocks[i].GetRightBorder() - 1) / width;
			int sectorY = movBlocks[i].GetY() / height;
			for (int j = sectorXl; j <= sectorXr; ++j) {
				table[sectorY][j].push_back(&movBlocks[i]);
			}
		}
	}

}

int Table::GetWidth()
{
	return width;
}

int Table::GetHeight()
{
	return height;
}