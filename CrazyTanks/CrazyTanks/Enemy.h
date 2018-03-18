#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"



class Enemy : Tank
{
public:
	Enemy();
	~Enemy();

	// Accessors
	inline int getPositionX() const { return Tank::getPositionX(); };
	inline int getPositionY() const { return Tank::getPositionY(); };
	inline const int& getDirection() const { return Tank::getDirection(); };
	inline clock_t getMoveT() const { return Tank::getMoveT(); };
	inline clock_t getShotT() const { return Tank::getShotT(); };


	//Modifiers
	inline void move(int xMove, int yMove) { Tank::move(xMove, yMove); };
	inline void changePosition(int xPos, int yPos) { Tank::changePosition(xPos, yPos); };
	inline void changeDirection(int direction) { Tank::changeDirection(direction); };
	inline void changeMoveT(clock_t time) { Tank::changeMoveT(time); };
	inline void changeShotT(clock_t time) { Tank::changeShotT(time); };


	//Overloading

private:
	int xPos;
	int yPos;

	int direction;

	clock_t tMove; // handles move speed;
	clock_t tShot; // handles time to reload
};

#endif
