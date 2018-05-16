#include "Player.h"

using namespace std;

Player::Player(const string &f_in, const string &name){
  this -> name = name;

  ifstream F;
  string line;

  Dictionary *dc;
  Board *bd;

  openFile(f_in, F);

  getline(F, line);
  trimString(line);
  dc = new Dictionary(line);

  getline(F, line);

  getline(F, line);
  trimString(line);
  bd = new Board(line, true);

  while(!line.empty()){
    getline(F, line);
    trimString(line);
    bd -> addLine(line, true);
  }

  getline(F, line);

  string key, val;

  while(!F.eof()){
    F >> val >> key;
    sol.insert(pair<string, string>(key, val));
  }

  map<string, string> *hintMap;

  for(auto it : sol){
    key = it.second;
    val = it.first;
    hintMap -> insert(pair<string, string>(key, val));
  }

  pz = new Puzzle(dc, bd, hintMap);
}
