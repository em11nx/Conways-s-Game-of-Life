#include "Game.h"

void copyVector(std::vector<Cell> &vSource, std::vector<Cell> &vDestination)
{
	vDestination.clear();
	for (int i = 0; i < vSource.size(); i++)
	{
		vDestination.push_back(vSource[i]);
	}
}

Game::Game()
{
	window.create(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Conway's Game of Life");
	window.setFramerateLimit(FPS);
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			Cell newCell(i, j, CELL_SIZE);
			grid.push_back(newCell);
			gridCopy.push_back(newCell);
		}
	}
	isRunning = false;
}
Game::~Game() { }

void Game::run()
{
	startingShape();

	elapsedActivated = clockActivating.getElapsedTime();
	while (window.isOpen())
	{
		window.clear();
		elapsedActivated = clockActivating.getElapsedTime();
		elapsedStart = clockStart.getElapsedTime();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.mouseButton.button == Mouse::Left && !isRunning)
			{
				int xCell = event.mouseButton.x / CELL_SIZE;
				int yCell = event.mouseButton.y / CELL_SIZE;
				grid[xCell * ROWS + yCell].update(window, clockActivating, elapsedActivated);
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					if (elapsedStart.asSeconds() >= 1)
					{
						isRunning = !isRunning;
						clockStart.restart();
					}
				}
				if (event.key.code == Keyboard::R)
				{
					isRunning = false;
					for (int i = 0; i < grid.size(); i++)
					{
						grid[i].die();
					}
				}
			}
		}
		if (isRunning)
		{
			copyVector(grid, gridCopy);
			for (int i = 0; i < grid.size(); i++)
			{
				int livingN = getLivingNeighbors(grid[i].getX(), grid[i].getY());
				if (livingN < 2 || livingN > 3)
				{
					gridCopy[i].die();
				}
				else if (livingN == 3)
				{
					gridCopy[i].born();
				}
			}
			copyVector(gridCopy, grid);
		}
		for (int i = 0; i < grid.size(); i++)
		{
			grid[i].draw(window);
		}
		window.display();
	}
}

int Game::getLivingNeighbors(int x, int y)
{
	int livingNighbors = 0;
	if (x >0 && y > 0 && grid[(x - 1) * ROWS + (y - 1)].isAlive())
	{
		livingNighbors++;
	}
	if (y > 0 && grid[x * ROWS + (y - 1)].isAlive())
	{
		livingNighbors++;
	}
	if (x < GRID_SIZE - 1 && y > 0 && grid[(x + 1) * ROWS + (y - 1)].isAlive())
	{
		livingNighbors++;
	}
	if (x > 0 && grid[(x - 1) * ROWS + y].isAlive())
	{
		livingNighbors++;
	}
	if (x < GRID_SIZE - 1 && grid[(x + 1) * ROWS + y].isAlive())
	{
		livingNighbors++;
	}
	if (x > 0 && y < GRID_SIZE - 1 && grid[(x - 1) * ROWS + (y + 1)].isAlive())
	{
		livingNighbors++;
	}
	if (y < GRID_SIZE - 1 && grid[x * ROWS + (y + 1)].isAlive())
	{
		livingNighbors++;
	}
	if (x < GRID_SIZE - 1 && y < GRID_SIZE - 1 && grid[(x + 1) * ROWS + (y + 1)].isAlive())
	{
		livingNighbors++;
	}
	return livingNighbors;
}

void Game::startingShape() {
	grid[2400].born();
	grid[2401].born();
	grid[2399].born();
	grid[2330].born();
	grid[2469].born();
}