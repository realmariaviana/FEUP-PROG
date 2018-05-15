#include <iostream>
#include <string>
#include <limits>

#include "Puzzle.h"
#include "ColorText.h"

using namespace std;

void printInit();
Puzzle* printMenu();
Puzzle* invalidMenuOption();
Puzzle* createPuzzle();
Puzzle* resumePuzzle();
const bool isComplete();

int main(){
  printInit();

  Puzzle *pz;
  string fileName;

  pz = printMenu();

  pz -> userIn();

  if(isComplete()){
    pz -> cleanBoard();
    fileName = pz -> saveToFile();
  }else{
    fileName = pz -> saveToFile();
  }

  cout << "Crossword puzzle saved to file " << fileName << endl;

  delete(pz);

  return 0;
}

const bool invalidIsCompleteOption(){
  if(cin.fail()){
    cout << endl << "Invalid option detected. Trt agian" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return isComplete();
  }else{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');;

    return isComplete();
  }
}

const bool isComplete(){
  cout << "Is the puzzle complete? [Y / N] ? ";
  char options;

  cin >> options;

  switch (options) {
    case 'Y':
    case 'y':
      return true;
    case 'N':
    case 'n':
      return false;
    default:
      return invalidIsCompleteOption();
  }
}

Puzzle* resumePuzzle() {
  cout << endl << endl;
  cout << "Crossword puzzle file ? " << endl;
  string fileName;
  cin >> fileName;

  Puzzle *pz;

  pz = new Puzzle(fileName);

  return pz;
}

Puzzle* createPuzzle(){
  string fileName;
  int row, column;

  cout << endl;
  cout << "Dictionary file name ? ";
  cin >> fileName;
  cout << "Board size (lines columns) ? ";
  cin >> row >> column;
  cout << endl;

  Puzzle *pz;
  pz = new Puzzle(fileName, row, column);

  return pz;
}

Puzzle* invalidMenuOption(){
  if(cin.fail()){
    cout << endl << "Invalid option detected. Trt agian" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return printMenu();
  }else{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');;

    return printMenu();
  }
}

Puzzle* printMenu(){
  cout << "Options: " << endl;
  cout << "1. Create Puzzle" << endl;
  cout << "2. Resume Puzzle" << endl;
  cout << "0. Exit" << endl;

  int options = -1;

  while(!cin.fail()){
    cout << "Option ? ";
    cin >> options;

    switch (options) {
      case 0:
        cout << "Closing the program..." << endl;
        exit(0);
      case 1:
        return createPuzzle();
        break;
      case 2:
        return resumePuzzle();
        break;
      default:
        return invalidMenuOption();
    }
  }
  return 0;
}

void printInit(){
  cout << endl << endl;
  cout << "CROSSWORDS PUZZLE CREATOR" << endl;
  cout << "==========================" << endl << endl;
  cout << "Instructions: " << endl;
  cout << "- Position ( LCD / CTRL-D = stop)" << endl;
  cout << "- LCD stands for Line Column and Direction" << endl;
  cout << "- Line must be in uppercase, column lowecase and Direction in uppercase" << endl;
  cout << "? does not work yet" << endl;
  cout << endl;
}
