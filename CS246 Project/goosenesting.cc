#include "goosenesting.h"
#include <iostream>
using namespace std; 

GooseNesting::GooseNesting(string name){
	this->name = name; 
	this->isOwnable = false; 
} 

void GooseNesting::specialty(Player * p){
	cout << "Landed on GooseNesting you got attacked by a flock of geese" << endl;
}
