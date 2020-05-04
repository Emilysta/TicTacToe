#include "Player.h"
#include <iostream>
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
	int number;
	if (isHuman == true) {
		do {
			std::cout << "Wybierz ruch ... ";
			std::cin >> number;
			if (_board->board[number] != What::none) {
				std::cout << "Wybierz jeszcze raz!\n";
			}
		} while (_board->board[number] != What::none);

		_board->board[number] = whatChar;
		_board->countOfMovesToEnd--;
		if (_board->isEnd(number) == true) {
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
		number = searchForOption(*_board,whatPlayer);
		_board->board[number] = whatChar;
		_board->countOfMovesToEnd--;
		if (_board->isEnd(number) == true) {
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
int Player::searchForOption(Board _board,Who player) {
	int tab[4] = {0,_board.size-1,_board.size*_board.size-1,_board.size * _board.size - _board.size };
	int i=-1;
	if (_board.countOfMovesToEnd == _board.size * _board.size) {
		i = rand() % 3;
		return tab[i];
	}
	return algorithmAlfaBeta(_board,3,M_INF,P_INF);
}

int Player::algorithmAlfaBeta(Board _board, int maxdepth, int _alpha, int _beta) {
	int index = -1;
	if (_board.whoseMove == this->whatPlayer) {
		alpha(_board, maxdepth, _alpha, _beta,index);
		return index;
	}
	else {
		beta(_board, maxdepth, _alpha, _beta,index);
		return index;
	}
}

int Player::alpha(Board _board, int maxdepth,int _alpha, int _beta,int& index) {
	int size = _board.size * _board.size;
	int v = M_INF;
	What opponentChar;
	if (whatChar == What::circle) {
		opponentChar = What::cross;
	}
	else {
		opponentChar = What::circle;
	}
	if (maxdepth == 0)
		return _board.openLines(opponentChar);
	for (int i = 0; i < size; i++) {
		Board test = _board;
		if (test.board[i] == What::none) {
			test.board[i] = whatChar;
			if (_board.whoseMove == Who::player1) {
				test.whoseMove = Who::player2;
			}
			else {
				test.whoseMove = Who::player1;
			}	
			int v2;
			if (test.isEnd(i) != true) {
				v2 = this->beta(test, --maxdepth, _alpha, _beta,index);
			}
			else {
				v2 = 100;
			}
			if (v2 > v) { index = i; v = v2; }
			if (v2 >=_beta) { return v; }
			if (v2 > _alpha) { _alpha = v2; }
		}
	}

	return v;
}

int Player::beta(Board _board, int maxdepth, int _alpha, int _beta,int& index) {
	int size = _board.size * _board.size;
	int v = P_INF;
	What opponentChar;
	if (whatChar == What::circle) {
		opponentChar = What::cross;
	}
	else {
		opponentChar = What::circle;
	}
	if (maxdepth == 0)
		return _board.openLines(opponentChar);
	for (int i = 0; i < size; i++) {
		Board test = _board;
		if (test.board[i] == What::none) {
			test.board[i] = whatChar;
			if (_board.whoseMove == Who::player1) {
				test.whoseMove = Who::player2;
			}
			else {
				test.whoseMove = Who::player1;
			}	
			int v2;
			if (test.isEnd(i) != true) {
				v2 = this->alpha(test, --maxdepth, _alpha, _beta,index);
			}
			else {
				v2 = -100;
			}
			if (v2 < v) { index = i; v = v2; }
			if (v2 <= _beta) { return v; }
			if (v2 < _alpha) { _beta = v2; }
		}
	}

	return v;
}
