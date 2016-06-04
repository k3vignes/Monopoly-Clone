#include "osap.h"
using namespace std;

OSAP::OSAP(string name){
	this->name = name; 
	this->isOwnable = false; 
}

void OSAP::specialty(Player *p){
  cout << "Landed on OSAP, collected $200" << endl;
}
