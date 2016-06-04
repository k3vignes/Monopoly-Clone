#ifndef BUILDING_H
#define BUILDING_H
#include "ownable.h"
#include "property.h"
#include "player.h"
#include <iostream> 

using namespace std; 

class Building: public Ownable{ 
	public:
	
	Building(int purchCost, int improveCost, int t[], string monopolyBlock, string name);  // constructor
	//~Building();	// destructor
	int rent();	// how much rent is owed when someone lands on property
	void improve(Player *p);
	void unimprove(Player *p);

};

#endif 
