#ifndef PLAYER_H
#define PLAYER_H
#include "property.h"
#include "ownable.h"
#include <map>
using namespace std;

class Game;

class Player{
	public:

	int id; //id of the player
	int money;			// how much money a player has
	static int rollUpRim [8];		// list of who has roll up rim and who doesn't
	string name; 			// name of the player
	char symbol; 			// the symbol representing a player
	int location; 		// location of the piece on the board
	int jail; 			// number of turns in jail, -1 if not in jail
	bool isBankrupt;
	Player* playerOwing; // NULL of noone or bank;
	int oweAmnt; //amnt owing
	map<string, Ownable *> prop;
	Game *game;

	Player(string n, char sym, Game* g); // constructor
	Player(string n, char sym, Game * g, int timCards, int m, int loc, int j, int id);
	void move(int die1, int die2); // moves the players a given number of spaces
	void setID(int n);  // sets the id for the player
	void setPos(int pos, bool collectable); // set players location
	void declareBankruptcy(); // player is out of the game
	bool availTimsCard(); //checks if theres an available rollUpRim to be distributed
	void addProperty(Ownable *op);
	void removeProperty(string name);
	void assets();
	int netWorth();
	void bankrupt();
	void transferAll(Player *p);
	void bankBankrupt();
	bool moneyOwing();
	void setOwing(Player *p, int amnt);
	void payDebts(); //pays back debts, if possible
	void pay(Player *p, int amnt);
	bool owesMoney();

};

#endif
