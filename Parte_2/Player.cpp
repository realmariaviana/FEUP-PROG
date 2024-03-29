#include "Player.h"

using namespace std;

Player::Player(const string &f_in, const string &name){
  this -> name = name;
  this -> numHelp = 0;
  this -> fileName = f_in;

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

  while(!F.eof()){
    string key, val;
    F >> val >> key;
    if(val.empty() && key.empty()) break;
    sol.insert(pair<string, string>(key, val));
  }

  pz = new Puzzle(dc, bd);
  int i = 0;

  for(auto it : sol){
    string key, val;

    key = it.second;
    val = it.first;
    char r, c, ori;
    string aux;
    stringstream ss, hint;

    pz -> addHintMap(key, val);

    ss << key;
    ss >> r >> c >> ori;
    hint << r << c << ' ';
    aux = dc -> getHint(val);
    hint << aux;

    if(ori == 'V'){
      hintV.push_back(hint.str());
    }else{
      hintH.push_back(hint.str());
    }
    i++;
  }

  printHint();
}

void Player::printHint(){
  cout << endl << "VERTICAL:" << endl;
  for(int i = 0; i < hintV.size(); i++){
    cout << "- " << hintV[i] << endl;
  }
  cout << endl << "HORIZONTAL" << endl;
  for(int i = 0; i < hintH.size(); i++){
    cout << "- " << hintH[i] << endl;
  }
}

void Player::userIn(){
  int ret;

  this -> init = time(NULL);

  pz -> userIn(ret);

  this -> end = time(NULL);

  this -> numHelp = ret;

}

//Takes care of file name incrementing its number and adding _p
void newFileNameP(string &fileName){
  stringstream ss, name;
  char a;
  int n;

  ss << fileName;
  ss >> a >> n >> a >> a >> a >> a;

  if(n < 10){
    name << "b00" << n << "_b.txt";
    fileName = name.str();
  }else if(n >= 10 && n < 100){
    name << "b0" << n << "_b.txt";
    fileName = name.str();
  }else{
    name << "b" << n << "_b.txt";
    fileName = name.str();
  }
}

const string Player::writeToFile(){
  newFileNameP(fileName);

  ofstream F;

  openFile(fileName, F);

  F << "Player Name: " << name << endl;
  F << "Time: " << end - init << " (s)" << endl;
  F << "Number of clues: " << numHelp << endl << endl;

  pz -> writeToFileB(F);

  return fileName;
}

const bool Player::isWinner(){
  vector<string> solV = solToVec();
  vector<string> insV = pz -> getInstructions();

  sortVector(solV);
  sortVector(insV);

  return solV == insV;
}

//PRIVATE METHODS
vector<string> Player::solToVec(){
  vector<string> ret;

  for(auto it : sol){
    string key, val;
    stringstream ss;

    key = it.first;
    val = it.second;

    ss << key << ' ' << val;

    ret.push_back(ss.str());
  }

  return ret;
}
