#include "ownable.h"
#include <iostream>
#include "player.h"
using namespace std;

Ownable::Ownable(){
  mortgaged = false;
}

void Ownable::setOwnership(Player *p){
	this->owner = p->id;
	p->money -= this->purchCost;
	p->addProperty(this);
}

void Ownable::transferOwnership(Player *p){
		this->owner = p->id;
		p->addProperty(this);
}

int Ownable::rent(){}

bool Ownable::checkMortgaged(){
  return mortgaged;
}

void Ownable::mortgage(Player *p){
  if(this->owner == p->id && this->buildingSize == 0 && !this->checkMortgaged()){
    p->money += purchCost/2;
	  mortgaged = true;
	  cout << "mortgaged, got: " << purchCost/2 << endl;
  }
  else{
    cout << "unsuccesssful mortgage" << endl;
  }
}

void Ownable::unmortgage(Player *p){
  if(this->checkMortgaged() && this->owner == p->id){
    p->money -= purchCost * 6 / 10;
	mortgaged = false;
	cout << "unmortgaged, spent: " << purchCost *6/10 << endl;
  }
}

void Ownable::setBuildingSize(int n){
	this->buildingSize = n;
}

int Ownable::value(){
	int val = this->purchCost;
	if(this->mortgaged)
	  return val/2;
	for(int i=0;i<buildingSize;i++){
		val += improveCost;
	}
	return val;
}

void Ownable::auction(Player *p, int bid){
  cout << "old player money: " << p->money << endl;
	p->money -= bid;
	cout << "new player money: " << p->money << endl;
	this->owner = p->id;
	p->addProperty(this);
}

void Ownable::bankruptTransfer(Player *p){
		this->owner = p->id;
		p->addProperty(this);
		if(this->mortgaged){
			p->money -= this->purchCost/10;
			cout << "received mortgaged property, paid 10% of purchCost: " << this->name << " cost: " << this->purchCost/10 << endl;
		  cout << "immediately unmortgage? y/n" << endl;
			string cmd;
			cin >> cmd;
			if(cmd == "y"){
				this->mortgaged = false;
				p->money -= this->purchCost/2;
        cout << "paid to unmortgage property: " << this->purchCost/2 << endl;
        cout << "new balance: " << p->money << endl;
			}
		}
}
