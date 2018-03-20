#include "stdafx.h"
#include "Wall.h"


Wall::Wall()
{
	this->hp = 3;
}

Wall::Wall(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->hp = 3;
}


Wall::~Wall()
{
}
