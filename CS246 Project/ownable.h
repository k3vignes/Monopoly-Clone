#ifndef OWNABLE_H
#define OWNABLE_H
#include "property.h"

class Player;

using namespace std;

class Ownable: public Property{
	public:

	int owner;		// which player owns the property, -1, if none
	int purchCost; 	// how much to buy the property
	int improveCost; 	// how much for the next improvement
	int tuition[6];	// amount of tuition for current level of buildingsize
	int buildingSize;	// the current size of the building on the property
	bool mortgaged; 	// whether or not the property is mortgaged
	string monopolyBlock; // which block does it belong to, eg; Math or Arts

	Ownable();
	//virtual ~Ownable(); 	// destructor
	virtual void setOwnership(Player *p); // sets the ownership of property to given player
	void transferOwnership(Player *p);
	virtual bool checkMortgaged();	// checks if property is mortgaged
	virtual int rent();	// how much rent is owed when someone lands on property
	void mortgage(Player *p);
	void unmortgage(Player *p);
	void setBuildingSize(int n);
	int value();
	void auction(Player *p, int bid);
	void bankruptTransfer(Player *p);

};

#endif
