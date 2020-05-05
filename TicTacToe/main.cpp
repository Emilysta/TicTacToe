#include "Game.h"
#include <iostream>

int main() {

	Game* newGame = new Game(3,3);
	newGame->startGame();
	std::cin.ignore();
	return 0;
}