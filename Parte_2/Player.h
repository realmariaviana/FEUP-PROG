#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <sstream>
#include <vector>

#include "Board.h"
#include "Dictionary.h"
#include "Puzzle.h"
#include "MyUtils.h"

class Player{
  public:
    Player(const string &f_in, const string &name);
    ~Player();

    /*	Prints hint vertically
     * horizontally
     */
    void printHint();

    /*	Handles all the user inputs
     */
    void userIn();

    /*	Writes to file player name,
     * time and number of clues given
     */
    const string writeToFile();
    const bool isWinner();
  private:
    Dictionary *dc;
    Board *bd;
    Puzzle *pz;

    string name;
    time_t init, end;
    int numHelp;
    string fileName;

    map<string, string> sol;
    vector<string> hintH;
    vector<string> hintV;

    vector<string> solToVec();
};

#endif
