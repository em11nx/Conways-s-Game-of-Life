#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Cell
{
public:
	Cell(int _x, int _y, int _cellSize);
	~Cell();
	bool isAlive();
	void born();
	void die();

	void draw(RenderWindow& window);
	void setPostion(Vector2f pos);
	int getX();
	int getY();

	void update(RenderWindow& window, Clock& clockActivating, Time& elapsedActiveated);

private:
	bool alive;
	int cellSize;
	int x;
	int y;
	RectangleShape shape;
};