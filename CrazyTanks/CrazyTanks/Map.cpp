#include "stdafx.h"
#include "Map.h"



Map::Map()
{
	//empty field creation
	this->map = std::vector<std::string>(2, std::string(mapSizeX, '_')); // upper and lower bounderies creation
	this->map[1][0] = '|';
	this->map[1][mapSizeX - 1] = '|';
	std::string horizontalBorder(mapSizeX, ' ');
	horizontalBorder[0] = '|';
	horizontalBorder[mapSizeX - 1] = '|';
	std::vector<std::string> horizontalBorderS(mapSizeY-2 , horizontalBorder); // right and left bounderies creation
	this->map.insert(this->map.begin()+1, horizontalBorderS.begin(), horizontalBorderS.end());
	//adding random baricades
	for (std::size_t i = 1; i < mapSizeY-1; i++)
	{
		for (std::size_t j = 1; j < mapSizeX-2; j++)
		{
			if ((i - mapSizeY + 2)*(i-mapSizeY + 2) + (j - mapSizeX / 2)*(j-mapSizeX / 2) > 4) // not allowing baricades near player spawn
			{ 
				int random = rand() % 200;
				switch (random)
				{
					case 0:
						if (j == mapSizeX - 2)
						{
							addWall(j, i);
							addWall(j-1, i);
							addWall(j-2, i);
						}
						if (j == 1)
						{
							addWall(j, i);
							addWall(j + 1, i);
							addWall(j + 2, i);

						}
						if (j != 1 && j != mapSizeX - 2)
						{
							addWall(j - 1, i);
							addWall(j, i);
							addWall(j + 1, i);
						}
						break;
					case 1:
						if (i == mapSizeY - 2)
						{
							addWall(j, i);
							addWall(j, i - 1);
							addWall(j, i - 2);
						}
						if (i == 1)
						{
							addWall(j, i);
							addWall(j, i + 1);
							addWall(j, i + 2);

						}
						if (i != 1 && i != mapSizeY - 2)
						{
							addWall(j, i - 1);
							addWall(j, i);
							addWall(j, i + 1);
						}
						
						break;
					default:
						break;
				}
			}
		}
	}
	// adding gold and fortress
	map[mapSizeY - 2][1] = 'G';
	addWall(1, mapSizeY - 3);
	addWall(2, mapSizeY - 3);
	addWall(2, mapSizeY - 2);
}


void Map::addWall(int xPos, int yPos)
{
	map[yPos][xPos] = '#';
	walls[std::pair<int, int>(xPos,yPos)] = Wall(xPos, yPos);
}

void Map::destroyWall(int xPos, int yPos)
{
	map[yPos][xPos] = ' ';
	walls.erase(std::pair<int, int>(xPos, yPos));
}

void Map::displayMap() const
{
	for (std::vector<std::string>::const_iterator iter1 = map.begin(); iter1 != map.end(); iter1++)
	{
		std::cout << *iter1 << std::endl;
	}
}

Map & Map::operator=(const Map & map)
{
	this->map = map.map;
	return *this;
}

Map::~Map()
{
}


