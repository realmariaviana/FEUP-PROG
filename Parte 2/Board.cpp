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
      cout << setw(2) << ".";
    }
    setcolor(NO_COLOR);
    cout << endl;
  }
}

bool Board::insertWord(const string &wrd, const char &init,const char &end,const char &ori) const{
  int r = LTR_TO_INT(init);
  int c = LTR_TO_INT(end);

}
