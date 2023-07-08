#pragma once
#include <vector>
#include "Cell.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	void startingShape();
private:
	int getLivingNeighbors(int x, int y);
	Clock clockActivating;
	Time elapsedActivated;
	Clock clockStart;
	Time elapsedStart;

	std::vector<Cell> grid;
	std::vector<Cell> gridCopy;

	bool isRunning;
	const int WINDOW_SIZE = 840;
	const int CELL_SIZE = 12;
	const int GRID_SIZE = WINDOW_SIZE / 12;
	const int ROWS = WINDOW_SIZE / CELL_SIZE;
	const int FPS = 60;

	RenderWindow window;
};