#include "Game.h"
#include <iostream>

Game::Game() {
	player_1 = nullptr;
	player_2 = nullptr;
	gameBoard = nullptr;
	sizeOfBoard = 0;
}

Game::Game(int size,int inLine,Who start) {
	player_1 = new Player(What::cross, Who::player1, true); //stworzenie graczy
	player_2 = new Player(What::circle, Who::player2,false); 
	sizeOfBoard = size;
	gameBoard = new Board(size,inLine,start);	//utworzenie planszy
}

bool Game::playerMove(int move) { //ruch gracza
	int row = move / sizeOfBoard;
	int column = move % sizeOfBoard;
	return player_1->choseMove(gameBoard,row,column);
}

bool Game::computerMove(int& move) { //ruch komputera
	return player_2->choseMove(gameBoard, move);
}

void Game::show() { //wyswietlenie planszy
	gameBoard->show();
}

int Game::getSize() { //zwrocenie rozmiary=u planszy
	return sizeOfBoard;
}

char Game::getP1() { //zwrocenie znaku,którym gra gracz 1
	return (char)(player_1->getWhatChar());
}

char Game::getP2() { //zwrocenie znaku,którym gra gracz 2
	return (char)(player_2->getWhatChar());
}

bool Game::isEnd() { //informacji, czy jest koniec gry, poniewaz jest brak pól
	return !gameBoard->isMoveLeft();
}

Who Game::whoseMove() {
	return gameBoard->getWhoseMove();
}



