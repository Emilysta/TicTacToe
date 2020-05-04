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
	void setWhatChar(What newWhatChar);
	What& getWhatChar();
	bool choseMove(Board* _board);
	int searchForOption(Board _board,Who player);
	int algorithmAlfaBeta(Board _board,int maxdepth, int _alpha, int _beta);
	int alpha(Board _board, int maxdepth, int _alpha, int _beta, int& index);
	int beta(Board _board, int maxdepth, int _alpha, int _beta, int& index);

};

