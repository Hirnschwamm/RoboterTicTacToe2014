#ifndef TTTFIELD_H
#define TTTFIELD_H

#include <vector>
#include <stdlib.h>
#include <stdio.h>

class TTTField
{
public:
    TTTField();
    int field[3][3];
    int turn();
    void newField(int x, int y, int p, TTTField *newField);
    bool won(int p);
    bool bestMove(int p, int *moveX, int *moveY, bool tryWin = true, bool checkBlock = true);
    bool checkFork(int p, int *moveX, int *moveY);
	bool checkLv3Fork(int p, int *moveX, int *moveY);
    bool predict(int p, std::vector<int> *moveX, std::vector<int> *moveY, bool off = true, bool deff = true);
    void aiTurn(int level, int *moveX, int *moveY);
    void randomEmpty(int *moveX, int *moveY);
    void cornor(int *moveX, int *moveY, int m);
    void debugPrint();
	void reset();
};

#endif // TTTFIELD_H
