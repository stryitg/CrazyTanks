#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>



class Game
{
public:
	Game();
	~Game();

	//Accessors

	inline const bool& getPlaying() const { return this->playing; };
	inline const int& getPlayerPositionX() const { return this->player.getPositionX(); };
	inline const int& getPlayerPositionY() const { return this->player.getPositionY(); };
	inline const int& getPlayerHp() const { return this->player.getHp(); };
	inline const int& getPlayerUntouchable() const { return this->player.getUntouchable(); };
	inline bool getPlayerVisible() const { return this->player.getVisible(); };
	inline const int& getScore() const { return this->score; };
	inline const int& getEnemyCounter() const { return this->enemyCounter; };
	inline const int& getPlayerDirection() const { return this->player.getDirection(); };

	//Modifiers

	inline void changeMap(char symbol, int xPos, int yPos) { this->map.changeMap(symbol, xPos, yPos); };
	void playerMove(int xMove, int yMove,double dt);
	inline void changePlayerUntouchable(bool is) { this->player.changeUntouchable(is); };
	inline void changePlayerDirection(int direction) { this->player.changeDirection(direction);};
	void changePlayerVisible(bool visible);
	void destroyEnemy(int xPos, int yPos);
	void addEnemy();
	void addPlayerBullet();
	void movePlayerBullet();
	void addEnemyBullet(Enemy& enemy);
	void moveEnemyBullet();
	void moveEnemy(Enemy& enemy,int xMove,int yMove,double dt);
	void moveEnemy(); // moves all enemy
	void enemyShot();

	//Functions

	void mainMenu();
	inline void displayMap() const { map.displayMap(); };
	
	//Overloading

private:
	bool playing;
	int menuChoise;
	int enemyCounter;

	Map map;
	Player player;
	std::list<Enemy> enemies;
	std::list<Bullet> playerBullets;
	std::list<Bullet> enemyBullets;

	int score;

	// Functions

	bool cShot(const Enemy& enemy);	// checks if enemy should shoot 
	
};

#endif 

