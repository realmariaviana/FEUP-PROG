#include <iostream>
#include <string>
#include<sstream>

#include "Puzzle.h"

//#include "Board.h"
//#include "MyUtils.h"
//#include "Dictionary.h"

using namespace std;

//void userInterface();

int main(){
  cout << "CROSSWORDS PUZZLE CREATOR" << endl;
  cout << "==========================" << endl;
  cout << "Instructions: " << endl;
  cout << "Position ( LCD / CTRL-D = stop)" << endl;
  cout << "LCD stands for Line Column and Direction" << endl;
  cout << "Line must be in uppercase, column lowecase and Direction in uppercase" << endl;
  cout << endl;
  cout << "-----------------------" << endl;
  cout << "Options: " << endl;
  cout << "1) Create Puzzle" << endl;
  cout << "2) Resume Puzzle" << endl;
  cout << "0)  Exit" << endl;

  int options = -1;
  cin >> options;

  while(!cin.fail()){
    cin >> options;

    switch (options) {
      case 0:
        cout << "Closing the program..." << endl;
        exit(0);
      case 1:

        break;
      case 2:

        break;
      default:
        
    }
  }

  Puzzle pz("sinonimos.txt", 10, 10);
  pz.userIn();

  return 0;
}
/*void options_size(int &column, int & row ){
  cout << "Board size (lines columnns)? ";
  cin >> column;
  cin >> row;
}

bool options_words(Board *bd, Dictionary *d){
string position, word;
stringstream ss;
char line, column, direction;

cout << endl;
cout << "Position (LCD / CTRL-Z = stop)? ";
cin.ignore();
cin.clear();
getline(cin, position);

ss<<position;
ss>>line >>column >>direction; //read char by char from input

cout << "Word (- = remove / ? = help)? ";
cin >> word;
if(!d->isValid(word)){
cout <<"ERROR: The word does not belong to the dictionary" << endl;
return false;
}
bd->insertWord(word, line, column, direction);
return true;
}

void userInterface(){
  int input;
  Board *bd;
  Dictionary *d;
  int column, row;
  d = new Dictionary("sinonimos.txt");
  cout << endl << endl;
  cout << "CROSSWORDS PUZZLE CREATOR\n===========================================" << endl;
  cout << endl << "OPTIONS: \n1. Create puzzle\n2. Resume puzzle \n0. Exit" << endl << endl;
  cout << "Option? ";
  cin >> input;

    switch(input){

      case 1: options_size(column, row);
              bd= new Board(column, row);
              bd->drawBoardEmpty();
              if(options_words(bd, d))
              bd->drawBoardCurrent();
              break;
      case 2: //bd.resumeBoard();
              break;
      case 0: //bd.exit();
              break;
    }
}*/
