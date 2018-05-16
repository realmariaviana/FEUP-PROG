#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <fstream>
#include <ctime>
#include <map>

#include "Board.h"
#include "Dictionary.h"
#include "Puzzle.h"
#include "MyUtils.h"

class Player{
  public:
    Player(const string &f_in, const string &name);
    ~Player();

  private:
    Puzzle *pz;

    string name;
    map<string, string> sol;
};

#endif
