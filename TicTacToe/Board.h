#pragma once

enum class What{cross='X',circle='O',none='_'};
enum class Who{player1=1, player2=2, none =10};
class Board{
	int size;
	What** board; //tablica znakow 'X', 'O' n x n
	Who whoseMove; //czyj ruch w obecnej kolejce
	int countOfMovesToEnd;
	Who winner;
	friend class Player;
	int  howManyInLine;
public: 
	Board();
	Board(const Board& boardToCopy);
	Board(int newSize, int inLine, Who start);
	~Board();
	int checkVertical(int i_column,What sign);
	int checkHorizontal(int i_row, What sign);
	int checkFirstDiagonal(What sign);
	int checkSecondDiagonal(What sign);
	int checkDiagonals(int i, int j,What sign);
	int isEnd(int row,int column, What sign);
	void show();
	bool isMoveLeft();
	Who checkWinner();
	Who getWhoseMove();
};

