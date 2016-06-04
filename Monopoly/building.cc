#include "building.h"
#include "ownable.h"
using namespace std;

Building::Building(int purchCost, int improveCost, int t[], string monopolyBlock, string name){
	this->purchCost = purchCost;
	this->improveCost = improveCost;
	for (int i = 0; i < 6; i++){
		this->tuition[i] = t[i];
	}
	this->monopolyBlock = monopolyBlock;
	this->buildingSize = 0;
	this->name = name;
	this->isOwnable = true;
	this->owner = -1;
}

void Building::improve(Player *p){
  if(!this->mortgaged && this->buildingSize < 5 && p->money >= this->improveCost){
   p->money -= this->improveCost;
   this->buildingSize++;
   cout << "improve to size: " << this->buildingSize << endl;
  }
	else if(p->money < this->improveCost){
   cout << "Not enough moeny to improve, cost: " << this->improveCost << " current balance " << p->money << endl;
	}
}

void Building::unimprove(Player *p){
  if(this->buildingSize > 0 && p->id == this->owner){
    this->buildingSize--;
	p->money += this->improveCost/2;
	cout << "unimprove to size: " << this->buildingSize << endl;
  }
}

int Building::rent(){
	return this->tuition[this->buildingSize];
}
