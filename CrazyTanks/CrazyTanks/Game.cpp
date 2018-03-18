#include "stdafx.h"
#include "Game.h"

//checks if there are enemy tanks near;
bool isNear(const std::list<Enemy>& enemies, int xPos, int yPos)
{
	for (std::list<Enemy>::const_iterator iter = enemies.begin(); iter != enemies.end(); iter++)
	{
		if (std::abs(iter->getPositionX() - xPos) + std::abs(iter->getPositionY() - yPos) <= 2)
		{
			return true;
		}
	}
	return false;
}

Game::Game()
{
	this->playing = true;
	int xPos = this->map.getMapSizeX() / 2;
	int yPos = this->map.getMapSizeY() - 2;
	this->player.changePosition(xPos, yPos);
	map.changeMap('P', xPos,yPos);
	//adding 3 tanks at random positions
	for (int i = 0; i < 3; i++) 
	{
		addEnemy();
	}
}


void Game::playerMove(int xMove, int yMove, double dt)
{
	if (double(clock() - player.getMoveT())/CLOCKS_PER_SEC > dt)
	{
		player.changeMoveT(clock());
		char newPosition = map.getMap(player.getPositionX() + xMove, player.getPositionY() + yMove);
		if (newPosition == ' ')
		{
			map.changeMap(' ', player.getPositionX(), player.getPositionY());
			player.move(xMove, yMove);
			if (player.getVisible())
			{
				map.changeMap('P', player.getPositionX(), player.getPositionY());
			}
		}
		if (newPosition == '#')
		{
			if (!player.getUntouchable())
			{
				player.changeHP(-1);
				player.changeUntouchable(true);
			}
		}
		if (newPosition == 'N')
		{
			if (!player.getUntouchable())
			{
				player.changeHP(-1);
				player.changeUntouchable(true);
				map.changeMap(' ', player.getPositionX(), player.getPositionY());
				player.move(xMove, yMove);
				map.changeMap('P', player.getPositionX(), player.getPositionY());
				destroyEnemy(player.getPositionX(), player.getPositionY());
			}
		}
	}
}

void Game::changePlayerVisible(bool visible)
{
	this->player.changeVisible(visible);
	if (visible)
	{
		map.changeMap('P', player.getPositionX(), player.getPositionY());
	}
	else
	{
		map.changeMap(' ', player.getPositionX(), player.getPositionY());
	}
}

void Game::destroyEnemy(int xPos, int yPos)
{
	std::list<Enemy>::iterator iter = enemies.begin();
	while ((iter != enemies.end() && ((iter->getPositionX() != xPos) || (iter->getPositionY() != yPos)) ))
	{
		++iter;
	}
	enemies.erase(iter);
	--enemyCounter;
	score += 5;
}

void Game::addEnemy()
{
	Enemy newEnemy;
	int tankPositionX;
	int tankPositionY;
	do
	{
		tankPositionX = rand() % this->map.getMapSizeX();
		tankPositionY = rand() % this->map.getMapSizeY();
	} while (isNear(enemies, tankPositionX, tankPositionY) || map.getMap(tankPositionX, tankPositionY) != ' ');
	newEnemy.changePosition(tankPositionX, tankPositionY);
	this->enemies.push_back(newEnemy);
	map.changeMap('N', tankPositionX, tankPositionY);
	++enemyCounter;
}

void Game::addPlayerBullet()
{
	if (double(clock() - player.getShotT()) / CLOCKS_PER_SEC > 0.1)
	{
		player.changeShotT(clock());
		Bullet newBullet(player.getPositionX(), player.getPositionY(), player.getDirection());
		playerBullets.push_back(newBullet);
	}
}

void Game::movePlayerBullet()
{
	std::list<Bullet>::iterator iter = playerBullets.begin();
	while (iter != playerBullets.end())
	{
		if (iter->getDirection() % 2 == 1)
		{
			if (double(clock() - iter->getFlyT()) / CLOCKS_PER_SEC > 0.01)
			{
				iter->changeFlyT(clock());
				if (map.getMap(iter->getPositionX(), iter->getPositionY()) != 'P')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
				}
				iter->move();
				char newPosition = map.getMap(iter->getPositionX(), iter->getPositionY());
				if (newPosition == ' ')
				{
					map.changeMap('|', iter->getPositionX(), iter->getPositionY());
					iter++;
				}
				else if (newPosition == 'N')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
					destroyEnemy(iter->getPositionX(), iter->getPositionY());
					playerBullets.erase(iter++);
				}
				else
				{
					playerBullets.erase(iter++);
				}
			}
		}
		else
		{
			if (double(clock() - iter->getFlyT()) / CLOCKS_PER_SEC > 0.005)
			{
				iter->changeFlyT(clock());
				if (map.getMap(iter->getPositionX(), iter->getPositionY()) != 'P')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
				}
				iter->move();
				char newPosition = map.getMap(iter->getPositionX(), iter->getPositionY());
				if (newPosition == ' ')
				{
					map.changeMap('-', iter->getPositionX(), iter->getPositionY());
					iter++;
				}
				else if (newPosition == 'N')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
					destroyEnemy(iter->getPositionX(), iter->getPositionY());
					playerBullets.erase(iter++);
				}
				else
				{
					playerBullets.erase(iter++);
				}
			}
		}
	}
}

void Game::addEnemyBullet(Enemy& enemy)
{
	if (double(clock() - enemy.getShotT()) / CLOCKS_PER_SEC > 1)
	{
		enemy.changeShotT(clock());
		Bullet newBullet(enemy.getPositionX(), enemy.getPositionY(), enemy.getDirection());
		enemyBullets.push_back(newBullet);
	}
}

void Game::moveEnemyBullet()
{
	std::list<Bullet>::iterator iter = enemyBullets.begin();
	while (iter != enemyBullets.end())
	{
		if (iter->getDirection() % 2 == 1)
		{
			if (double(clock() - iter->getFlyT()) / CLOCKS_PER_SEC > 0.04)
			{
				iter->changeFlyT(clock());
				char position = map.getMap(iter->getPositionX(), iter->getPositionY());
				if ((position != 'P') && position != 'N')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
				}
				iter->move();
				position = map.getMap(iter->getPositionX(), iter->getPositionY());
				if (position == ' ')
				{
					map.changeMap('|', iter->getPositionX(), iter->getPositionY());
					iter++;
				}
				else if (position == 'P')
				{
					player.changeHP(-1);
					player.changeUntouchable(true);
					enemyBullets.erase(iter++);
				}
				else
				{
					enemyBullets.erase(iter++);
				}
			}
		}
		else
		{
			if (double(clock() - iter->getFlyT()) / CLOCKS_PER_SEC > 0.02)
			{
				iter->changeFlyT(clock());
				char position = map.getMap(iter->getPositionX(), iter->getPositionY());
				if ((position != 'P') && position != 'N')
				{
					map.changeMap(' ', iter->getPositionX(), iter->getPositionY());
				}
				iter->move();
				position = map.getMap(iter->getPositionX(), iter->getPositionY());
				if (position == ' ')
				{
					map.changeMap('-', iter->getPositionX(), iter->getPositionY());
					iter++;
				}
				else if (position == 'P')
				{
					player.changeHP(-1);
					player.changeUntouchable(true);
					enemyBullets.erase(iter++);
				}
				else
				{
					enemyBullets.erase(iter++);
				}
			}
		}
	}
}

void Game::moveEnemy(Enemy& enemy,int xMove,int yMove,double dt)
{
	if (double(clock() - enemy.getMoveT()) / CLOCKS_PER_SEC > dt)
	{
		enemy.changeMoveT(clock());
		char newPosition = map.getMap(enemy.getPositionX() + xMove, enemy.getPositionY() + yMove);
		if (newPosition == ' ')
		{
			map.changeMap(' ', enemy.getPositionX(), enemy.getPositionY());
			enemy.move(xMove, yMove);
			map.changeMap('N', enemy.getPositionX(), enemy.getPositionY());
		}
		if (newPosition == 'P')
		{
			if (!player.getUntouchable())
			{
				player.changeHP(-1);
				player.changeUntouchable(true);
			}
			map.changeMap(' ', enemy.getPositionX(), enemy.getPositionY());
			destroyEnemy(enemy.getPositionX(), enemy.getPositionY());
		}
	}
}

void Game::moveEnemy()
{
	std::list<Enemy>::iterator iter = enemies.begin();
	while (iter != enemies.end())
	{
		// horizontal movement
		if (std::abs(iter->getPositionX() - player.getPositionX()) >= std::abs(iter->getPositionY() - player.getPositionY()))
		{
			if (iter->getPositionX() > player.getPositionX()) // moving  left
			{
				char nextPos = map.getMap(iter->getPositionX() - 1, iter->getPositionY());
				if (nextPos == ' ' || nextPos == 'P') // can move
				{
					if (nextPos == 'P')
					{
						moveEnemy(*iter++, -1, 0, 0.4);
						break; // kinda solves problem with next node being lost after destruction of the tank 
					}
					moveEnemy(*iter, -1, 0, 0.4);
					iter->changeDirection(2);
				}
				else //cant move
				{
					if (map.getMap(iter->getPositionX(), iter->getPositionY() - 1) == ' ')
					{
						moveEnemy(*iter, 0, -1, 0.4);
						iter->changeDirection(1);
					}
					else 
					{
						moveEnemy(*iter, 0, 1, 0.4);
						iter->changeDirection(3);
					}
				}
			}
			// moving right
			else if (iter->getPositionX() < player.getPositionX())
			{
				char nextPos = map.getMap(iter->getPositionX() + 1, iter->getPositionY());
				//can move
				if (nextPos == ' ' || nextPos == 'P')
				{
					if (nextPos == 'P')
					{
						moveEnemy(*iter++, 1, 0, 0.4);
						break;
					}
					moveEnemy(*iter, +1, 0, 0.4);
					iter->changeDirection(4);
				}
				//cant move
				else
				{
					if (map.getMap(iter->getPositionX(), iter->getPositionY() -1 ) == ' ')
					{
						moveEnemy(*iter, 0, -1, 0.4);
						iter->changeDirection(1);
					}
					else 
					{
						moveEnemy(*iter, 0, 1, 0.4);
						iter->changeDirection(3);
					}
				}
			}
		}
		else // vertical movement
		{
			if (iter->getPositionY() > player.getPositionY()) //moving up
			{
				char nextPos = map.getMap(iter->getPositionX(), iter->getPositionY() - 1);
				if (nextPos == ' ' || nextPos == 'P') //can move
				{
					if (nextPos == 'P')
					{
						moveEnemy(*iter++, 0, -1, 0.4);
						break;
					}
					moveEnemy(*iter, 0, -1, 0.4);
					iter->changeDirection(1);
				}	
				else //cant
				{
					if (map.getMap(iter->getPositionX() - 1, iter->getPositionY()) == ' ')
					{
						moveEnemy(*iter, -1, 0, 0.4);
						iter->changeDirection(2);
					}
					else 				
					{
						moveEnemy(*iter, 1, 0, 0.4);
						iter->changeDirection(4);
					}
				}
			}
			else if (iter->getPositionY() < player.getPositionY()) //moving down
			{
				char nextPos = map.getMap(iter->getPositionX(), iter->getPositionY() + 1);
				if (nextPos == ' ' || nextPos == 'P') //can move
				{
					if (nextPos == 'P')
					{
						moveEnemy(*iter++, 0, +1, 0.4);
						break;
					}
					moveEnemy(*iter, 0, +1, 0.4);
					iter->changeDirection(3);
				}
				else // cant
				{
					if (map.getMap(iter->getPositionX()-1, iter->getPositionY()) == ' ')
					{
						moveEnemy(*iter, -1, 0, 0.4);
						iter->changeDirection(2);
					}
					else
					{
						moveEnemy(*iter, 1, 0, 0.4);
						iter->changeDirection(4);
					}
				}
			}
		}
		++iter;
	}
}

void Game::enemyShot()
{
	std::list<Enemy>::iterator iter = enemies.begin();
	while (iter != enemies.end())
	{
		if (cShot(*iter))
		{
			addEnemyBullet(*iter);
		}
		++iter;
	}
}

void Game::mainMenu()
{
	std::cout << "MAIN MENU" << std::endl;
	std::cout << "1. Play"  << std::endl;
	std::cout << "2. Quit" << std::endl;
	std::cin >> menuChoise;
	switch (menuChoise)
	{
		case 1:
			this->playing = true;
			break;
		case 2:
			this->playing = false;
		default:
			this->playing = false;
			break;
	}
}

bool Game::cShot(const Enemy & enemy)
{
	switch (enemy.getDirection())
	{
		case 1:
			if (player.getPositionY() < enemy.getPositionY())
			{
				return true;
			}
			return false;
			break;
		case 2:
			if (player.getPositionX() < enemy.getPositionX())
			{
				return true;
			}
			return false;
			break;
		case 3:
			if (player.getPositionY() > enemy.getPositionY())
			{
				return true;
			}
			return false;
			break;
		case 4:
			if (player.getPositionX() > enemy.getPositionX())
			{
				return true;
			}
			return false;
			break;
		default:
			return true;
			break;
	}
}





Game::~Game()
{
}
