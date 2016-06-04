#include "coopfee.h"
using namespace std;

CoopFee::CoopFee(string name){
	this->name = name;
	this->isOwnable = false;
}

void CoopFee::specialty(Player * p){
  cout << "Landed on pay coop fee, pay $150" << endl;
	p->pay(NULL, 150);
}
