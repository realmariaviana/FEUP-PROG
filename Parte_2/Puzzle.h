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
     *  Counter for the number of hints the user asks
     */
    void userIn(int &n);

    /*	Finishes board makes all the dot cells as # also known as black cells
     */
    void cleanBoard();

    /*	Saves puzzle to file
     */
    const string saveToFile();

    /*	Writes fo file
     */
    void writeToFileB(ofstream &F);

    /* Populates hintMap to be used on cwplayer
     */
    void addHintMap(const string &key, const string &val);

    /* Converts instructions to a vector making it easier to compare
     */
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

    /* Handles user input to coordinates, making sure the input is valid
     * returns true when it detects a CTRL-D
     */
    const bool userInPos(string &inPos);

    /*	Handles user input word making sure it is present on the dictionary
     */
    const int checkInWrd(string &a);

    /*	Handles user input word
     */
    const int userInWrd(string &inWrd);

    /* Given a coordinate it returns the val in hintMap
     */
    const string getHintP(const string &coord);
};

#endif
