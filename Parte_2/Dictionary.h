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
    Dictionary(const string &fileName);

    /*	Checks if word belongs to Dictionary
     * makes all the words uppercase
     */
    bool isValid(string &str) const;

    /*	Gives hints for cwcreator
     */
    vector<string> searchWords(const string &str);

    /*	Gives hints for cwplayer
     */
    const string getHint(const string &wrd);
  private:
    multimap<string, string> words;
    vector<string> keys;                              // Necessary to reutilize wildacrdMatch
    int ltrFreq[26];                                  // From first program
};

#endif
