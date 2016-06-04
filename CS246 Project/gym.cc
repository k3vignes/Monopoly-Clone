#include "gym.h"
#include <iostream>
using namespace std; 

Gym::Gym(string name){ 
	this->purchCost = 150;
	this->improveCost = 0;
	//this->tuition = NULL;
	for (int i =0; i < 6; i++) { 
		this->tuition[i] = 0; 
	}
	this->buildingSize = 0;
	this->monopolyBlock = "Gym";
	this->name = name;
	this->isOwnable = true;
	this->owner = -1;  
}

	
	
