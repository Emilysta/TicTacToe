#include "Board.h"
#include <iostream>
#include <time.h>

Board::Board() {
	size = 0;
	board = nullptr;
	whoseMove = Who::none;
	winner = Who::none;
	countOfMovesToEnd = 0;
	howManyInLine = 0;
}
Board::Board(const Board& boardToCopy) {
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
	winner = boardToCopy.winner;
	countOfMovesToEnd = boardToCopy.countOfMovesToEnd;
	howManyInLine = boardToCopy.howManyInLine;
}

Board::Board(int newSize, int inLine,Who start) {
	srand((unsigned)(time(NULL)));
	size = newSize;
	board = new What * [size];//tablica o rozmiarze np 4x4 
	for (int i = 0; i < size; ++i) {
		board[i] = new What[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = What::none;
		}
	}
	winner = Who::none;
	whoseMove = start;
	countOfMovesToEnd = size * size;
	howManyInLine = inLine;
}

Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete board[i];
	}
	delete[] board;
}

int Board::checkVertical(int i_column, What sign) { //sprawdz w pionie
	What opposite;
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) {//i_column indeks sprawdzanej kolumny
		if (board[i][i_column] == sign) {
			++count1;
			count2 = 0;
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][i_column] == opposite) {
			++count2;
			count1 = 0;
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {
			count1 = 0;
			count2 = 0;
		}
	}
	return 0;
}

int Board::checkHorizontal(int i_row, What sign) { //sprawdz w poziomie
	What opposite;
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //i_row indeks sprawdzanego rzedu 
		if (board[i_row][i] == sign) {
			++count1;
			count2 = 0;
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i_row][i] == opposite) {
			++count2;
			count1 = 0;
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {
			count1 = 0;
			count2 = 0;
		}
	}
	return 0;
}

int Board::checkDiagonals(int i, int j, What sign) {
	What opposite;
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
		row = i + j;
		column = 0;
		if (row + 1 >= howManyInLine) {
			do {
				if (board[row][column] == sign) {
					++count1;
					count2 = 0;
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {
					++count2;
					count1 = 0;
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {
					count1 = 0;
					count2 = 0;
				}
				++column;
				--row;
			} while (row >= 0);
		}
	}
	else { //jezeli w dolnym
		row = size - 1;
		column = j - (size - 1 - i);
		if (column<= size - howManyInLine) {
			do {
				if (board[row][column] == sign) {
					++count1;
					count2 = 0;
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {
					++count2;
					count1 = 0;
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {
					count1 = 0;
					count2 = 0;
				}
				++column;
				--row;
			} while (column<=size-1);
		}
	}
	k = j;
	row = 0;
	column = 0;
	count1 = 0;
	count2 = 0;
	/* sprawdzanie po ukosie \ */
	if (i <= k) { //jezeli znajdujemy sie w gornym trojkacie
		row = 0;
		column = j - i;
		if (column<= size - howManyInLine) {
			do {
				if (board[row][column] == sign) {
					++count1;
					count2 = 0;
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {
					++count2;
					count1 = 0;
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {
					count1 = 0;
					count2 = 0;
				}
				++column;
				++row;
			} while (column <= size-1);
		}
	}
	else { //jezeli w dolnym
		row = i - j;
		column = 0;
		if (row <= size - howManyInLine) {
			do {
				if (board[row][column] == sign) {
					++count1;
					count2 = 0;
					if (count1 == howManyInLine) {
						return 10;
					}
				}
				else if (board[row][column] == opposite) {
					++count2;
					count1 = 0;
					if (count2 == howManyInLine) {
						return -10;
					}
				}
				else {
					count1 = 0;
					count2 = 0;
				}
				++column;
				++row;
			} while (row <= size - 1);
		}
	}
	return 0;
}

int Board::checkFirstDiagonal(What sign) {
	What opposite;
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //sprawdzenie czy na przekatnej \ nie ma wygranej 
		if (board[i][i] == sign) {
			++count1;
			count2 = 0;
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][i] == opposite) {
			++count2;
			count1 = 0;
			if (count2 == howManyInLine) {
				return -10;
			}
		}
	}
	return 0;
}

int Board::checkSecondDiagonal(What sign) {
	What opposite;
	if (sign == What::circle) {
		opposite = What::cross;
	}
	else {
		opposite = What::circle;
	}
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < size; i++) { //sprawdzenie czy na przekatnej / nie ma wygranej 
		if (board[i][size - i - 1] == sign) {
			++count1;
			count2 = 0;
			if (count1 == howManyInLine) {
				return 10;
			}
		}
		else if (board[i][size - i - 1] == opposite) {
			++count2;
			count1 = 0;
			if (count2 == howManyInLine) {
				return -10;
			}
		}
		else {
			count1 = 0;
			count2 = 0;
		}
	}
	return 0;
}

int Board::isEnd(int row, int column, What sign) {
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
	/*if (row == column) {
		Value = checkFirstDiagonal(sign);
		if (Value != 0) {
			return Value;
		}
	}
	for (int i = 0; i < size; i++) {
		if ((row == i && column == size - i - 1)) {
			Value = checkSecondDiagonal(sign);
			if (Value != 0) {
				return Value;
			}
		}
	}*/
	return 0;
}

void Board::show() {
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

Who Board::checkWinner() {
	if (winner == Who::none && isMoveLeft() == false) {
		return Who::none;
	}
	else {
		return winner;
	}
}

Who Board::getWhoseMove() {
	return whoseMove;
}
