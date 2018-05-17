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

  string key, val;
  vector<string> coord;

  while(!F.eof()){
    F >> val >> key;
    coord.push_back(val);
    sol.insert(pair<string, string>(key, val));
  }

  pz = new Puzzle(dc, bd);
  int i = 0;

  for(auto it : sol){
    key = it.second;
    val = it.first;
    char r, c, ori;
    string aux;
    stringstream ss, hint;

    pz -> addHintMap(key, val);

    ss << coord[i++];
    ss >> r >> c >> ori;
    hint << r << c << ' ';

    aux = dc -> getHint(key);
    hint << aux;

    if(ori == 'V'){
      hintV.push_back(hint.str());
    }else{
      hintH.push_back(hint.str());
    }
  }

  cout << "VERTICAL:" << endl;
  for(int i = 0; i < hintV.size(); i++){
    cout << "- " << hintV[i] << endl;
  }

  cout << endl << "HORIZONTAL" << endl;
  for(int i = 0; i < hintH.size(); i++){
    cout << "- " << hintH[i] << endl;
  }
  cout << endl;
}
