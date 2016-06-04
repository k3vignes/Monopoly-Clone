#ifndef UNOWNABLE_H
#define UNOWNABLE_H
#include "property.h" 
#include "player.h"
using namespace std;

class Unownable: public Property{ 
	public:

	//virtual ~Unownable();	// destructor
	virtual void specialty(Player *p) = 0; // what happens when you land on that property
};

#endif 
