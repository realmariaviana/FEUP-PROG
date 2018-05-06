#include <iostream>
#include <string>

#include "Board.h"

using namespace std;

int main(){
  /*Dictionary dt("synonyms.txt");


  pair<map<string, string> ::iterator, map<string, string> ::iterator> ret;
  ret = dt.words.equal_range("ABACK");

  for(multimap<string, string>::iterator it = ret.first; it != ret.second; ++it){
    cout << it->second << " ";
  }
  cout << endl;*/

  Board bd(10, 10);
  bd.drawBoardEmpty();

  bd.insertWord("simao", 'A', 'a', 'H');
  bd.drawBoardCurrent();

  bd.insertWord("sofia", 'A', 'a', 'V');
  bd.drawBoardCurrent();

  bd.insertWord("afonso", 'A', 'F', 'H');
  bd.drawBoardCurrent();

  return 0;
}
