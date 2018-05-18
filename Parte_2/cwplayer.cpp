#include <iostream>

#include "Player.h"

using namespace std;

int main(){
  Player *py;
  //srand(time(NUll));
  py = new Player("b002.txt", "Simao");

  py -> userIn();

  py -> writeToFile();

  return 0;
}
