#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "unownable.h"
#include "player.h"
#include "PRNG.h"
using namespace std;

class NeedlesHall: public Unownable{ 
	public:
	PRNG prng;

	NeedlesHall(string name); // constructor
	//~NeedlesHall(); // destructor 
	
	void specialty(Player *p); // when player lands on this square they lose or gain some amount of money
};

#endif 
