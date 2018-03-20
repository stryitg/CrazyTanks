#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player : Tank
{
public:
	Player();
	~Player();

	//Accessors

	inline int getPositionX() const { return Tank::getPositionX(); };
	inline int getPositionY() const { return Tank::getPositionY(); };
	inline const int& getHp() const { return this->hp; };
	inline const int& getUntouchable() const { return this->untouchable; };
	inline const int& getDirection() const { return Tank::getDirection(); };
	inline bool getVisible() const { return this->visible; };
	inline int getHP() const { return this->hp; };
	inline clock_t getMoveT() const { return Tank::getMoveT(); };
	inline clock_t getShotT() const { return Tank::getShotT(); };

	//Modifiers

	inline void move(int xMove, int yMove) { Tank::move(xMove, yMove); };
	inline void changePosition(int xPos, int yPos) { Tank::changePosition(xPos, yPos); };
	inline void changeHP(int HP) { this->hp += HP; };
	inline void changeUntouchable(bool is) { this->untouchable = is; };
	inline void changeDirection(int direction) { Tank::changeDirection(direction); };
	inline void changeVisible(bool visible) { this->visible = visible; };
	inline void changeMoveT(clock_t time) { Tank::changeMoveT(time); };
	inline void changeShotT(clock_t time) { Tank::changeShotT(time); };

	//Overloading



private:
	int xPos;
	int yPos;

	int hp;
	bool untouchable;
	bool visible;
	int direction;

	clock_t tMove; // handles move speed;
	clock_t tShot; // handles time to reload
};

#endif

