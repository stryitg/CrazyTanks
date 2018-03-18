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
							map[i][j] = '#';
							map[i][j - 1] = '#';
							map[i][j - 2] = '#';
						}
						if (j == 1)
						{
							map[i][j] = '#';
							map[i][j + 1] = '#';
							map[i][j + 2] = '#';
						}
						if (j != 1 && i != mapSizeX - 2)
						{
							map[i][j-1] = '#';
							map[i][j] = '#';
							map[i][j + 1] = '#';
						}
						break;
					case 1:
						if (i == mapSizeY - 2)
						{
							map[i][j] = '#';
							map[i-1][j] = '#';
							map[i-2][j] = '#';
						}
						if (i == 1)
						{
							map[i][j] = '#';
							map[i+1][j] = '#';
							map[i+2][j] = '#';
						}
						if (i != 1 && i != mapSizeY - 2)
						{
							map[i-1][j] = '#';
							map[i][j] = '#';
							map[i+1][j] = '#';
						}
						break;
					default:
						break;
				}
			}
		}
	}
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


