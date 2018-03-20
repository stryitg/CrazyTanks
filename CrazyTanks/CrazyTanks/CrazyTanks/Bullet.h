#ifndef BULLET_H
#define BULLET_H

#include <time.h>

class Bullet
{
public:
	Bullet();
	Bullet(int xPos, int yPos, int directions);
	~Bullet();

	//Accessors

	inline int getPositionX() const { return this->xPos; };
	inline int getPositionY() const { return this->yPos; };
	inline const int& getDirection() const { return this->direction; };
	inline clock_t getFlyT() const { return this->tFly; };

	//Modifiers

	void move();
	inline void changeFlyT(clock_t time) { this->tFly = time; };

private:
	int xPos;
	int yPos;

	int direction;

	clock_t tFly; // handles bullet speed
};

#endif

