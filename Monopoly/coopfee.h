#ifndef COOPFEE_H
#define COOPFEE_H
#include "unownable.h"
#include "player.h"
using namespace std; 

class CoopFee: public Unownable{ 
	public:

	CoopFee(string name); // constructor
	//~CoopFee(); // destructor 
	
	void specialty(Player * p); // when player lands on this square they pay $150 to bank
};

#endif 
