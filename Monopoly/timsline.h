#ifndef TIMSLINE_H
#define TIMSLINE_H
#include "unownable.h"
#include "player.h"
using namespace std;

class TimsLine: public Unownable{ 
	public:

	TimsLine(string name); // constructor
	//~TimsLine(); // destructor 
	
	void specialty(Player *p); // nothing happens if player lands here, if player sent here can't get out unless... (read specs pdf)
};

#endif 
