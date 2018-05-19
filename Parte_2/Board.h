#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>

#include "ColorText.h"

#define LTR_TO_INT(n) n - 65           //Calculates the row given the letter in caps
#define ltr_TO_INT(n) n - 97           //Calculates the column given the letter

using namespace std;

class Board {
  public:
    //Constructor: given the number of rows and columns
    Board(int row, int column);

    //Constructor: given a line of an existing board
    Board(const string &line);
    Board(const string &line, const bool &flag);

    /*  Empty board for the first iteration of cwcreator
     */
    void drawBoardEmpty();

    /*  Current board displaying words as they are entered
     */
    void drawBoardCurrent();

    /* Insert word depending of direction, it also handles invalid inputs
     * wrd string to be entered on the Board
     * init Line
     * end Column
     * ori orientation, vertical or horizontal
     */
    const bool insertWord(const string &wrd,const char &init,const char &end,const char &ori);

    /*	Deletes word from board depending on the direction
     *  init Line
     *  end Column
     * ori orientation, vertical ou horizontal
     */
    const string deleteWord(const char &init, const char &end, const char &ori);

    /* Makes all the dot cells as # also known as black cells
     */
    void finishBoard();

    /*	Adds line to board
     *  used in cwcreator to resume a board, from a file
     *  line string containing a line of the board
     */
    void addLine(const string &line);

    /*	Adds line to board
     * used in cwplayer to initiate board[][] and not read any letters
     *  line string containing a line of the board
     */
    void addLine(const string &line, const bool &flag);

    /*	Writes board to file
     *  F ofstream passed by reference
     */
    void writeToFile(ofstream &F);

    /* Gets word in board starting on the given coords and goind all the way to the
     * end of the row or column
     *  init Line
     *  end Column
     * ori orientation, vertical ou horizontal
     */
    const string getWord(const char &init, const char &end, const char &ori);
  private:
    vector< vector<char> > board;
    int row, column;

    /*	Checks if board vertically if its possible to insert the word
     *  wrd to check if existing letters match the word being inserted
     *  r Line
     *  c Column
     */
    const int checkBoardV(const string &wrd, const int &r, const int &c);

    /*	Checks if board horizontally if its possible to insert the word
     *  wrd to check if existing letters match the word being inserted
     *  r Line
     *  c Column
     */
    const int checkBoardH(const string &wrd, const int &r, const int &c);

    /*	Inserts word to board vertically
     * wrd passed by reference
     *  r Line
     *  c Column
     */
    void insertWordV(const string &wrd, const int &r, const int &c);

    /*	Inserts word to board horizontally
     *  r Line
     *  c Column
     */
    void insertWordH(const string &wrd, const int &r, const int &c);

    /*	Deletes word vertically
     *  r Line
     *  c Column
     * returns word deleted
     */
    const string deleteWordV(const int &r, const int &c);

    /*	Deletes word horizontally
     *  r Line
     *  c Column
     * returns word deleted
     */
    const string deleteWordH(const int &r, const int &c);

    /*	Checks if either a dot or a # is in the sorrounding cells vertically
     *  as to not mess up existing words on the when something is deleted
     *  r Line
     *  c Column
     */
    const bool checkSurrondingsV(const int &r, const int &c);

    /*	Checks if either a dot or a # is in the sorrounding cells horizontally
     *  as to not mess up existing words on the board when something is deleted
     *  r Line
     *  c Column
     */
    const bool checkSurrondingsH(const int &r, const int &c);

    /* Returns word written vertically on the board
    *  r Line
    *  c Column
    */
    const string getWordV(const int &r, const int &c);

    /* Returns word written horizontally on the board
    *  r Line
    *  c Column
    */
    const string getWordH(const int &r, const int &c);
};

#endif
