#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include "unownable.h" 
#include "player.h"
using namespace std; 

class GooseNesting: public Unownable{ 
	public:

	GooseNesting(string name); // constructor
	//~GooseNesting(); // destructor 
	
	void specialty(Player * p); // when player lands on this square nothing happens
};

#endif 
