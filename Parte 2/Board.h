#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <iomanip>
#include <cctype>

#include "ColorText.h"

#define LTR_TO_INT(n) n - 65
#define ltr_TO_INT(n) n-97

using namespace std;

class Board {
  public:
    Board(int row, int column);
    ~Board();
    void drawBoardEmpty(); //Empty board for the first iteration program
    void drawBoardCurrent(); //Current board displaying words as they are entered
    void drawBoardStart(); //Board for player program
    const bool insertWord(const string &wrd,const char &init,const char &end,const char &ori);
    void deleteWord(const char &init, const char &end);
  private:
    char **board;
    int row, column;

    const int checkBoardH(const string &wrd, const int &r, const int &c);
    const int checkBoardV(const string &wrd, const int &r, const int &c);
    void insertWordV(const string &wrd, const int &r, const int &c);
    void insertWordH(const string &wrd, const int &r, const int &c);
};

#endif
