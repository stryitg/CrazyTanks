#ifndef TANK_H
#define TANK_H

#include <time.h>

class Tank
{
public:
	Tank();
	~Tank();

	
	// Accessors

	inline int getPositionX() const { return this->xPos; };
	inline int getPositionY() const { return this->yPos; };
	inline const int& getDirection() const { return this->direction; };
	inline clock_t getMoveT() const { return this->tMove; };
	inline clock_t getShotT() const { return this->tShot; };


	//Modifiers

	void move(int xMove, int yMove);
	void changePosition(int xPos, int yPos);
	inline void changeDirection(int direction) { this->direction = direction; };
	inline void changeMoveT(clock_t time) { this->tMove = time; };
	inline void changeShotT(clock_t time) { this->tShot = time; };


private:
	int xPos;
	int yPos;

	int direction;

	clock_t tMove; // handles move speed;
	clock_t tShot; // handles time to reload  
};


#endif
