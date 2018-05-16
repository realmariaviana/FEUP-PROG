#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <map>

#include "MyUtils.h"
#include "Dictionary.h"
#include "Board.h"

using namespace std;

class Puzzle{
  public:
    Puzzle(const string &f_dictionary, const int &row, const int &column);
    Puzzle(const string &f_in);
    Puzzle(Dictionary &dc, Board &bd, map<string, string> &hintMap);
    ~Puzzle();
    void userIn(int &n);
    void cleanBoard();
    const string saveToFile();
  private:
    Dictionary *dc;
    Board *bd;

    string fileDictionary;
    string filePuzzle;
    bool newBoard;
    bool fileName;

    map<string, string> instructions;
    map<string, string> *hintMap;

    const bool userInPos(string &inPos);
    const int userInWrd(string &inWrd);
    const int checkInWrd(string &a);
};

#endif
