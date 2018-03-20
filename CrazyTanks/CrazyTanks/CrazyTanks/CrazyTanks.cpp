// CrazyTanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <Windows.h>


void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}

void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void move(Game& game)
{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			game.playerMove(0, -1,0.06);
			game.changePlayerDirection(1);
			return;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			game.playerMove(0, 1, 0.06);
			game.changePlayerDirection(3);
			return;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			game.playerMove(-1, 0, 0.03);
			game.changePlayerDirection(2);
			return;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			game.playerMove(1, 0, 0.03);
			game.changePlayerDirection(4);
			return;
		}
}

void blink(Game& game,int& blinkCounter, clock_t& tPrev)
{
	if (game.getPlayerUntouchable())
	{
		if (blinkCounter < 4)
		{
			if (double(clock() - tPrev) / CLOCKS_PER_SEC > 0.3)
			{
				tPrev = clock();
				++blinkCounter;
				game.changePlayerVisible(!game.getPlayerVisible());
			}
		}
		else
		{
			game.changePlayerUntouchable(false);
			blinkCounter = 0;
		}
	}
}

void gameOver(Game& game, int& blinkCounter, clock_t& tAddEnemy,clock_t& tBlink)
{
	if (game.getPlayerHp() <= 0)
	{
		system("cls");
		std::cout << "Game over" << std::endl;
		std::cout << "Your score is " << game.getScore() << std::endl;
		game.mainMenu();
		if (game.getPlaying())
		{
			Game newGame;
			game = newGame;
		}
		blinkCounter = 0;
		tAddEnemy = clock(); 
		tBlink = clock();
		system("cls");
	}
}

void addEnemy(Game& game, clock_t& tPrev)
{
	if (game.getEnemyCounter() == 0)
	{
		game.addEnemy();
	}
	else if (game.getEnemyCounter() < 5)
	{
		if (double(clock() - tPrev) / CLOCKS_PER_SEC > 10)
		{
			game.addEnemy();
			tPrev = clock();
		}
	}
}


void shot(Game& game)
{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			game.addPlayerBullet();
		}
}



int main()
{
	srand(time(NULL));

	Game CrazyTanks;
	CrazyTanks.mainMenu();
	// time counters for different events
	clock_t tBlink = clock();
	clock_t tShoot = clock();
	clock_t tAddEnemy = clock();
	int blinkCounter = 0;
	while (CrazyTanks.getPlaying())
	{
		gotoxy(0, 0);
		move(CrazyTanks);
		blink(CrazyTanks,blinkCounter,tBlink); // makes player's tank blink after taking damage
		gameOver(CrazyTanks,blinkCounter,tAddEnemy,tBlink); // handles end of the game
		CrazyTanks.movePlayerBullet();
		addEnemy(CrazyTanks, tAddEnemy);
		shot(CrazyTanks); // handles player's shots
		CrazyTanks.enemyShot();
		CrazyTanks.moveEnemyBullet();
		CrazyTanks.moveEnemy();
		CrazyTanks.displayMap();
		std::cout << "HP " << CrazyTanks.getPlayerHp() << " Score " << CrazyTanks.getScore() << std::endl;
	}
	system("cls");
	system("pause");
    return 0;
}

