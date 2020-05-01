#pragma once
#include "Board.h"
#include "Player.h"
class Game{
	Player* player_1;
	Player* player_2;
	Board* gameBoard;
	int sizeOfBoard;

public: 
	Game();
	Game(int size);
	~Game() =default;
	void startGame();
	void show();
};

