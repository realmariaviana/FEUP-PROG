#include "Board.h"

using namespace std;

Board::Board(int colum, int row){
  this->row = row;
  this->colum = colum;

  board = new  char *[row];

  for(int i = 0; i < row; i++){
    board[i] = new char [colum];
  }

  for(int i = 0; i < colum; i++){
    for(int j = 0; j < row; j++){
      board[i][j] = '.';
    }
  }
}

Board::~Board(){
  for(int i = 0; i < row; i++){
    delete [] board[i];
  }
  delete [] board;
}

void Board::drawBoardEmpty(){
  char ltrC = 'a';
  char ltrR = 'A';

  setcolor(RED);
  cout << setw(3) << ltrC++ << ' ';
  for(int i = 0; i < colum-1; i++) cout << ltrC++ << ' ';
  cout << endl;
  setcolor(NO_COLOR);

  for(int i = 0; i < colum; i++){
    cout << RED << ltrR++;
    for(int j = 0; j < row; j++){
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
  cout << setw(3) << ltrC++ << ' ';
  for(int i = 0; i < colum-1; i++) cout << ltrC++ << ' ';
  cout << endl;
  setcolor(NO_COLOR);

  for(int i = 0; i < colum; i++){
    cout << RED << ltrR++;
    for(int j = 0; j < row; j++){
      setcolor(BLACK, WHITE_B);
      cout << setw(2) << board[i][j];
    }
    setcolor(NO_COLOR);
    cout << endl;
  }
}

const int Board::checkBoardH(const string &wrd, const int &r, const int &c){
  int aux = c;
  for(int i = 0; i < wrd.size(); i++){
    if(board[r][aux] == wrd.at(i) || board[r][aux] == '#' || board[r][aux] == '.'){
      aux++;
      continue;
    }else{
      return i + c;
    }
  }

  return -1;
}

const int Board::checkBoardV(const string &wrd, const int &r, const int &c){
  int aux = r;
  for(int i = 0; i < wrd.size(); i++){
    if(board[aux][c] == wrd.at(i) || board[aux][c] == '#' || board[aux][c] == '.'){
      aux++;
      continue;
    }else{
      return i + r;
    }
  }

  return -1;
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

const bool Board::insertWord(const string &wrd, const char &init,const char &end,const char &ori){
  int r = LTR_TO_INT(init);
  int c = ltr_TO_INT(end);

  int maxSpace, ret;
  if(ori == 'V'){
    maxSpace = colum - c;
    ret = checkBoardV(wrd, r, c);
  }else{
    maxSpace = row - r;
    ret = checkBoardH(wrd, r, c);
  }

  if(maxSpace < wrd.size()){
    cout << "Word does not fit, not enough space" << endl;
    return false;
  }

  if(ret != -1){
    //cout << "Incompatible letter at " << ret << endl;       //Needs refining
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
