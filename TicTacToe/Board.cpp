#include "Board.h"
#include <iostream>
#include <time.h>

Board::Board() { 
	size = 0;
	board = nullptr;
	whoseMove = Who::none;
	countOfMovesToEnd = 0;
	howManyInLine = 0;
}

Board::Board(const Board& boardToCopy) { //konstruktor kopiuj¹cy - obecnie nie jest wykorzystywany
	size = boardToCopy.size;
	board = new What * [size];
	for (int i = 0; i < size; ++i) {
		board[i] = new What[size];
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; j++) {
			board[i][j] = boardToCopy.board[i][j];
		}
	}
	whoseMove = boardToCopy.whoseMove;
	countOfMovesToEnd = boardToCopy.countOfMovesToEnd;
	howManyInLine = boardToCopy.howManyInLine;
}

Board::Board(int newSize, int inLine,Who start) { 
	srand((unsigned)(time(NULL)));
	size = newSize; //rozmiar np.4
	//utworzenie tablicy o rozmiarze np 4x4 
	board = new What * [size];
	for (int i = 0; i < size; ++i) {
		board[i] = new What[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = What::none;
		}
	}
	whoseMove = start; //kto zaczyna grê
	countOfMovesToEnd = size * size;
	howManyInLine = inLine; //iloœæ znakó w linii potrzebna do wygrania
}

Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete board[i];
	}
	delete[] board;
}

int Board::checkVertical(int i_column, What sign) { //sprawdz w pionie, zwraca wartoœæ 10 dla wygranej podanego do funkcji znaku, 
	//-10 dla wygranej znaku przeciwnika, 0 w przypadku braku jakiejkolwiek wygranej
	What opposite; //wyznacz znak przeciwnika
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) {//i_column indeks sprawdzanej kolumny
		if (board[i][i_column] == sign) { //sprawdzanie kolejnych znaków
			++count1; //sumowanie
			count2 = 0; //zerowanie liczby znaków przeciwnika
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][i_column] == opposite) {//sprawdzanie kolejnych znaków
			++count2; //sumowanie
			count1 = 0; //zerowanie liczby znaków przeciwnika
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else { //jesli pole jest puste
			count1 = 0; //wyzeruj oba liczniki
			count2 = 0;
		}
	}
	return 0;
}

int Board::checkHorizontal(int i_row, What sign) { //sprawdz w poziomie, zwraca wartoœæ 10 dla wygranej podanego do funkcji znaku, 
	//-10 dla wygranej znaku przeciwnika, 0 w przypadku braku jakiejkolwiek wygranej
	What opposite; //wyznacz znak przeciwnika
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //i_row indeks sprawdzanego rzedu 
		if (board[i_row][i] == sign) {//sprawdzanie kolejnych znaków
			++count1;//sumowanie
			count2 = 0;//zerowanie liczby znaków przeciwnika
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i_row][i] == opposite) {//sprawdzanie kolejnych znaków
			++count2;//sumowanie
			count1 = 0;//zerowanie liczby znaków przeciwnika
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {//jesli pole jest puste
			count1 = 0;//wyzeruj oba liczniki
			count2 = 0;
		}
	}
	return 0;
}

int Board::checkDiagonals(int i, int j, What sign) {//zwraca wartoœæ 10 dla wygranej podanego do funkcji znaku, 
	//-10 dla wygranej znaku przeciwnika, 0 w przypadku braku jakiejkolwiek wygranej
	What opposite; //wyznacz znak przeciwnika
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	} 
	int k = size - j - 1;
	int row = 0;
	int column = 0;
	int count1 = 0;
	int count2 = 0;
	/* sprawdzanie po ukosie / */
	if (i <= k ) { //jezeli znajdujemy sie w gornym trojkacie
		row = i + j;//ustawienie indeksów poczatku przek¹tnej
		column = 0;
		if (row + 1 >= howManyInLine) { //sprawdzenie czy na danej przekatnej moze zmiescic sie tyle znakow ile potrzeba do wygranej
			do {
				if (board[row][column] == sign) {//sprawdzanie kolejnych znaków
					++count1;//sumowanie
					count2 = 0;//zerowanie liczby znaków przeciwnika
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {//sprawdzanie kolejnych znaków
					++count2;//sumowanie
					count1 = 0;//zerowanie liczby znaków przeciwnika
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {//jesli pole jest puste
					count1 = 0;//wyzeruj oba liczniki
					count2 = 0;
				}
				++column;
				--row;
			} while (row >= 0); //wykonanie sprawdzenia dopóki nie znajdzeimy sie na drugim koñcu
		}
	}
	else { //jezeli w dolnym
		row = size - 1; //ustawienie indeksów poczatku przek¹tnej
		column = j - (size - 1 - i); 
		if (column<= size - howManyInLine) {//sprawdzenie, czy na danej przekatnej moze zmiescic sie tyle znakow ile potrzeba do wygranej
			do {
				if (board[row][column] == sign) {//sprawdzanie kolejnych znaków
					++count1;//sumowanie
					count2 = 0;//zerowanie liczby znaków przeciwnika
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {//sprawdzanie kolejnych znaków
					++count2;//sumowanie
					count1 = 0;//zerowanie liczby znaków przeciwnika
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {//jesli pole jest puste
					count1 = 0;//wyzeruj oba liczniki
					count2 = 0;
				}
				++column;
				--row;
			} while (column<=size-1);//wykonanie sprawdzenia dopóki nie znajdzeimy sie na drugim koñcu
		}
	}
	k = j;
	row = 0;
	column = 0;
	count1 = 0;
	count2 = 0;
	/* sprawdzanie po ukosie \ */
	if (i <= k) { //jezeli znajdujemy sie w gornym trojkacie
		row = 0; //ustawienie indeksów poczatku przek¹tnej
		column = j - i;
		if (column<= size - howManyInLine) { //sprawdzenie, czy na danej przekatnej moze zmiescic sie tyle znakow ile potrzeba do wygranej
			do {
				if (board[row][column] == sign) {//sprawdzanie kolejnych znaków
					++count1;//sumowanie
					count2 = 0;//zerowanie liczby znaków przeciwnika
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {//sprawdzanie kolejnych znaków
					++count2;//sumowanie
					count1 = 0;//zerowanie liczby znaków przeciwnika
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {//jesli pole jest puste
					count1 = 0;//wyzeruj oba liczniki
					count2 = 0;
				}
				++column;
				++row;
			} while (column <= size-1);//wykonanie sprawdzenia dopóki nie znajdzeimy sie na drugim koñcu
		}
	}
	else { //jezeli w dolnym
		row = i - j; //ustawienie indeksów poczatka przek¹tnej
		column = 0;
		if (row <= size - howManyInLine) { //sprawdzenie, czy na danej przekatnej moze zmiescic sie tyle znakow ile potrzeba do wygranej
			do {
				if (board[row][column] == sign) {//sprawdzanie kolejnych znaków
					++count1;//sumowanie
					count2 = 0;//zerowanie liczby znaków przeciwnika
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {//sprawdzanie kolejnych znaków
					++count2;//sumowanie
					count1 = 0;//zerowanie liczby znaków przeciwnika
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {//jesli pole jest puste
					count1 = 0;//wyzeruj oba liczniki
					count2 = 0;
				}
				++column;
				++row;
			} while (row <= size - 1);//wykonanie sprawdzenia dopóki nie znajdzeimy sie na drugim koñcu
		}
	}
	return 0;
}

int Board::checkFirstDiagonal(What sign) { //obecnie nie jest wykorzystywane, zast¹pione przez checkDiagonals
	What opposite; //wyznacz znak przeciwnika
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //sprawdzenie czy na przekatnej \ nie ma wygranej 
		if (board[i][i] == sign) {//sprawdzanie kolejnych znaków
			++count1;//sumowanie
			count2 = 0;//zerowanie liczby znaków przeciwnika
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][i] == opposite) {//sprawdzanie kolejnych znaków
			++count2;//sumowanie
			count1 = 0;//zerowanie liczby znaków przeciwnika
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {//jesli pole jest puste
			count1 = 0;//wyzeruj oba liczniki
			count2 = 0;
		}
	}
	return 0;
}

int Board::checkSecondDiagonal(What sign) {//obecnie nie jest wykorzystywane, zast¹pione przez checkDiagonals
	What opposite; //wyznacz znak przeciwnika
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //sprawdzenie czy na przekatnej / nie ma wygranej 
		if (board[i][size - i - 1] == sign) {//sprawdzanie kolejnych znaków
			++count1;//sumowanie
			count2 = 0;//zerowanie liczby znaków przeciwnika
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][size - i - 1] == opposite) {//sprawdzanie kolejnych znaków
			++count2;//sumowanie
			count1 = 0;//zerowanie liczby znaków przeciwnika
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {//jesli pole jest puste
			count1 = 0;//wyzeruj oba liczniki
			count2 = 0;
		}
	}
	return 0;
}

int Board::isEnd(int row, int column, What sign) { //sprawdzenie, czy wstawiony znak zmienia sytuacjê na planszy
	/* jeœli funkcje sprawdzaj¹ce zwracaj¹ wartoœæ inn¹ ni¿ 10 to zaistnia³a sytuacja wygranej lub przegranej*/
	int Value = checkVertical(column, sign);
	if (Value != 0) {
		return Value;
	}
	Value = checkHorizontal(row, sign);
	if (Value != 0) {
		return Value;
	}

	Value = checkDiagonals(row,column, sign);
	if (Value != 0) {
		return Value;
	}
	return 0;
}

void Board::show() { //wyœwietlanie planszy
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << (char)(board[i][j]);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "---------" << std::endl;
}

bool Board::isMoveLeft() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == What::none)
			{
				return true;
			}
		}
	}
	return false;
}

Who Board::getWhoseMove() {
	return whoseMove;
}
