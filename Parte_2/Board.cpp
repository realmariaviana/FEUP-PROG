#include "Board.h"

using namespace std;

Board::Board(int row, int columnn){
  this -> row = row;
  this -> column = columnn;

  board.reserve(row);

  for(int i = 0; i < row; i++){
    board[i].reserve(column);
    for(int j = 0; j < column; j++) board[i][j] = '.';
  }
}

void Board::drawBoardEmpty(){
  char ltrC = 'a';
  char ltrR = 'A';

  setcolor(RED);
  cout << ' ';
  for(int i = 0; i < column; i++, ltrC++) cout << setw(2) << ltrC;
  cout << endl;
  setcolor(NO_COLOR);

  for(int i = 0; i < row; i++){
    cout << RED << ltrR++;
    for(int j = 0; j < column; j++){
      setcolor(BLACK, WHITE_B);
      cout << setw(2) << '.';
    }
    setcolor(NO_COLOR);
    cout << endl;
  }
}

void Board::drawBoardCurrent(){
  char ltrC = 'a';
  char ltrR = 'A';

  setcolor(RED);
  cout << ' ';
  for(int i = 0; i < column; i++, ltrC++) cout << setw(2) << ltrC;
  cout << endl;
  setcolor(NO_COLOR);

  for(int i = 0; i < row; i++){
    cout << RED << ltrR++;
    for(int j = 0; j < column; j++){
      setcolor(BLACK, WHITE_B);
      cout << setw(2) << board[i][j];
    }
    setcolor(NO_COLOR);
    cout << endl;
  }
}

const bool Board::insertWord(const string &wrd, const char &init,const char &end,const char &ori){
  int r = LTR_TO_INT(init);
  int c = ltr_TO_INT(end);

  int maxSpace, ret;
  if(ori == 'V'){
    maxSpace = column - c;
    ret = checkBoardV(wrd, r, c);
  }else{
    maxSpace = row - r;
    ret = checkBoardH(wrd, r, c);
  }

  if(maxSpace < wrd.size()){
    cout << "Word does not fit, not enough space" << endl;
    return false;
  }

  if(ret == -1){
    cout << "Incompatible letter somewhere" << endl;
    return false;
  }

  if(ori == 'V'){
    insertWordV(wrd, r, c);
  }else{
    insertWordH(wrd, r, c);
  }

  return true;
}

void Board::deleteWord(const char &init, const char &end, const char &ori){
  int r = LTR_TO_INT(init);
  int c = ltr_TO_INT(end);
  
  if(ori == 'V'){
    deleteWordV(r, c);
  }else{
    deleteWordH(r, c);
  }
}

//PRIVATE METHODS
const bool Board::checkSurrondingsH(const int &r, const int &c){
  if(r == 0){
    return board[r+1][c] != '.' && board[r+1][c] != '#';
  }else if(r == row -1){
    return board[r-1][c] != '.' && board[r+1][c] != '#';
  }else{
    return board[r-1][c] != '.' && board[r-1][c] != '#' && board[r+1][c] != '.' && board[r+1][c] != '#';
  }
}

const bool Board::checkSurrondingsV(const int &r, const int &c){
  if (c == 0) {
    return board[r][c+1] != '.' && board[r][c+1] != '#';
  } else if (c == column -1) {
    return board[r][c-1] != '.' && board[r][c-1] != '#';
  } else {
    return board[r][c-1] != '.' && board[r][c-1] != '#' && board[r][c+1] != '.' && board[r][c+1] != '#';
  }
}

void Board::deleteWordH(const int &r, const int &c){
  int aux = c;
  while(aux != column){
    if(board[r][aux] == '.' || board[r][aux] == '#') return;
    if(checkSurrondingsH(r, aux)){ aux++; continue; }
    board[r][aux++] = '.';
  }
}

void Board::deleteWordV(const int &r, const int &c){
  int aux = r;
  while(aux != row){
    if(board[aux][c] == '.' || board[aux][c] == '#') return;
    if(checkSurrondingsV(aux, c)){ aux++; continue; }
    board[aux++][c] = '.';
  }
}

void Board::insertWordH(const string &wrd, const int &r, const int &c){
  int aux = c;
  for(size_t i = 0; i < wrd.size(); i++){
    board[r][aux++] = wrd.at(i);
  }
}

void Board::insertWordV(const string &wrd, const int &r, const int &c){
  int aux = r;
  for(size_t i = 0; i < wrd.size(); i++){
    board[aux++][c] = wrd.at(i);
  }
}

const int Board::checkBoardH(const string &wrd, const int &r, const int &c){
  int aux = c;
  for(int i = 0; i < wrd.size(); i++){
    if(board[r][aux] == wrd.at(i) || board[r][aux] == '#' || board[r][aux] == '.'){
      aux++;
      continue;
    }else{
      return -1;
    }
  }

  return aux;
}

const int Board::checkBoardV(const string &wrd, const int &r, const int &c){
  int aux = r;
  for(int i = 0; i < wrd.size(); i++){
    if(board[aux][c] == wrd.at(i) || board[aux][c] == '#' || board[aux][c] == '.'){
      aux++;
      continue;
    }else{
      return -1;
    }
  }

  return aux;
}
