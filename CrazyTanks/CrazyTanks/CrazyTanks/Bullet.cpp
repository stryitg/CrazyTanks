#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	this->direction = 1;
	this->tFly = clock();
}

Bullet::Bullet(int xPos, int yPos, int direction)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->direction = direction;
	this->tFly = clock();
}


Bullet::~Bullet()
{
}

#include<iostream>
void Bullet::move()
{
	switch (this->direction)
	{
		case 1:
			yPos -= 1;
			break;
		case 2:
			xPos -= 1;
			break;
		case 3:
			yPos += 1;
			break;
		case 4:
			xPos += 1;
			break;
		default:
			break;
	}
}
