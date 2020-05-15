#pragma once
#include "Board.h"
#include "Player.h"
class Game{
	Player* player_1; //gracz nr 1
	Player* player_2; //gracz nr 2
	Board* gameBoard; //plansza
	int sizeOfBoard; //rozmiar planszy

public: 
	Game();
	Game(int size,int inLine, Who start);
	~Game() =default;
	bool playerMove(int move); //ruch gracza
	bool computerMove(int& move); //rych AI
	void show(); //wyswieltanie planszy
	int getSize(); //zwraca rozmiar planszy - jelsi plansza 4x4 to zwraca 4
	char getP1(); //zwraca znak playera 1
	char getP2(); // zwraca znak playera 2
	bool isEnd(); // true jesli nie ma juz ruchów, false jesli s¹ jeszcze jakies ruchy
	Who whoseMove(); //zrraca informacje kogo ruch jest obecnie.
};


