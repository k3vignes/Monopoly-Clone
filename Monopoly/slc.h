#ifndef SLC_H
#define SLC_H
#include "unownable.h"
#include "player.h"
#include "PRNG.h"
using namespace std;

class SLC: public Unownable{ 
	public:
	PRNG prng;

	SLC(string name); // constructor
	//~SLC(); // destructor 
	
	void specialty(Player *p); // when player lands on this square they are moved randomly to another square
};

#endif 
