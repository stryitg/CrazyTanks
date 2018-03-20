#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	Tank::Tank();
	this->hp = 3;
	this->untouchable = false;
	this->visible = true;
}


Player::~Player()
{
}


