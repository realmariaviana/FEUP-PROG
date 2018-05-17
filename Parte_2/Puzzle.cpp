#include "Puzzle.h"

using namespace std;

Puzzle::Puzzle(const string &f_dictionary, const int &row, const int &column){
  this -> fileDictionary = f_dictionary;
  this -> filePuzzle = "b001.txt";
  this -> newBoard = true;
  this -> fileName = false;
  this -> hintM = false;

  bd = new Board(row, column);
  dc = new Dictionary(f_dictionary);
}

Puzzle::Puzzle(const string &f_in){
  this -> filePuzzle = f_in;
  this -> newBoard = false;
  this -> fileName = true;
  this -> hintM = false;

  ifstream F;
  string line;

  openFile(f_in, F);

  getline(F, line);
  trimString(line);
  dc = new Dictionary(line);
  this -> fileDictionary = line;

  getline(F, line);

  getline(F, line);
  trimString(line);
  bd = new Board(line);

  while(!line.empty()){
    getline(F, line);
    trimString(line);
    bd -> addLine(line);
  }

  string key, val;

  while(!F.eof()){
    F >> val >> key;
    cout << val << key << endl;
    instructions.insert(pair<string, string>(key, val));
  }
  bd -> drawBoardCurrent();
}

Puzzle::Puzzle(Dictionary *dc, Board *bd){
  this -> dc = dc;
  this -> bd = bd;
  this -> hintMap = hintMap;
  this -> newBoard = false;
  this -> hintM = true;

  bd -> drawBoardCurrent();
}

Puzzle::~Puzzle(){
  delete(dc);
  delete(bd);
}

void Puzzle::userIn(int &n){
  int ret;

  if(newBoard) bd -> drawBoardEmpty();

  while(1){
    string inPos, inWrd, delWrd;
    stringstream ss;
    char init, end, ori;
    int flag = -1;

    if(userInPos(inPos)) return;

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
          n++;
          if(hintM){
            string ret;
            ret = getHintP(inPos);
            cout << inPos << " hint: " << dc -> getHint(ret) << endl;
          }
          //? dar pistas para aquela posicao
          //utilizar dc -> searchWords(wildStr)
          //wildStr string com ? nos locais onde nao temos letras
          //ha funcoes no board que retornam a linha/coluna para as coordenadas indicadas
          //mas e preciso altera las unico criterio de paragem e #
        }
    }

    switch (flag) {
      case 0:
        instructions.insert(pair<string, string>(inWrd, inPos));
        flag = -1;
        break;
      case 1:{
        map<string, string>::iterator it;
        it = instructions.find(delWrd);
        instructions.erase(it);
        flag = -1;
        break;
      }
      default:
        break;
    }
    bd -> drawBoardCurrent();
  }
}

void Puzzle::cleanBoard(){
  bd -> finishBoard();
}

void newFileName(string &fileName){
  stringstream ss;
  char a;
  int n;

  ss << fileName;
  ss >> a >> n >> a >> a >> a >> a;
  n++;

  if(n<10){
    stringstream sa;
    sa << "b00" << n << ".txt";
    fileName = sa.str();
  }else if(n >= 10 && n < 100){
    stringstream sa;
    sa << "b0" << n << ".txt";
    fileName = sa.str();
  }else{
    stringstream sa;
    sa << "b" << n << ".txt";
    fileName = sa.str();
  }
}

const string Puzzle::saveToFile(){
  if(fileName){
    newFileName(filePuzzle);
  }

  ofstream F;

  openFile(filePuzzle, F);

  F << fileDictionary << endl << endl;

  bd -> writeToFile(F);

  for(auto it : instructions){
    F << it.second << ' ' << it.first << endl;
  }

  F.close();

  return filePuzzle;
}

void Puzzle::addHintMap(const string &key, const string &val){
  hintMap.insert(pair<string, string>(key, val));
}

//PRIVATE METHODS
const string Puzzle::getHintP(const string &coord){
  return hintMap.find(coord) -> second;
}

const int Puzzle::userInWrd(string &inWrd){
  bool flag = true;
  int ret;

  cout << "Word ( - = remove / ? = help) ? ";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin >> inWrd;
  cout << endl;

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

  cout << endl << "Position ( LCD / CTRL-D = stop) ? ";
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
