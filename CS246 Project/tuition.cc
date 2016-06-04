#include "tuition.h"
#include <iostream>
using namespace std;

Tuition::Tuition(string name){
	this->name = name;
	this->isOwnable = false;
}

void Tuition::specialty(Player * p){
  cout << "Landed on Tuition, pay $300 or 10% of your total networth" << endl;
  cout << "Type 300 or 10nw" << endl;
  bool done = false;
  string cmd;
  while(!done){
    cin >> cmd;
	  if(cmd == "300"){
		  cout << "old amount of money: " << p->money << endl;
		  p->pay(NULL, 300);
			cout << "paid 300 new player's money: " << p->money << endl;
	    done = true;
	  }
	  else if(cmd == "10nw"){
		  int rent = p->netWorth()/10;
			cout << "old amount of money: " << p->money << endl;
		  p->pay(NULL, rent);
			cout << "paid " << rent << "new player's money: " << p->money << endl;
	    done = true;
    }
  }
}
