#pragma once
#include "Ball.h"
#include "Bonus.h"
#include "labengine.h"
#include <queue>
#define LIFE 3
#define NUM_COLUMNS (int)(LabGetWidth() / BLOCK_WIDTH)
#define NUM_LINES (int)(LabGetHeight() / 4 / BLOCK_HEIGHT)

#define CARR_START_X (int)(LabGetWidth() / 2)
#define CARR_START_Y (int)(LabGetHeight() - CARR_HEIGHT)
#define BALL_START_X (int)(LabGetWidth() / 2)
#define BALL_START_Y (int)(CARR_START_Y - CARR_HEIGHT / 2 - BALL_RADIUS)


class Arkanoid {
public:
	int life;
	int score;
	Ball ball;
	Carriage carriage;
	vector<Block> blocks;
	vector<MovableBlock> movBlocks;
	Table table;
	vector<Bonus*> flyBonus;
	vector<Bonus*> newBonus;
	vector<Bonus*> activeBonus;

	Arkanoid() :life(LIFE), score(0), ball(LabGetWidth() / 2, LabGetHeight() / 2), carriage(CARR_START_X, CARR_START_Y), table(BLOCK_HEIGHT, BLOCK_WIDTH) {}
	void Die();
	void AddLife();
	int GetLife();
	void MakeBlocks();
	void PressButton(labkey_t key);
	void UpdateAllPosition();
	void AddNewBonus();
	void UpdateBonus();
	void DeleteOldBonus();
	void DrawAll();
	bool Status();
	void MakeStartConfig();
};