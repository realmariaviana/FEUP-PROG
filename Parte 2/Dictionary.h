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
    vector<string> searchWords(const string &str);
    //Methods to give hints
private:
    vector<string> keys;
    multimap<string, string> words;
    int ltrFreq[26];
};

#endif
