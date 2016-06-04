#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "ownable.h" 
using namespace std;

class Residence: public Ownable{ 
	public:
	
	Residence(string name);  // constructor, purchCost = 200, improveCost = 0, tuition varies, buildinsize = 0, no Block)
	//~Residence();	// destructor
	//int rent();	// how much rent is owed when someone lands on property

};

#endif 
