#include "Player.h"
#include <iostream>

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
	do {
		std::cout << "Wybierz ruch ... ";
		std::cin >> number;
		if (_board->board[number] != What::none) {
			std::cout << "Wybierz jeszcze raz!\n";
		}
	} while (_board->board[number] != What::none );
	if (_board->whoseMove == Who::player1 && whatPlayer == Who::player1) {
		_board->board[number] = whatChar;
		if (_board->isEnd(number) == true) {
			return true;
		}
		_board->whoseMove = Who::player2;
	}
	else if (_board->whoseMove == Who::player2 && whatPlayer == Who::player2) {
		_board->board[number] = whatChar;
		if (_board->isEnd(number) == true) {
			return true;
		}
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