#ifndef DICTIONART_H_
#define DICTIONART_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iterator>
#include <cstdlib>

#include "MyUtils.h"

#define NUM_OPT 3

using namespace std;

typedef multimap<string, string>::iterator MMiterator;

class Dictionary{
  public:
    //Constructor: given the name of the file containg the words
    Dictionary(const string &fileName);

    /*	Checks if word belongs to Dictionary
     *  str word to the checked
     *  returns true if word exists in keys false otherwise
     */
    bool isValid(string &str) const;

    /*	Using the wildcardMatch() from the 1st project
     *  It gives options of words that fit a given space
     *  It also makes sure the size is correct
     *  returns a vector containg NUM_OPT of options that can fit the space
     */
    vector<string> searchWords(const string &str);

    /*	Gives hints to the user by going through words and picking a random one
     *  wrd key stored in words needed to access val that contains the synonims
     *  returns a possible hint
     */
    const string getHint(const string &wrd);
  private:
    multimap<string, string> words;

    //Needed to reutilize wildcardMatch()
    vector<string> keys;
    int ltrFreq[26];


    /* Handles a line from the file, inserting them in the multimap
     * str line
     * returns 1st word in line aka key
     */
    const string checkLine(const string &str);
};

#endif
