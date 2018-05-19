#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>

#include "ColorText.h"

#define LTR_TO_INT(n) n - 65
#define ltr_TO_INT(n) n - 97

using namespace std;

class Board {
  public:
    Board(int row, int column);
    Board(const string &line);
    Board(const string &line, const bool &flag);

    /*	Empty board for the
     * first iteration program
     */
    void drawBoardEmpty();

    /*	Current board displaying words
     * as they are entered
     */
    void drawBoardCurrent();

    /* Insert word depending of direction
     * and handler for invalid inputs
     */
    const bool insertWord(const string &wrd,const char &init,const char &end,const char &ori);

    /*	Deletes word from board
     * depending on the direction
     */
    const string deleteWord(const char &init, const char &end, const char &ori);

    /* Makes all the dot cells as
     * # also known as black cells
     */
    void finishBoard();

    /*	Adds line to board */
    void addLine(const string &line);

    /*	Adds line to board */
    void addLine(const string &line, const bool &flag);

    /*	Writes board to file  */
    void writeToFile(ofstream &F);

    const string getWord(const char &init, const char &end, const char &ori);
  private:
    vector< vector<char> > board;
    int row, column;

    /*	Checks if board is capable
     * to insert word vertically
     */
    const int checkBoardV(const string &wrd, const int &r, const int &c);

    /*	Checks if board is capable
     * to insert word horizontally
     */
    const int checkBoardH(const string &wrd, const int &r, const int &c);

    /*	Inserts word to board
     * vertically
     */
    void insertWordV(const string &wrd, const int &r, const int &c);

    /*	Inserts word to board
     * horizontally
     */
    void insertWordH(const string &wrd, const int &r, const int &c);

    /*	Deletes word
     * vertically
     */
    const string deleteWordV(const int &r, const int &c);

    /*	Deletes word
     * horizontally
     */
    const string deleteWordH(const int &r, const int &c);

    /*	Checks if either a dot or a #
     * is in the sorrounding cells
     * horizontally
     */
    const bool checkSurrondingsH(const int &r, const int &c);

    /*	Checks if either a dot or a #
     * is in the sorrounding cells
     * vertically
     */
    const bool checkSurrondingsV(const int &r, const int &c);
    const string getWordV(const int &r, const int &c);
    const string getWordH(const int &r, const int &c);
};

#endif
