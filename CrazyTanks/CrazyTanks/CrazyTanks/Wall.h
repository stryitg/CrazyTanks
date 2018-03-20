#ifndef WALL_H
#define WALL_H


class Wall
{
public:
	Wall();
	Wall(int xPos, int yPos);
	~Wall();

	//Accessors
	
	inline const int&  getHP() const { return this->hp; };
	
	//Modifiers

	inline void changeHp(int hp) { this->hp += hp; };

private:
	int xPos;
	int yPos;
	
	int hp;
};

#endif

