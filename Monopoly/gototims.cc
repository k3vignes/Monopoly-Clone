#include "gototims.h"
#include <iostream>
using namespace std;


GoToTims::GoToTims(string name){
	this->name = name;
	this->isOwnable = false;
}

void GoToTims::specialty(Player *p){
	cout << "goto tims" << endl;
	p->location = 10;
	p->jail = 0;
}
