#pragma once
#include "Board.h"
class Player{
	What whatChar; //jaki znak przynalezy do tego gracza
	Who whatPlayer; //kt�ry gracz, 1 czy 2
	bool isHuman; //czy jest cz�owiekiem
public: 
	Player();
	Player(What newWhatChar,Who newWhatPlayer, bool _ishuman);
	~Player() = default;
	void setWhatChar(What newWhatChar);
	What& getWhatChar();
	bool choseMove(Board* _board);
	int searchForOption(Board _board,Who player,int& row, int& column);
	int minimax(Board _board,int depth,bool isMax);
	What getOpponentChar();
};