#ifndef TTTFIELD_H
#define TTTFIELD_H

#include <vector>
#include <stdlib.h>
#include <stdio.h>

class TTTField
{
    //Tic Tac Toe logic
public:
    TTTField(); //initalises this field
    int field[3][3]; //the playfield
    int turn(); //amount of tokens on field
    void newField(int x, int y, int p, TTTField *newField); //creates a copy of this field and adds token p at field[x][y]
    bool won(int p); //has player p won?
    bool bestMove(int p, int *moveX, int *moveY, bool tryWin = true, bool checkBlock = true); //used for AI
    bool checkFork(int p, int *moveX, int *moveY); //used for AI
    bool checkLv3Fork(int p, int *moveX, int *moveY); //(unused) attempt to improve AI
    bool predict(int p, std::vector<int> *moveX, std::vector<int> *moveY, bool off = true, bool deff = true); //used for AI
    void aiTurn(int level, int *moveX, int *moveY); //gives the next move for the AI level on this field
    void randomEmpty(int *moveX, int *moveY); //gives a random empty field position
    void cornor(int *moveX, int *moveY, int m); //used for AI (gives cornor m)
    void debugPrint(); //prints field to console
    void reset(); //resets this field
};

#endif // TTTFIELD_H
