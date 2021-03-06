#include "slc.h"
using namespace std;

SLC::SLC(string name){
	this->name = name;
	this->isOwnable = false;
	prng = PRNG(9);
}

void SLC::specialty(Player *p){
  int n;
  if(p->availTimsCard()){
    n = prng(1,100);
    if(n == 1){
	 cout << "won roll up rim" << endl;
	  p->rollUpRim[p->id] += 1;
		cout << p->name << "now has " << p->rollUpRim[p->id] << "rollUpRim's" << endl;
	  return;
	}
  }

  n = prng(1, 24);
  if(n<=3){
    //move 3 back
	cout << "move 3 back" << endl;
	p->move(0, -3);
  }
  else if(n<=7){
    //move 2 back
	cout << "move 2 back" << endl;
	p->move(0, -2);
  }
  else if(n<=11){
    //move 1 back
	cout << "move 1 back" << endl;
	p->move(0, -1);
  }
  else if(n<=14){
    // move 1 forward
	cout << "move 1 forward" << endl;
	p->move(0,1);
  }
  else if(n<=18){
    // move 2 forward
	cout << "move 2 forward" << endl;
	p->move(0,2);
  }
  else if(n<=22){
    // move 3 forward
	cout << "move 3 forward" << endl;
	p->move(0,3);
  }
  else if(n == 23){
    // goto dc tims line
	cout << "goto DC tims line" << endl;
	p->setPos(30, false);
  }
  else if(n == 24){
    // advance to OSAP
	cout << "goto OSAP" << endl;
	p->setPos(0, true);
  }
}
