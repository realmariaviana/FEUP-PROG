#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <sstream>

#include "Board.h"
#include "Dictionary.h"
#include "Puzzle.h"
#include "MyUtils.h"

class Player{
  public:
    Player(const string &f_in, const string &name);
    ~Player();

  private:
    Dictionary *dc;
    Board *bd;
    Puzzle *pz;

    string name;
    map<string, string> sol;
    vector<string> hintH;
    vector<string> hintV;
};

#endif
