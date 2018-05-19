#include <iostream>

#include "Player.h"

using namespace std;

void printInit();

int main(){
  //srand(time(NUll));

  printInit();

  string fileName, name;

  cout << "Crossword Puzzle file ? ";
  cin >> fileName;

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Player name ? ";
  getline(cin, name);
  trimString(name);

  cout << endl << endl;

  Player *py;

  py = new Player(fileName, name);

  py -> userIn();

  if(py -> isWinner()){
    cout << endl << "Your solution was correct!!!" << endl;
  }else{
    cout << endl << "Your solution was incorrect :(" << endl;
  }

  cout << "Information saved on: " << py -> writeToFile() << endl << endl;

  return 0;
}

void printInit(){
  cout << endl << endl;
  cout << "CROSSWORDS PUZZLE PLAYER" << endl;
  cout << "==========================" << endl << endl;
  cout << "Instructions: " << endl;
  cout << "- Position ( LCD / CTRL-D = stop)" << endl;
  cout << "- LCD stands for Line Column and Direction" << endl;
  cout << "- Line must be in uppercase, column lowecase and Direction in uppercase" << endl;
  cout << endl;
}
