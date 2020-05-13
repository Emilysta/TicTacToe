#include "Player.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#define P_INF 10000 //plus "nieskonczonsc"
#define M_INF -10000 //minus "nieskonczonsc"

Player::Player()
{
	whatChar = What::none;
	whatPlayer = Who::none;
	isHuman = true;
}

Player::Player(What newWhatChar, Who newWhatPlayer, bool _ishuman) {
	whatChar = newWhatChar;
	whatPlayer = newWhatPlayer;
	isHuman = _ishuman;
}

bool Player::choseMove(Board* _board, int _row, int _column) { //ruch uzytkownika 
	int row = _row;
	int column = _column;

	_board->board[row][column] = whatChar;
	_board->countOfMovesToEnd--;
	if (_board->isEnd(row, column, whatChar) != 0) {
		return true;
	}
	
	if (_board->whoseMove == Who::player1) {
		_board->whoseMove = Who::player2;
	}
	else {
		_board->whoseMove = Who::player1;
	}
	return false;
}

bool Player::choseMove(Board* _board,int& move) { //ruch komputera
	int row = 0;
	int column = 0;
	searchForOption(_board, whatPlayer, row, column); //poszukiwanie opcji ruchu dla komputera 
	_board->board[row][column] = whatChar;
	_board->countOfMovesToEnd--;
	move = row * _board->size + column;
	if (_board->isEnd(row, column, whatChar) != 0) {
		return true;
	}
	if (whatPlayer == Who::player1) {
		_board->whoseMove = Who::player2;
	}
	else
	{
		_board->whoseMove = Who::player1;
	}
	return false;
}

void Player::setWhatChar(What newWhatChar) {
	whatChar = newWhatChar;
}

What& Player::getWhatChar() {
	return whatChar;
}

int Player::searchForOption(Board* _board, Who player, int& _row, int& _column) { //jesli rusza sie jako pierwszy to losuje sposrod "naroznikow" planszy
	//jesli jako pierwszy rusza sie uzytkownik to przeszukuje za pomoca algorytmu ciêæ alfa-beta
	int tab[2] = { 0,_board->size - 1 };
	if (_board->countOfMovesToEnd == _board->size * _board->size) {
		_row = tab[rand() % 2];
		_column = tab[rand() % 2];
		return 0;
	}
	std::ofstream file;
	file.open("nowy.txt", std::ios::out);
	int maxValue = M_INF;
	int scoreForMove = 0;
	for (int i = 0; i < _board->size; i++) {
		for (int j = 0; j < _board->size; j++) {
			if (_board->board[i][j] == What::none) {
				_board->board[i][j] = whatChar;
				scoreForMove = minimax(_board, i, j, 0, false, M_INF, P_INF);
				_board->board[i][j] = What::none;
				file<<scoreForMove<<" i: "<<i<<" j: "<<j<<std::endl;
				if (scoreForMove > maxValue) {
					_row = i;
					_column = j;
					maxValue = scoreForMove;
				}
			}
		}
	}
	file.close();
	return 0;
}

int Player::minimax(Board* _board, int i, int j, int depth, bool isMax, int alpha, int beta) {

	int scores = _board->isEnd(i, j, whatChar);
	if (scores == 10) {
		return scores - depth;
	}
	if (scores == -10) {
		return scores + depth;
	}
	if (_board->isMoveLeft() == false || depth == (2 * _board->size - _board->howManyInLine+2)) {
		return 0;
	}

	int maxValue;
	int scoreForMove = 0;
	if (isMax) {
		maxValue = M_INF;
		for (int i = 0; i < _board->size; i++) {
			for (int j = 0; j < _board->size; j++) {
				if (_board->board[i][j] == What::none) {
					_board->board[i][j] = whatChar;
					scoreForMove = minimax(_board, i, j, depth + 1, false, alpha, beta);
					maxValue = std::max(scoreForMove, maxValue);
					alpha = std::max(alpha, maxValue);
					_board->board[i][j] = What::none;
					if (alpha >= beta) {
						i = _board->size;
						j = _board->size;
					}
				}
			}
		}
		return maxValue;
	}
	else {
		int maxValue = P_INF;
		for (int i = 0; i < _board->size; i++) {
			for (int j = 0; j < _board->size; j++) {
				if (_board->board[i][j] == What::none) {
					_board->board[i][j] = getOpponentChar();
					scoreForMove = minimax(_board, i, j, depth + 1, true, alpha, beta);
					maxValue = std::min(scoreForMove, maxValue);
					_board->board[i][j] = What::none;
					beta = std::min(beta, maxValue);
					_board->board[i][j] = What::none;
					if (alpha >= beta) {
						i = _board->size;
						j = _board->size;
					}
				}
			}
		}
		return maxValue;
	}
}

What Player::getOpponentChar() {
	if (whatChar == What::circle) {
		return What::cross;
	}
	else {
		return What::circle;
	}
}