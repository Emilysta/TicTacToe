#include "Game.h"
#include <iostream>

Game::Game() {
	player_1 = nullptr;
	player_2 = nullptr;
	gameBoard = nullptr;
	sizeOfBoard = 0;
}

Game::Game(int size,int inLine) {
	player_1 = new Player(What::cross, Who::player1, false);
	player_2 = new Player(What::circle, Who::player2,false);
	sizeOfBoard = size;
	gameBoard = new Board(size,inLine);
	
}

void Game::startGame() {
	int i = sizeOfBoard * sizeOfBoard;
	gameBoard->show();
	std::cout << "----------------------\n";
	do {
		if (gameBoard->getWhoseMove() == Who::player1){
			if (player_1->choseMove(gameBoard) == true) {
				break;
			}
			gameBoard->show();
		}
		else {
			if (player_2->choseMove(gameBoard) == true) {
				break;
			}
			gameBoard->show();
		}
		i--;
	} while ( i>0);
	gameBoard->show();
	
	std::cout << "Koniec gry"<<std::endl;
}

void Game::show() {
	gameBoard->show();
}