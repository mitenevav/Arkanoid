#pragma once
#include "labengine.h"
#include "Object.h"
#include <vector>
using namespace std;
#define BLOCKS_SPEED 1
#define BLOCKS_SCORE 30
#define BLOCK_WIDTH (LabGetWidth() / 12)
#define BLOCK_HEIGHT (LabGetHeight() / 25)
#define MOVBLOCKS_SCORE 50
class Bonus;

class Block : public Object {
protected:
	int height;
	int width;
	int strength;
	Bonus* bonus;
	int score;
public:
	Block(int x, int y);
	Block(int height_, int width_, int x, int y, int strength_, int score_);
	virtual ~Block() {}
	void DrowBlock();
	int Hit();
	Bonus* GetBonus();
	int GetStrenght();
	int GetWidth();
	int GetHeight();
	virtual int GetLeftBorder();
	virtual int GetRightBorder();
	virtual int GetUpperBorder();
	virtual int GetLowerBorder();
};


class MovableBlock;

class Table {
private:
	int height;
	int width;
	vector<vector<vector<Block*>>> table;
public:
	Table(int height_, int width_);
	vector<Block*> GetVec(int x, int y);
	void Update(vector<Block> &blocks, vector<MovableBlock> &movBlocks);
	int GetWidth();
	int GetHeight();
};

class MovableBlock : public Block {
private:
	SpeedVec speed;
public:
	MovableBlock(int x, int y);
	void UpdatePos(Table &tab);
};