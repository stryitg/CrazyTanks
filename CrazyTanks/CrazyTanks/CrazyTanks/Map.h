#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <map>
#include <utility>
#include "Wall.h"


class Map
{
public:
	Map();
	~Map();

	// Accessors

	inline const char& getMap(int xPos, int yPos) const { return this->map[yPos][xPos]; };
	inline int getMapSizeX() const { return this->mapSizeX; };
	inline int getMapSizeY() const { return this->mapSizeY; };
	inline const int& getWallHp(int xPos, int yPos) { return walls[std::pair<int, int>(xPos, yPos)].getHP(); };


	//Modifiers

	inline void changeMap(char symbol, int xPos, int yPos) { this->map[yPos][xPos] = symbol; };
	inline void changeWallHP(int hp, int yPos, int xPos) { walls[std::pair<int, int>(yPos, xPos)].changeHp(hp); };
	void addWall(int xPos, int yPos);
	void destroyWall(int xPos, int yPos);

	//Functions

	void displayMap() const;

	//Overloading

	Map& operator= (const Map& map);
	

private:
	std::vector<std::string> map;
	const int mapSizeX = 60;
	const int mapSizeY = 20;

	std::map<std::pair<int, int>,Wall> walls;
};

#endif
