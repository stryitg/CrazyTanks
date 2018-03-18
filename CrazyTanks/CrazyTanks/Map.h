#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>


class Map
{
public:
	Map();
	~Map();

	// Accessors

	inline const char& getMap(int xPos, int yPos) const { return this->map[yPos][xPos]; };
	inline int getMapSizeX() const { return this->mapSizeX; };
	inline int getMapSizeY() const { return this->mapSizeY; };


	//Modifiers

	inline void changeMap(char symbol, int xPos, int yPos) { this->map[yPos][xPos] = symbol; };

	//Functions

	void displayMap() const;

	//Overloading

	Map& operator= (const Map& map);
	

private:
	std::vector<std::string> map;
	const int mapSizeX = 60;
	const int mapSizeY = 20;
};

#endif
