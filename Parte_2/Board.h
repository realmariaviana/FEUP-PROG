#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>

#include "ColorText.h"

#define LTR_TO_INT(n) n - 65
#define ltr_TO_INT(n) n - 97

using namespace std;

class Board {
  public:
    Board(int row, int column);
    Board(const string &line);
    void drawBoardEmpty();        //Empty board for the first iteration program
    void drawBoardCurrent();      //Current board displaying words as they are entered
    const bool insertWord(const string &wrd,const char &init,const char &end,const char &ori);
    const string deleteWord(const char &init, const char &end, const char &ori);
    void finishBoard();
    void addLine(const string &line);
    void writeToFile(ofstream &F);
    //const string getWord(const char &init, const char &end, const char &ori);
  private:
    vector< vector<char> > board;
    int row, column;

    const int checkBoardV(const string &wrd, const int &r, const int &c);
    const int checkBoardH(const string &wrd, const int &r, const int &c);
    void insertWordV(const string &wrd, const int &r, const int &c);
    void insertWordH(const string &wrd, const int &r, const int &c);
    const string deleteWordV(const int &r, const int &c);
    const string deleteWordH(const int &r, const int &c);
    const bool checkSurrondingsH(const int &r, const int &c);
    const bool checkSurrondingsV(const int &r, const int &c);
    //const string getWordV(const int &r, const int &c);
    //const string getWordH(const int &r, const int &c);
};

#endif
