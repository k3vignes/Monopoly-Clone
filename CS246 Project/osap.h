#ifndef OSAP_H
#define OSAP_H
#include "unownable.h" 
using namespace std;

class OSAP: public Unownable{ 
	public:

	OSAP(string name); // constructor
	//~OSAP(); // destructor 
	
	void specialty(Player *p); // when player lands on this square they collect $200
};

#endif 
