#include <iostream>
#include <string>
#include<sstream>

#include "Board.h"
#include "MyUtils.h"

using namespace std;

void userInterface();

int main(){
  /*Dictionary dt("synonyms.txt");


  pair<map<string, string> ::iterator, map<string, string> ::iterator> ret;
  ret = dt.words.equal_range("ABACK");

  for(multimap<string, string>::iterator it = ret.first; it != ret.second; ++it){
    cout << it->second << " ";
  }
  cout << endl;*/
  userInterface();

  //bd.insertWord("simao", 'A', 'a', 'H');
  //bd.drawBoardCurrent();

  //bd.insertWord("sofia", 'A', 'a', 'V');
  //bd.drawBoardCurrent();

  //bd.insertWord("afonso", 'A', 'F', 'H');
  //bd.drawBoardCurrent();

  return 0;
}
void options_size(int &column, int & row ){
  cout << "Board size (lines columnns)? ";
  cin >> column;
  cin >> row;
}

void options_words(Board *bd){
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
makeUpper(word);
bd->insertWord(word, line, column, direction);

}

void userInterface(){
  int input;
  Board *bd;
  int column, row;

  cout << endl << endl;
  cout << "CROSSWORDS PUZZLE CREATOR\n===========================================" << endl;
  cout << endl << "OPTIONS: \n1. Create puzzle\n2. Resume puzzle \n0. Exit" << endl << endl;
  cout << "Option? ";
  cin >> input;

    switch(input){

      case 1:options_size(column, row);
        bd= new Board(column, row);
        bd->drawBoardEmpty();
        options_words(bd);
        bd->drawBoardCurrent();
              break;
      case 2: //bd.resumeBoard();
              break;
      case 0: //bd.exit();
              break;
    }
}
