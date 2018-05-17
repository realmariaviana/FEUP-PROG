#include <iostream>

#include "Player.h"

using namespace std;

int main(){
  Player *py;
  cout << "main b" << endl;
  py = new Player("b002.txt", "Simao");
  cout << "main a" << endl;
  return 0;
}
