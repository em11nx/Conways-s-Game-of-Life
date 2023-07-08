#include "Cell.h"
#include <iostream>

Cell::~Cell() { }

Cell::Cell(int _x, int _y, int _cellSize)
{
	alive = false;
	x = _x;
	y = _y;
	cellSize = _cellSize;
	shape.setFillColor(Color::Black);
	shape.setOutlineColor(Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setSize(Vector2f(cellSize, cellSize));
}

bool Cell::isAlive()
{
	return alive;
}
int Cell::getX()
{
	return x;
}
int Cell::getY()
{
	return y;
}
void Cell::draw(RenderWindow& window)
{
	shape.setPosition(x*cellSize, y*cellSize);
	window.draw(shape);
}
void Cell::setPostion(Vector2f pos)
{
	shape.setPosition(pos);
}
void Cell::die()
{
	alive = false;
	shape.setFillColor(Color::Black);
}
void Cell::born()
{
	alive = true;
	shape.setFillColor(Color::Blue);
}
void Cell::update(RenderWindow& window, Clock& clockActivating, Time& elapsedActiveated)
{
	if (elapsedActiveated.asSeconds() >= 0.2f)
	{
		clockActivating.restart();
		if (alive)
		{
			die();
		}
		else
		{
			born();
		}
	}
}