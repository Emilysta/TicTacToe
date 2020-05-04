#include "Player.h"
#include <iostream>
#include <algorithm>
#define P_INF 10000 //plus "nieskonczonsc"
#define M_INF -10000 //minus "nieskonczonsc"

Player::Player()
{
	whatChar = What::none;
	whatPlayer = Who::none;
	isHuman = true;
}

Player::Player(What newWhatChar,Who newWhatPlayer, bool _ishuman) {
	whatChar = newWhatChar;
	whatPlayer = newWhatPlayer;
	isHuman = _ishuman;
}

bool Player::choseMove(Board* _board) {
	int row;
	int column;
	if (isHuman == true) {
		do {
			do {
				std::cout << "Wybierz ruch rzad: ";
				std::cin >> row;
			} while (row < 0 || row >= _board->size);
			do {
				std::cout << "Wybierz ruch kolumne: ";
				std::cin >> column;
			} while (column < 0 || column >= _board->size);
		} while ( _board->board[row][column] != What::none);

		_board->board[row][column] = whatChar;
		_board->countOfMovesToEnd--;
		if (_board->isEnd(row,column) == true) {
			return true;
		}
		if (_board->whoseMove == Who::player1) {
			_board->whoseMove = Who::player2;
		}
		else {
			_board->whoseMove = Who::player1;
		}
	}
	else {
		row = 0;
		column = 0;
		searchForOption(*_board,whatPlayer,row, column);
		_board->board[row][column] = whatChar;
		_board->countOfMovesToEnd--;
		if (_board->isEnd(row,column) == true) {
			return true;
		}
		if (whatPlayer == Who::player1) {
			_board->whoseMove = Who::player2;
		}
		else
		{
			_board->whoseMove = Who::player1;
		}
	}
	return false;
}

void Player::setWhatChar(What newWhatChar) {
	whatChar = newWhatChar;
}

What& Player::getWhatChar() {
	return whatChar;
}

int Player::searchForOption(Board _board,Who player,int& _row,int& _column) {
	int tab[2] = { 0,_board.size - 1 };
	if (_board.countOfMovesToEnd == _board.size * _board.size) {
		_row = tab[rand() % 2];
		_column = tab[rand() % 2]; 
		return 0;
	}

	int maxValue = M_INF;
	
	for (int i = 0; i < _board.size; i++) {
		for (int j = 0; j < _board.size; j++) {
			if (_board.board[i][j] == What::none) {
				_board.board[i][j] = whatChar;
				int scoreForMove =minimax(_board,0,false);
				_board.board[i][j] = What::none;
				std::cout << "Waga: " << scoreForMove << "Rzad: " << i << "Kolumna" << j << std::endl;
				if (scoreForMove > maxValue) {
					_row = i;
					_column = j;
					maxValue = scoreForMove;
				}
			}
		}
	}
	
}

int Player::minimax(Board _board,int depth, bool isMax){
	int scores = _board.evaluate(whatChar);
	if (scores == 10) {
		return scores-depth ;
	}
	if (scores == -10) {
		return scores+depth ;
	}
	
	if (_board.isMoveLeft()==false) {
		return 0;
	}

	if (isMax){
		int maxValue = M_INF;
		for (int i = 0; i < _board.size; i++) {
			for (int j = 0; j < _board.size; j++) {
				if (_board.board[i][j] == What::none) {
					_board.board[i][j] = whatChar;
					int scoreForMove = minimax(_board,depth+1,false);
					maxValue = std::max(scoreForMove, maxValue);
					_board.board[i][j]=What::none;
				}
			}
		}
		return maxValue;
	}
	else {
		int minValue = P_INF;
		for (int i = 0; i < _board.size; i++) {
			for (int j = 0; j < _board.size; j++) {
				if (_board.board[i][j] == What::none) {
					_board.board[i][j] = getOpponentChar();
					int scoreForMove = minimax(_board,depth+1,true);
					minValue = std::min(scoreForMove, minValue);
					_board.board[i][j] = What::none;
				}
			}
		}
		return minValue;
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