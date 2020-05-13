#pragma once
#include "Board.h"
class Player{
	What whatChar; //jaki znak przynalezy do tego gracza
	Who whatPlayer; //który gracz, 1 czy 2
	bool isHuman; //czy jest cz³owiekiem
public: 
	Player();
	Player(What newWhatChar,Who newWhatPlayer, bool _ishuman);
	~Player() = default;
	void setWhatChar(What newWhatChar); //ustawia znak
	What& getWhatChar(); //zwraca znak u¿ytkownika
	bool choseMove(Board* _board,int _row,int _column); //ruch uzytkownika 
	bool choseMove(Board* _board,int &move); //ruch komputera
	int searchForOption(Board* _board,Who player,int& row, int& column); //poszukiwanie opcji ruchu dla komputera 
	//jesli rusza sie jako pierwszy to losuje sposrod "naroznikow" planszy
	//jesli jako pierwszy rusza sie uzytkownik to przeszukuje za pomoca algorytmu ciêæ alfa-beta

	int minimax(Board* _board, int i, int j, int depth,bool isMax,int alpha, int beta); //ciecia alfa-beta
	What getOpponentChar(); //zwraca znak przeciwnika
};