#ifndef TUITION_H
#define TUITION_H
#include "unownable.h"
#include "player.h"
using namespace std;

class Tuition: public Unownable{ 
	public:

	Tuition(string name); // constructor
	//~Tuition(); // destructor 
	
	void specialty(Player *p); // when player lands on this square they pay money to bank
};

#endif 
