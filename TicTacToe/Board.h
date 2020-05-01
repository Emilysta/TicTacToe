#pragma once

enum class What{cross='X',circle='O',none='_'};
enum class Who{player1=1, player2=2, none =10};
class Board{
	int size;
	What* board; //tablica znakow 'X', 'O'
	Who whoseMove; //czyj ruch w obecnej kolejce
	int lastMove;
	int* firstDiagonal; //indeksy elementów pierwszej z przekatnych
	int* secondDiagonal; //indeksy elementów drugiej z przekatnych
	friend class Player;
	friend class Game;
public: 
	Board();
	Board(int newSize);
	~Board();
	bool checkVertical(int i_column);
	bool checkHorizontal(int i_row);
	bool checkFirstDiagonal();
	bool checkSecondDiagonal();
	bool isEnd(int index);
	void show();
};

