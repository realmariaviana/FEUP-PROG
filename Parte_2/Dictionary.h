#ifndef DICTIONART_H_
#define DICTIONART_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "MyUtils.h"

class Dictionary{
  public:
    Dictionary(const string &fileName);
    bool isValid(string &str) const;
    vector<string> searchWords(const string &str);    //Methods to give hints
private:
    multimap<string, string> words;
    vector<string> keys;                              // Necessary to reutilize wildacrdMatch
    int ltrFreq[26];                                  // From first program
};

#endif
