#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(const string &fileName){
  ifstream f_in;

  openFile(fileName, f_in);

  string line;
  string ky;

  getline(f_in, line);
  trimString(line);
  ky = checkLine(line, words);
  keys.push_back(ky);

  while(!f_in.eof()){
    getline(f_in, line);
    trimString(line);
    ky = checkLine(line, words);
    keys.push_back(ky);
  }

  sortVector(keys);

  for(int i = 0; i < 26; i++) ltrFreq[i] = 0;

  char ltr = 'a';
  int n = 0;

  for(size_t i = 0; i < ky.size(); i++){
    if(keys[i].at(0) != ltr){
      for(int j = n+1; j < 26; j++){
        ltrFreq[j] += ltrFreq[n];
      }
      ltr++;
      n++;
    }else{
      ltrFreq[n]++;
    }
  }
}

bool Dictionary::isValid(string &str) const{
  makeUpper(str);
  return searchVector(keys, str);
}

void calcInt(int &init, int &end, char ltr, int *ltrFreq){
  init = end = 0;

  if(ltr == 'A'){
    end = ltrFreq[0];
    return;
  }

  int pos = POS_LETTER((int)ltr);

  init = ltrFreq[pos -1] +1;
  end = init + ltrFreq[pos];
}

vector<string> Dictionary::searchWords(const string &str){
  vector<string> ret;

  int init = 0, end = keys.size();
  int pos = 0;
  char ltr;

  if (str.at(0) != '?') {
    calcInt(init, end, str.at(0), ltrFreq);
    pos = str.find_first_of('?', 1);
    pos ++;
    ltr = str.at(pos);
  } else {
    pos = str.find_first_of('?');
    pos ++;
    ltr = str.at(pos);
  }

  for(int i = init; i < end; i++){
    string aux = keys.at(i);

    if(aux.at(pos) == ltr){
      if (wildcardMatch(aux.c_str(), str.c_str()) ) ret.push_back(aux);
    }
  }

  return ret;
}

const string Dictionary::getHint(const string &wrd){
  string aux = wrd;
  makeUpper(aux);

  pair< MMiterator, MMiterator > ret;
  ret = words.equal_range(aux);

  int max = distance(ret.first, ret.second);
  if(max == 0) return "No more hints";
  int pos = rand() % max;

  MMiterator it = ret.first;

  //for(it = ret.first, int i = 0; i< max; i++, it++);
  for(int i = 0; i < pos; i++) it++;
  aux = it -> second;
  words.erase(it);
  return aux;
}
