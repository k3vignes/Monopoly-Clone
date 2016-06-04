#include "needleshall.h"
using namespace std;

NeedlesHall::NeedlesHall(string name){
	this->name = name;
	this->isOwnable = false;
	prng = PRNG(9);
}

void NeedlesHall::specialty(Player *p){
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

  n = prng(1,36);
  if(n<=2){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall -200" << endl;
    p->pay(NULL,200);
		cout << "new amount of money: " << p->money << endl;
  }
  else if(n<=6){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall -100" << endl;
    p->pay(NULL,100);
		cout << "new amount of money: " << p->money << endl;
  }
  else if(n<=12){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall -50" << endl;
    p->pay(NULL,50);
		cout << "new amount of money: " << p->money << endl;
  }
  else if(n<=24){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall 25" << endl;
    p->money += 25;
		cout << "new amount of money: " << p->money << endl;
  }
  else if(n<=30){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall +50" << endl;
    p->money += 50;
		cout << "new amount of money: " << p->money << endl;
  }
  else if(n<=34){
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall +100" << endl;
    p->money += 100;
		cout << "new amount of money: " << p->money << endl;cout << "new amount of money: " << p->money << endl;
  }
  else{
		cout << "old amount of money: " << p->money << endl;
    cout << "NeedlesHall +200" << endl;
    p->money += 200;
		cout << "new amount of money: " << p->money << endl;
  }
}
