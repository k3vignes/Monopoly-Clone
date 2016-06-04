#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <sstream>
using namespace std;

class View {
  public:
  char board[67][122]; 
  string prop[40]; 
  bool isOwnable[40]; 

 
 View();
 void print(std::ostream &out);
 void init(string name, bool ownable); 
 void removePlayer(int square, char symbol, int playerId);
 void updateBuilding(int square, int buildingSize);
 void updateOwner(int square, char symbol, string monopolyBlock);
 void updatePlayer(int oldLoc, int newLoc, int playerId, char symbol);
 int locateWidthSqr(int loc);
 int locateHeightSqr(int loc);
};

#endif
