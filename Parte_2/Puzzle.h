#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

#include "MyUtils.h"
#include "Dictionary.h"
#include "Board.h"

using namespace std;

class Puzzle{
  public:
    Puzzle(const string &f_dictionary, const int &row, const int &column);
    Puzzle(const string &f_in);
    Puzzle(Dictionary *dc, Board *bd);
    ~Puzzle();

    /*	Handles all the user inputs
     */
    void userIn(int &n);

    /*	Finishes board
     * Makes all the dot cells as
     * # also known as black cells
     */
    void cleanBoard();

    /*	Saves puzzle to file
     */
    const string saveToFile();

    /*	Writes fo file
     */
    void writeToFileB(ofstream &F);

    /* Adds hints to puzzle
     */
    void addHintMap(const string &key, const string &val);
    vector<string> getInstructions();

  private:
    Dictionary *dc;
    Board *bd;

    string fileDictionary;
    string filePuzzle;
    bool newBoard;
    bool fileName;
    bool hintM;

    map<string, string> instructions;
    map<string, string> hintMap;

    /*	Handles hint according to position
     */
    const bool userInPos(string &inPos);

    /*	Handles user input word
     */
    const int checkInWrd(string &a);

    /*	Handles user input word
     */
    const int userInWrd(string &inWrd);

    /*	Handles user input position
     */
    const string getHintP(const string &coord);
};

#endif
