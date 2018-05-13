#include "Puzzle.h"

using namespace std;

Puzzle::Puzzle(const string &f_dictionary, const int &row, const int &column){
  this -> fileName = f_dictionary;

  bd = new Board(row, column);
  dc = new Dictionary(f_dictionary);
}

/*Puzzle::Puzzle(const string &f_in){

}*/

Puzzle::~Puzzle(){
  delete(dc);
  delete(bd);
}

const int checkInPos(string a){
  if(a.size() != 3) return 1;

  stringstream ss;
  char init, end, ori;

  ss << a;
  ss >> init >> end >> ori;

  if(init < 65 || init > 90) return 2;
  if(end < 97 || init > 122) return 2;
  if(ori != 'V' && ori != 'H') return 2;

  return 0;
}

const bool Puzzle::userInPos(string &inPos){
  bool flag = true;

  cout << "Position ( LCD / CTRL-D = stop) ? ";
  cin >> inPos;

  if(cin.eof()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
  }

  while(1){
    int ret = checkInPos(inPos);
    switch (ret) {
      case 0:
        flag = false;
        break;
      case 1:
        cout << "Invalid input size: LCD" << endl;
        inPos.erase();
        break;
      case 2:
        cout << "Invalid input letters: LineColumnDirection" << endl;
        inPos.erase();
        break;
    }
    if(!flag) break;
    cout << "Try again (LCD / CTRL-D = stop) ? ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> inPos;
    if(cin.eof()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
      }
  }

  return false;
}

const int Puzzle::checkInWrd(string &a){
  if(a.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos){
    if(dc->isValid(a)){
      return 0;
    }else{
      return 1;
    }
  }else{
    if(a.compare("-") != 0 && a.compare("?") != 0){
      return 2;
    }else{
      return -1;
    }
  }
}

const int Puzzle::userInWrd(string &inWrd){
  bool flag = true;
  int ret;

  cout << "Word ( - = remove / ? = help) ? ";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin >> inWrd;

  while(1){
    if(cin.eof()){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input: Word (- = remove / ? = help)";
      cin >> inWrd;
    }

    int aux = checkInWrd(inWrd);
    switch (aux) {
      case -1:
        flag = false;
        ret = 1;
        break;
      case 0:
        flag = false;
        ret = 0;
        break;
      case 1:
        cout << "Word does not exist" << endl;
        break;
      case 2:
        cout << "Invalid symbol: - = remove / ? = help" << endl;
        break;
    }
    if(!flag) break;
    cout << "Try again: Word (- = remove / ? = help) ? ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> inWrd;
  }

  return ret;
}

void Puzzle::userIn(){
  int ret;
  int flag;

  bd -> drawBoardEmpty();

  while(1){
    string inPos, inWrd, delWrd;
    stringstream ss;
    char init, end, ori;

    if(userInPos(inPos)) break;

    ss << inPos;
    ss >> init >> end >> ori;

    ret = userInWrd(inWrd);

    switch (ret) {
      case 0:
        if(bd -> insertWord(inWrd, init, end, ori)) flag = 0;
        break;
      case 1:
        if(inWrd.compare("-") == 0){
          delWrd = bd -> deleteWord(init, end, ori);
          flag = 1;
          break;
        }else{
          flag = -1;
          /*string wldStr = bd -> getWord(init, end , ori);
          vector<string> opt = dc -> searchWords(wldStr);

          for(int i = 0; i < opt.size(); i++) cout << opt[i] << "; ";
          cout << endl;
          flag2 = false;
          break;*/
        }
    }

    switch (flag) {
      case 0:
        instructions.insert(pair<string, string>(inWrd, inPos));
        break;
      case 1:{
        map<string, string>::iterator it;
        it = instructions.find(delWrd);
        instructions.erase(it);
        break;
      }
      default:
        break;
    }
    bd -> drawBoardCurrent();
  }
}
