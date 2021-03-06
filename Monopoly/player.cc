#include "property.h"
#include "player.h"
#include "ownable.h"
#include "game.h"
#include "controller.h"
#include <iostream>
using namespace std;

int Player::rollUpRim[8] = {0,0,0,0,0,0,0,0};

Player::Player(string n, char sym, Game * g){
  id = -1;
  money = 1500;
  name = n;
  symbol = sym;
  location = 0;
  jail = -1;
  isBankrupt = false;
  game = g;
  oweAmnt = -2;
}

Player::Player(string n, char sym, Game * g, int timCards, int m, int loc, int j, int id){
  this->id = id;
  this->name = n;
  this->symbol = sym;
  this->game = g;
  rollUpRim[this->id] = timCards;
  this->money = m;
  this->location = loc;
  this->jail = j;
  this->oweAmnt = -2;
}

void Player::setID(int n){
	this->id = n;
}

void Player::move(int die1, int die2){
  int old = location;
  if(jail==2 && die1 != die2){
    string cmd;
    bool done = false;
    cout << "Didnt roll doubles, payTims or useTims to get out of jail" << endl;
    while(!done){
      cin >> cmd;
      if(cmd == "useTims"){
        game->useTims();
        done = true;
      }
      else if(cmd == "payTims"){
        this->pay(NULL, 50);
        done = true;
      }
      else{
        cout << "invalid input" << endl;
      }
    }
  }
  else if(jail > -1 && die1 != die2){
    jail++;
	  return;
  }
  else if(die1 == die2){
    jail = -1;
  }

  if(die1 + die2 > 40){
    this->money += 200 * (die1 + die2) / 40;
  }

  location = (location + die1 + die2) % 40;
  if(location < old){
    this->money += 200;
	  cout << "collected OSAP Money: " << this->money << endl;
  }
  game->checkLandingPos(location, die1, die2);
}

void Player::setPos(int pos, bool collectable){
  if(collectable && location >= pos){
    this->money += 200;
	  cout << "collected OSAP Money: " << this->money << endl;
  }

  location = pos;
  game->checkLandingPos(location, -1, -1);
}

bool Player::availTimsCard(){
  int c = 0;
  //check if available one
  for(int i=0;i<8;i++){
    c += rollUpRim[i];
  }

  bool result;
  (c<4) ? result = true : result = false;
  return result;
}

void Player::addProperty(Ownable *op){
  this->prop[op->name] = op;
  game->gameUpdate(op->name, this->symbol, op->monopolyBlock);
}

void Player::removeProperty(string name){
  this->prop.erase(name);
}

void Player::assets(){
  cout << this->name << "'s assets: $" << this->money << endl;
  cout << "Properties owned:" << endl;;
  typedef map<string, Ownable*>::iterator it;
  for(it iterator = this->prop.begin(); iterator != this->prop.end(); iterator++){
    cout << " " << iterator->second->name;
    if(iterator->second->mortgaged)
      cout << " mortgaged";
    cout << " improvements:  " << iterator->second->buildingSize << endl;
  }
  cout << endl;
  cout << "Tims cups: " << rollUpRim[this->id] << endl;
  cout << "Total net worth: " << this->netWorth() << endl;
}

int Player::netWorth(){
  int n = this->money;
  typedef map<string, Ownable*>::iterator it;
  for(it iterator = this->prop.begin(); iterator != this->prop.end(); iterator++){
    n += iterator->second->value();
  }
  return n;
}

void Player::bankrupt(){
  this->isBankrupt = true;
}

void Player::transferAll(Player *p){
  typedef map<string, Ownable*>::iterator it;
  for(it iterator = this->prop.begin(); iterator != this->prop.end(); iterator++){
    iterator->second->bankruptTransfer(p);
    this->game->notification->view->updateBuilding(this->game->findProperty(iterator->second->name), 0);
    this->game->gameUpdate(iterator->second->name, p->symbol, iterator->second->monopolyBlock);
  }
  // transfer tims cups
  rollUpRim[p->id] += rollUpRim[this->id];
  rollUpRim[this->id] = 0;
}

void Player::bankBankrupt(){
  typedef map<string, Ownable*>::iterator it;
  for(it iterator = this->prop.begin(); iterator != this->prop.end(); iterator++){
    if(iterator->second->checkMortgaged())
      iterator->second->mortgaged = false;
    iterator->second->buildingSize = 0;
    this->game->notification->view->updateBuilding(this->game->findProperty(iterator->second->name), 0);
    this->game->auction(iterator->second);
    this->removeProperty(iterator->second->name);
  }
  //detroy all tim cups
  rollUpRim[this->id] = 0;
}

// only if not enough money to pay
void Player::setOwing(Player *payee, int amnt){
  this->playerOwing = payee;
  this->oweAmnt = amnt;
}

bool Player::owesMoney(){
  if(this->oweAmnt > 0)
    return true;
  else
   return false;
}

void Player::payDebts(){
  if(this->owesMoney()){
    if(this->money > this->oweAmnt){
      //pay back
      cout << "Paid owing amount: " << this->oweAmnt;
      if(this->playerOwing == NULL){
        cout << " to bank" << endl;
      }
      else{
        this->playerOwing += this->oweAmnt;
        cout << " to player: " << this->playerOwing->name;
      }
      cout << "new balance: " << this->money << endl;
      this->oweAmnt = 0;
      this->playerOwing = NULL;
    }
    else{
      cout << "still owing " << this->oweAmnt << endl;
    }
  }
}

void Player::pay(Player *p, int amnt){
  if(this->money>amnt){
    this->money -= amnt;
    if(p != NULL){
      p->money += amnt;
    }
  }
  else{
    this->setOwing(p, amnt);
    cout << "insufficient funds, owe: " << amnt << endl;
    cout << "current funds: " << this->money << endl;
    cout << "mortgage, trade or declare bankrupt" << endl;
  }
}
