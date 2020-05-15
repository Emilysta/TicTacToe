#pragma once

enum class What{cross='X',circle='O',none='_'};
enum class Who{player1=1, player2=2, none =10};
class Board{
	int size;
	What** board; //tablica znakow 'X', 'O' n x n
	Who whoseMove; //czyj ruch w obecnej kolejce
	int countOfMovesToEnd; //liczba ruchów do koñca
	friend class Player; // zaprzyjaŸnienie klasy gracza z plansza
	int  howManyInLine; //iloœæ znaków w linii
public: 
	Board();
	Board(const Board& boardToCopy);
	Board(int newSize, int inLine, Who start);
	~Board();
	/* Wszystkie funkcje sprawdzaj¹ce zwracaj¹ wartoœæ 10 dla wygranej podanego do funkcji znaku, 
	-10 dla wygranej znaku przeciwnika, 0 w przypadku braku jakiejkolwiek wygranej*/
	int checkVertical(int i_column,What sign);
	int checkHorizontal(int i_row, What sign);
	int checkFirstDiagonal(What sign);
	int checkSecondDiagonal(What sign);
	int checkDiagonals(int i, int j,What sign);
	int isEnd(int row,int column, What sign);//wykorzystuje funkcje sprawdzaj¹ce 
	void show();
	bool isMoveLeft(); //true -  gdy s¹ jakieœ ruchy, false - gdy ich nie ma
	Who getWhoseMove(); 
};

