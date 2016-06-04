#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "unownable.h"
#include "player.h"
using namespace std; 

class GoToTims: public Unownable{ 
	public:

	GoToTims(string name); // constructor
	//~GoToTims(); // destructor 
	
	void specialty(Player *p); // player lands on this square they sent to tims linee
};

#endif 
