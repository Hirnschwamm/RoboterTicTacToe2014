#include "tttfield.h"

TTTField::TTTField() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            field[x][y] = -1;
        }
    }
}

int TTTField::turn() {
    int r = 0;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (field[x][y] > -1) r++;
        }
    }

    return r;
}

void TTTField::newField(int newX, int newY, int p, TTTField *newField) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            newField->field[x][y] = field[x][y];
        }
    }
    newField->field[newX][newY] = p;
}

bool TTTField::won(int p) {
    //coloumns
    for (int x = 0; x < 3; x++) {
        if (field[x][0] == p && field[x][1] == p && field[x][2] == p) return true;
    }
    //rows
    for (int y = 0; y < 3; y++) {
        if (field[0][y] == p && field[1][y] == p && field[2][y] == p) return true;
    }
    //diagonals
    if (field[0][0] == p && field[1][1] == p && field[2][2] == p) return true;
    if (field[0][2] == p && field[1][1] == p && field[2][0] == p) return true;
    //not won
    return false;
}

bool TTTField::bestMove(int p, int *moveX, int *moveY, bool tryWin, bool checkBlock) {
    TTTField tmpField;

    if (tryWin) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (field[x][y] < 0) {
                    newField(x, y, p, &tmpField);
                    if (tmpField.won(p)) {
                        (*moveX) = x;
                        (*moveY) = y;
                        return true;
                    }
                }
            }
        }
    }

    p = 1 - p;

    if (checkBlock) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (field[x][y] < 0) {
                    newField(x, y, p, &tmpField);
                    if (tmpField.won(p)) {
                        (*moveX) = x;
                        (*moveY) = y;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool TTTField::checkFork(int p, int *moveX, int *moveY) {
    TTTField tmpFieldLv1;
    TTTField tmpFieldLv2;

    int wins = 0;
    std::vector<int> posRX;
    std::vector<int> posRY;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (field[x][y] < 0) {
                newField(x, y, p, &tmpFieldLv1);
                wins = 0;
                for (int x1 = 0; x1 < 3; x1++) {
                    for (int y1 = 0; y1 < 3; y1++) {
                        if (tmpFieldLv1.field[x1][y1] < 0) {
                            tmpFieldLv1.newField(x1, y1, p, &tmpFieldLv2);
                            if (tmpFieldLv2.won(p)) {
                                wins++;
                            }
                            if (wins > 1) {
                                (*moveX) = x;
                                (*moveY) = y;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    p = 1 - p;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (field[x][y] < 0) {
                newField(x, y, p, &tmpFieldLv1);
                wins = 0;
                for (int x1 = 0; x1 < 3; x1++) {
                    for (int y1 = 0; y1 < 3; y1++) {
                        if (tmpFieldLv1.field[x1][y1] < 0) {
                            tmpFieldLv1.newField(x1, y1, p, &tmpFieldLv2);
                            if (tmpFieldLv2.won(p)) {
                                wins++;
                                if (wins > 1) {
                                    posRX.push_back(x);
                                    posRY.push_back(y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (posRX.size() == 1) {
        (*moveX) = posRX[0];
        (*moveY) = posRY[0];
        return true;
    } else if (posRX.size() == 2) {
        int m = 0;
        std::vector<int> mSetX;
        std::vector<int> mSetY;
        predict(p, &mSetX, &mSetY);
        //randomizeable(?)
        while ((posRX[0] == mSetX[m] && posRY[0] == mSetY[m]) ||
               (posRX[1] == mSetX[m] && posRY[1] == mSetY[m])) m++;
        (*moveX) = mSetX[m];
        (*moveY) = mSetY[m];
        return true;
    } else if (posRX.size() > 2) {
        int m = rand() % 4;
        cornor(moveX, moveY, m);
        if (field[*moveX][*moveY] > -1) cornor(moveX, moveY, (m + 1) % 4);
        return true;
    }

    return false;
}

bool TTTField::checkLv3Fork(int p, int *moveX, int *moveY) {
	TTTField tmpFieldLv1;
    TTTField tmpFieldLv2;
	TTTField tmpFieldLv3;

    int wins = 0;
    std::vector<int> posRX;
    std::vector<int> posRY;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (field[x][y] < 0) {
                newField(x, y, p, &tmpFieldLv1);
                for (int x1 = 0; x1 < 3; x1++) {
                    for (int y1 = 0; y1 < 3; y1++) {
                        if (tmpFieldLv1.field[x1][y1] < 0) {
                            tmpFieldLv1.newField(x1, y1, p, &tmpFieldLv2);
							wins = 0;
							for (int x2 = 0; x2 < 3; x2++) {
								for (int y2 = 0; y2 < 3; y2++) {
                                    if (tmpFieldLv2.field[x2][y2] < 0) {
                                        tmpFieldLv2.newField(x2, y2, p, &tmpFieldLv3);
                                        if (tmpFieldLv3.won(p)) {
                                            wins++;
                                        }
                                        if (wins > 1) {
                                            (*moveX) = x;
                                            (*moveY) = y;
                                            return true;
                                        }
                                    }
								}
							}
                        }
                    }
                }
            }
        }
    }

	if (posRX.size() == 1) {
        (*moveX) = posRX[0];
        (*moveY) = posRY[0];
        return true;
    } else if (posRX.size() == 2) {
        int m = 0;
        std::vector<int> mSetX;
        std::vector<int> mSetY;
        predict(p, &mSetX, &mSetY);
        //randomizeable(?)
        while ((posRX[0] == mSetX[m] && posRY[0] == mSetY[m]) ||
               (posRX[1] == mSetX[m] && posRY[1] == mSetY[m])) m++;
        (*moveX) = mSetX[m];
        (*moveY) = mSetY[m];
        return true;
    } else if (posRX.size() > 2) {
        int m = rand() % 4;
        cornor(moveX, moveY, m);
        if (field[*moveX][*moveY] > -1) cornor(moveX, moveY, (m + 1) % 4);
        return true;
    }

    return false;
}

bool TTTField::predict(int p, std::vector<int> *moveX, std::vector<int> *moveY, bool off, bool deff) {
    TTTField tmpFieldLv1;
    TTTField tmpFieldLv2;

    if (off) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (field[x][y] < 0) {
                    newField(x, y, p, &tmpFieldLv1);
                    for (int x1 = 0; x1 < 3; x1++) {
                        for (int y1 = 0; y1 < 3; y1++) {
                            if (tmpFieldLv1.field[x1][y1] < 0) {
                                tmpFieldLv1.newField(x1, y1, p, &tmpFieldLv2);
                                if (tmpFieldLv2.won(p)) {
                                    moveX->push_back(x);
                                    moveY->push_back(y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (moveX->size() > 0) return true;

    p = 1 - p;

    if (deff) {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (field[x][y] < 0) {
                    newField(x, y, p, &tmpFieldLv1);
                    for (int x1 = 0; x1 < 3; x1++) {
                        for (int y1 = 0; y1 < 3; y1++) {
                            if (tmpFieldLv1.field[x1][y1] < 0) {
                                tmpFieldLv1.newField(x1, y1, p, &tmpFieldLv2);
                                if (tmpFieldLv2.won(p)) {
                                    moveX->push_back(x);
                                    moveY->push_back(y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (moveX->size() > 0) return true;
    return false;
}

void TTTField::randomEmpty(int *moveX, int *moveY) {
    if (turn() > 8) return;
    do {
        (*moveX) = rand() % 3;
        (*moveY) = rand() % 3;
    } while(field[*moveX][*moveY] > -1);
}

void TTTField::cornor(int *moveX, int *moveY, int m) {
    if (m < 2) {
        (*moveX) = 0;
    } else {
        (*moveX) = 2;
    }

    if (m % 2 > 0) {
        (*moveY) = 2;
    } else {
        (*moveY) = 0;
    }
}

void TTTField::debugPrint()
{
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (field[x][y] == -1) printf(" ");
            if (field[x][y] == 0) printf("X");
            if (field[x][y] == 1) printf("O");
            if (x < 2) printf(" | ");
        }
        printf("\n");
        if (y < 2) printf("---------\n");
    }
}

void TTTField::reset() {
	for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            field[x][y] = -1;
        }
    }
}

void TTTField::aiTurn(int level, int *moveX, int *moveY) {
    int mySign = turn() % 2;

    switch(level) {
        case 0: {
            break;
        }

        case 1: {
            randomEmpty(moveX, moveY);
            break;
        }

        case 2: {
            if (!bestMove(mySign, moveX, moveY, true, false)) randomEmpty(moveX, moveY);
            break;
        }

        case 3: {
            if (!bestMove(mySign, moveX, moveY)) randomEmpty(moveX, moveY);
            break;
        }

        case 4: {
            if (turn() == 0) {
                (*moveX) = 1;
				(*moveY) = 1;
				//8% lose vs level 3
				//cornor(moveX, moveY, rand() % 4);
            } else if (turn() == 1) {
                //O not center start?
                if (field[1][1] < 0) {
                    (*moveX) = 1;
                    (*moveY) = 1;
                } else {
                    cornor(moveX, moveY, rand() % 4);
                }
            } else if (!bestMove(mySign, moveX, moveY) &&
                       !checkFork(mySign, moveX, moveY)) {
                std::vector<int> moveSetX;
                std::vector<int> moveSetY;
                if (predict(mySign, &moveSetX, &moveSetY)) {
                    int m = rand() % moveSetX.size();
                    (*moveX) = moveSetX[m];
                    (*moveY) = moveSetY[m];
                } else {
                    randomEmpty(moveX, moveY);
                }
            }
            break;
        }

		case 5: {
            if (turn() == 0) {
				cornor(moveX, moveY, rand() % 4);
            } else if (turn() == 1) {
                //O not center start?
                if (field[1][1] < 0) {
                    (*moveX) = 1;
                    (*moveY) = 1;
                } else {
                    cornor(moveX, moveY, rand() % 4);
                }
            } else if (!bestMove(mySign, moveX, moveY) &&
                       !checkFork(mySign, moveX, moveY) &&
                       !checkLv3Fork(mySign, moveX, moveY)) {
                std::vector<int> moveSetX;
                std::vector<int> moveSetY;
                if (predict(mySign, &moveSetX, &moveSetY)) {
                    int m = rand() % moveSetX.size();
                    (*moveX) = moveSetX[m];
                    (*moveY) = moveSetY[m];
                } else {
                    randomEmpty(moveX, moveY);
                }
            }
            break;
        }
    }
}
