#ifndef GYM_H
#define GYM_H
#include "ownable.h" 
using namespace std; 


class Gym: public Ownable{ 
	public:
	
	Gym(string name);  // constructor, purchcost = 150, imrovecost = 0, tuition varies, no bulding, no block, 
	//~Gym();	// destructor
	//int rent();	// how much rent is owed when someone lands on property

};

#endif 
