#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include "property.h"
#include "player.h"
#include "PRNG.h"
#include <list>
using namespace std;

/*
 * Abstract class to allow Game to send noticiations to a registered object
 */
class Controller;

class Game {
  public:
  PRNG prng;  // random number for dice
  Property *board[40];  // The board
  Player* players[9]; // The players
  int currPlayer; // Current player's turn
  int numPlayers;  // Number of players in the game
  int doubles; // number of times player rolled doubles;
  bool canRoll;

  Controller *notification;  // object registered for notifications


  Game();
  //~Game();

  void init(Controller *gameNotification); //dne
  void makePlayer(string name, char symbol); //done
  //bool checkPieceAvail(char symbol);
  void save(string filename);
  string intToStr(int n);
  string savePlayers();
  string saveProperties();
  void load(string filename);
  void loadPlayers(ifstream &file);
  void loadProperties(ifstream &file);
  //void testingMode();
  void mortgage(string propName);
  void unmortgage(string propName);
  bool isOwnable(Property *prop);
  int findProperty(string name);    //done
  void roll(); //done
  void roll(int die1, int die2);
  void next(); //done
  void improve(string propName);
  void unimprove(string propName);
  bool checkOwned(Property* property);  //done
  void checkLandingPos(int propIndex, int die1, int die2);		// done
  void buy();
  bool gameWon();   //done
  void setPosition(int i); //done
  void addPlayer(string name, char piece); //dne
  void payRent(int die1, int die2);
  bool isMonopoly(int propIndex);
  int findPlayerIndex(string name);
  Player *findPlayer(string pname);
  void trade(string pname, string str1, string str2);
  void listAssets();
  void canAuction();
  void auction(Ownable *op);
  void bankrupt();
  void bankrupt(Player *p);
  void bankBankrupt();
  void gameUpdate(string name, char sym, string monopolyBlock);
  bool inList(list <int> index, int n);
  void addTims(string name);
  void useTims();
  void payTims();
  bool emptyMonopoly(int propIndex);
};

#endif
