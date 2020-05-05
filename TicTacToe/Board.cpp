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
    board = new What*[size];
    for (int i = 0; i < size; ++i) { 
        board[i] = new What[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j++) {
            board[i][j]= boardToCopy.board[i][j];
        }
    }
    whoseMove = boardToCopy.whoseMove;
    winner = boardToCopy.winner;
    countOfMovesToEnd = boardToCopy.countOfMovesToEnd;
    howManyInLine = boardToCopy.howManyInLine;
}

Board::Board(int newSize,int inLine) {
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
    whoseMove = Who(std::rand() % 2 + 1);
    countOfMovesToEnd = size * size;
    howManyInLine = inLine;
 }

Board::~Board() {
    for (int i = 0; i < size; i++) {
        delete board[i];
    }
    delete[] board;
}

int Board::checkVertical(int i_column,What sign) { //sprawdz w pionie
    What opposite;
    if (sign == What::circle) {
        opposite = What::cross;
    }
    else {
        opposite = What::circle;
    }
    int count1=0;
    int count2=0;
    for (int i = 0; i < size; i++) {//i_column indeks sprawdzanej kolumny
        if (board[i][i_column] ==sign) {
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
    }
    return 0;
}

int Board::checkHorizontal(int i_row,What sign) { //sprawdz w poziomie
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
    }
    return 0;
}

int Board::isEnd(int row,int column,What sign) {
    int Value = checkVertical(column, sign);
    if (Value != 0) {
       return Value;
    }
    Value = checkHorizontal(row, sign);
    if (Value != 0) {
       return Value;
    }
    if (row == column) {
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
    }
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

int Board::evaluate(What sign) {
    for (int i = 0; i < size; i++)
    {
        int Value = checkHorizontal(i, sign);
        if (Value!=0) {
            return Value;
        }
        Value = checkVertical(i, sign);
        if (Value != 0) {
            return Value;
        }
    }
    int Value = checkFirstDiagonal(sign);
    if (Value != 0) {
        return Value;
    }
    Value = checkSecondDiagonal(sign);
    if (Value != 0) {
        return Value;
    }

    return 0;
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
