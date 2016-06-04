#include "residence.h" 
#include <iostream> 
using namespace std;

Residence::Residence(string name){ 
	this->purchCost = 200;
	this->improveCost = 0;
	//this->tuition = NULL;
	for (int i =0; i < 6; i++) { 
		this->tuition[i] = 0; 
	}
	this->buildingSize = 0;
	this->monopolyBlock = "Residence";
	this->name = name;
	this->isOwnable = true; 
	this->owner = -1; 
}



