#include <iostream>
#include "labengine.h"
#include "Ñarriage.h"
#include "Ball.h"
#include "Blocks.h"
#include "Manager.h"
#include "Bonus.h"
#include <vector>
using namespace std;

int main() {
	labparams_t param;
	param.height = 600;
	param.scale = 1;
	param.width = 1080;
	
if (LabInitWith(&param))
{
	labkey_t key = LABKEY_ENTER;

	Arkanoid arcanoid;
	arcanoid.MakeBlocks();

	while (key != LABKEY_ESC && arcanoid.Status())
	{
		if (LabInputKeyReady() != LAB_FALSE) {
			key = LabInputKey();
			arcanoid.PressButton(key);
		}
		arcanoid.UpdateAllPosition();
		arcanoid.AddNewBonus();
		arcanoid.UpdateBonus();
		arcanoid.DeleteOldBonus();
		arcanoid.DrawAll();
		
		LabDelay(10);

	}
	LabTerm();
	cout << "GAME OVER" << endl;
	cout << "Your score : " << arcanoid.score << endl;
}

	return 0;
}