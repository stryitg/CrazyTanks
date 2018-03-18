#include "stdafx.h"
#include "Tank.h"


Tank::Tank()
{
	this->direction = 1;
	this->tMove = clock();
	this->tShot = clock();
}


Tank::~Tank()
{
}

void Tank::move(int xMove, int yMove)
{
	this->xPos += xMove;
	this->yPos += yMove;
}

void Tank::changePosition(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}
