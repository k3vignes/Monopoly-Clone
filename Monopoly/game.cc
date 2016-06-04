#include "game.h"
#include "PRNG.h"
#include <iostream>
#include "building.h"
#include "residence.h"
#include "gym.h"
#include "slc.h"
#include "needleshall.h"
#include "osap.h"
#include "coopfee.h"
#include "goosenesting.h"
#include "gototims.h"
#include "timsline.h"
#include "tuition.h"
#include "player.h"
#include "unownable.h"
#include <fstream>
#include <sstream>
#include "controller.h"

using namespace std;

Game::Game(){
	for (int i = 0; i < 9; i++){           // makes sure everything in list these list are null
		this->players[i] = 0;
	}
	this->prng = PRNG(5);
	this->numPlayers = 0;
	this->currPlayer = 0;		// initialize currPlayer
	this->doubles = 0;
	this->canRoll = true;
}

void Game::init(Controller *gameNotification){
	notification = gameNotification;			// initializes notif



	this->board[0] = new OSAP("OSAP");
	int tAl[6] = {2, 10, 30, 90, 160, 250};
	this->board[1] = new Building(40, 50, tAl, "Arts1", "AL");
	this->board[2] = new SLC("SLC1");
	int tMl[6] = {4, 20, 60, 180, 320, 450};
	this->board[3] = new Building(60, 50, tMl, "Arts1", "ML");
	this->board[4] = new Tuition("Tuition");
	this->board[5] = new Residence("MKV");
	int tEch[6] = {6, 30, 90, 270, 400, 550};
	this->board[6] = new Building(100, 50, tEch, "Arts2", "ECH");
	this->board[7] = new NeedlesHall("NeedlesHall1");
	int tPas[6] = {6, 30, 90, 270, 400, 550};
	this->board[8] = new Building(100, 50, tPas, "Arts2", "PAS");
	int tHh[6] = {8, 40, 100, 300, 450, 600};
	this->board[9] = new Building(120, 50, tHh, "Arts2", "HH");
	this->board[10] = new TimsLine("TimsLine");
	int tRch[6] = {10, 50, 150, 450, 625, 750};
	this->board[11] = new Building(140, 100, tRch, "Eng", "RCH");
	this->board[12] = new Gym("PAC");
	int tDwe[6] = {10, 50, 150, 450, 625, 750};
	this->board[13] = new Building(140, 100, tDwe, "Eng", "DWE");
	int tCph[6] = {12, 60, 180, 500, 700, 900};
	this->board[14] = new Building(160, 100, tCph, "Eng", "CPH");
	this->board[15] = new Residence("UWP");
	int tLhi[6] = {14, 70, 200, 550, 750, 950};
	this->board[16] = new Building(180, 100, tLhi, "Health", "LHI");
	this->board[17] = new SLC("SLC2");
	int tBmh[6] = {14, 70, 200, 550, 750, 950};
	this->board[18] = new Building(180, 100, tBmh, "Health", "BMH");
	int tOpt[6] = {16, 80, 220, 600, 800, 1000};
	this->board[19] = new Building(200, 100, tOpt, "Health", "OPT");
	this->board[20] = new GooseNesting("GooseNesting");
	int tEv1[6] = {18, 90, 250, 700, 875, 1050};
	this->board[21] = new Building(220, 150, tEv1, "Env", "EV1");
	this->board[22] = new NeedlesHall("NeedlesHall2");
	this->board[23] = new  Building(220, 150, tEv1, "Env", "EV2");
	int tEv3[6] = {20, 100, 300, 750, 925, 1100};
	this->board[24] =  new Building (240, 150, tEv3, "Env", "EV3");
	this->board[25] = new  Residence("V1");
	int tPhys[6] = {22, 110, 330, 800, 975, 1150};
	this->board[26] = new  Building(260, 150, tPhys, "Sci1", "PHYS");
	this->board[27] = new  Building(260, 150, tPhys, "Sci1", "B1");
	this->board[28] = new  Gym("CIF");
	int tB2[6] = {24, 120, 360, 850, 1025, 1200};
	this->board[29] = new  Building(280, 150, tB2, "Sci1", "B2");
	this->board[30] = new  GoToTims("GoToTims");
	int tEit[6] = {26, 130, 390, 900, 1100, 1275};
	this->board[31] = new  Building(300, 200, tEit, "Sci2", "EIT");
	this->board[32] = new  Building(300, 200, tEit, "Sci2", "ESC");
	this->board[33] = new  SLC("SLC3");
	int tC2[6] = {28, 150, 450, 1000, 1200, 1400};
	this->board[34] = new  Building(320, 200, tC2, "Sci2", "C2");
	this->board[35] = new  Residence("REV");
	this->board[36] = new  NeedlesHall("NeedlesHall3");
	int tMc[6] = {35, 175, 500, 1100, 1300, 1500};
	this->board[37] = new  Building(350, 200, tMc, "Math", "MC");
	this->board[38] = new  CoopFee("CoopFee");
	int tDc[6] = {50, 200, 600, 1400, 1700, 2000};
	this->board[39] = new  Building(400, 200, tDc, "Math", "DC");
}

void Game::addPlayer(string playerName, char piece){
	Player* pp = new Player(playerName, piece, this);
	pp->setID(this->numPlayers);
	this->players[this->numPlayers] = pp;
	cout << this->players[this->numPlayers]->name + " symbol: " + this->players[this->numPlayers]->symbol << endl;
	this->numPlayers++;
}

bool Game::checkOwned(Property* prop){
	if(!this->isOwnable(prop))
	  return false;

	Ownable* op = static_cast<Ownable *>(prop);
	if (op->owner == -1){
		return false;
	}
	return true;
}

int Game::findProperty(string name){
  for(int i = 0;i<40;i++){
    if(this->board[i]->name == name)
	    return i;
  }
  return -1;
}

void Game::roll(){
	if(this->canRoll){
	  int die1 = prng (1,6);
	  int die2 = prng (1,6);
	  this->roll(die1, die2);
  }
}

void Game::roll(int die1, int die2){
	if(this->doubles == 2 && die1 == die2){
    this->players[currPlayer]->setPos(30,false);
		this->doubles = 0;
		this->canRoll = false;
		return;
	}

  if(this->canRoll){
		int oldLoc = this->players[this->currPlayer]->location;
		cout << "roll on die1 is: " << die1 << " roll on die2 is: " << die2 << endl;
		cout << "old posion: " << this->players[this->currPlayer]->location << endl;
		this->players[this->currPlayer]->move(die1, die2);
		cout << "new position: " << this->players[this->currPlayer]->location << endl;
		notification->view->updatePlayer(oldLoc, this->players[this->currPlayer]->location, this->players[this->currPlayer]->id, this->players[this->currPlayer]->symbol);

		this->canRoll = false;
		if(die1 == die2){
			this->doubles++;
			this->canRoll = true;
			cout << "Rolled doubles! You can roll again" << endl;
		}
		else{
			this->doubles = 0;
		}
	}
}

void Game::next(){
	if (!this->canRoll && !this->players[this->currPlayer]->owesMoney()){
		this->currPlayer = (this->currPlayer + 1) % this->numPlayers;
		while(this->players[this->currPlayer]->isBankrupt){
			this->currPlayer = (this->currPlayer + 1) % this->numPlayers;
		}
		this->canRoll = true;
	}
	else{
		cout << "cant call next players turn, roll the die or pay back debts" << endl;
	}

	cout << "current player turn is " << this->players[this->currPlayer]->name << endl;
	cout << "Their location is on " << this->board[this->players[currPlayer]->location]->name << endl;
	if(this->players[currPlayer]->jail > -1){
		cout << "They are in DC tims line: roll, payTims, useTims" << endl;
	}
}

bool Game::gameWon(){
	int c = 0;
	int index;
	for(int i=0;i<this->numPlayers;i++){
	  (this->players[i]->isBankrupt) ? c++ : index = i;
	}
	if(c == this->numPlayers - 1){
    cout << "game over winner is: " << this->players[index]->name <<endl;
	  return true;
	}
	else
	  return false;
}

void Game::setPosition(int i){
	this->canRoll = false;
	int oldLoc = this->players[this->currPlayer]->location;
	this->players[this->currPlayer]->setPos(i, true);
	notification->view->updatePlayer(oldLoc, this->players[this->currPlayer]->location, this->players[this->currPlayer]->id, this->players[this->currPlayer]->symbol);
}

void Game::checkLandingPos(int propIndex, int die1, int die2){
	Property* prop = this->board[propIndex];
	if (prop->isOwnable){
		Ownable* up = static_cast<Ownable *>(prop);
		if (up->owner != this->currPlayer && up->owner != -1){
			this->payRent(die1, die2);				//since not buyable
		}
		else if(up->owner == -1 && this->players[currPlayer]->money < up->purchCost){
			cout << "insufficient funds to buy property. property automatically auctioned" << endl;
			this->canAuction();
		}
		else if (up->owner == -1){
			bool done = false;
			string cmd;
			cout << "landed on unOwned property, so buy or auction this property" << endl;
			while (!done){
				cin >> cmd;
				if (cmd == "buy"){
					this->buy();
					done = true;
				}
				else if(cmd == "auction"){
					this->canAuction();
					done = true;
				}
				else{
					cout << "invalid input, must buy or auction property" << endl;
				}
			}
		}
	}
	else {
		Unownable* up = static_cast<Unownable *>(prop);
		int oldLoc = this->players[this->currPlayer]->location;
		up->specialty(this->players[this->currPlayer]);
		if (this->players[this->currPlayer]->location != oldLoc){
			notification->view->updatePlayer(oldLoc, this->players[this->currPlayer]->location, this->players[this->currPlayer]->id, this->players[this->currPlayer]->symbol);
		}
	}
}

bool Game::isOwnable(Property* prop){
	return prop->isOwnable;
}

// assuminh player has enough money
void Game::buy(){
	Property* p = this->board[this->players[this->currPlayer]->location];
	if (isOwnable(p)){
		Ownable* up = static_cast<Ownable *>(p);
		if (up->owner == -1){
			up->setOwnership(this->players[this->currPlayer]);
			cout << " owner: " << up->owner << endl;
			cout << " money: " << this->players[this->currPlayer]->money << endl;
		}
	}
}

void Game::payRent(int die1, int die2){
	Ownable* op = static_cast<Ownable *>(this->board[this->players[this->currPlayer]->location]);
	if (!op->mortgaged){
		if (op->monopolyBlock == "Gym"){
			// Pay gym rent
			Gym* gp = static_cast<Gym* >(op);
			int i = findProperty("CIF");
			int k = findProperty("PAC");
			Gym* tempGp = static_cast<Gym* >(this->board[i]);
			Gym* tempGp2 = static_cast<Gym* > (this->board[k]);
			cout << "BEFORE PAYING RENT - IN GYM RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[gp->owner]->money << endl;
			if (tempGp->owner == tempGp2->owner){
				// pay 10X sum of dice
				int rent = 10 * (die1 + die2);
				this->players[currPlayer]->pay(this->players[gp->owner], rent);
			}
			else{
				// pay 4x sum of dice
				int rent = 4 * (die1 + die2);
				this->players[currPlayer]->pay(this->players[gp->owner], rent);
			}
			cout << "AFTER PAYING RENT - IN GYM RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[gp->owner]->money << endl;

		}
		else if (op->monopolyBlock == "Residence"){
			//pay res rent;
			Residence* rp = static_cast<Residence* >(op);
			cout << "BEFORE PAYING RENT - IN RES RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[rp->owner]->money << endl;
			int res[4];
			Residence* tempRp = static_cast<Residence* >(this->board[findProperty("MKV")]);
			Residence* tempRp2 = static_cast<Residence* >(this->board[findProperty("UWP")]);
			Residence* tempRp3 = static_cast<Residence* >(this->board[findProperty("V1")]);
			Residence* tempRp4 = static_cast<Residence* >(this->board[findProperty("REV")]);
			res[0] = tempRp->owner;
			res[1] = tempRp2->owner;
			res[2] = tempRp3->owner;
			res[3] = tempRp4->owner;
			int numSameOwner = 0;
			for (int i =0; i < 4; i++){
				if (res[i] == rp->owner){
					numSameOwner++;
				}
			}
			int rent = numSameOwner * 25;

			this->players[currPlayer]->pay(this->players[rp->owner], rent);
			cout << "AFTER PAYING RENT - IN RES RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[rp->owner]->money << endl;
		}
		else{

			// Pay building rent
			Building* bp = static_cast<Building *>(op);
			cout << "building Name: " << bp->name << " monoblock: " << bp->monopolyBlock << " tuition[0]: " << bp->tuition[0] << endl;
			cout << "BEFORE PAYING RENT - IN BUILDING RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[bp->owner]->money << endl;
			int rent;
			if (isMonopoly(findProperty(bp->name)) && bp->buildingSize == 0){
      				rent = bp->rent() * 2;
      			}
      			else {
      				rent = bp->rent();
      			}
			this->players[currPlayer]->pay(this->players[bp->owner], rent);
			cout << "AFTER PAYING RENT - IN BUILDING RENT - curplayer.money: " << this->players[this->currPlayer]->money << " owner's money: " << this->players[bp->owner]->money << endl;
		}
	}
}

bool Game::isMonopoly(int propIndex){
	Ownable* op = static_cast<Ownable *>(this->board[propIndex]);
	for(int i = 0; i < 40; i++){
		if (isOwnable(this->board[i])){
			Ownable *tempOp = static_cast<Ownable *>(this->board[i]);
			if (op->monopolyBlock == tempOp->monopolyBlock){
				if (op->owner != tempOp->owner){
					return false;
				}
			}
		}
	}
	return true;
}

bool Game::emptyMonopoly(int propIndex){
	if(!this->isMonopoly(propIndex))
	  return true;
	else if(this->isMonopoly(propIndex)){
		Ownable* op = static_cast<Ownable *>(this->board[propIndex]);
		for(int i = 0; i < 40; i++){
			if (isOwnable(this->board[i])){
				Ownable *tempOp = static_cast<Ownable *>(this->board[i]);
				if (op->monopolyBlock == tempOp->monopolyBlock){
					if (tempOp->buildingSize > 0){
						return false;
					}
				}
			}
		}
    return true;
	}
	return true;
}

void Game::mortgage(string name){
	if (isOwnable(this->board[findProperty(name)]) && emptyMonopoly(findProperty(name))){
		Ownable* op = static_cast<Ownable *>(this->board[findProperty(name)]);
		op->mortgage(this->players[this->currPlayer]);
	}

	this->players[currPlayer]->payDebts();
}

void Game::unmortgage(string name){
	if (isOwnable(this->board[findProperty(name)])){
		Ownable* op = static_cast<Ownable *>(this->board[findProperty(name)]);
		op->unmortgage(this->players[this->currPlayer]);
	}
}

void Game::improve(string propName){
	if (isOwnable(this->board[findProperty(propName)])){
		Ownable* op = static_cast<Ownable *>(this->board[findProperty(propName)]);
		cout << "IMPROVE-BEFORE buildingsize: " << op->buildingSize << endl;
		cout << "block: " << op->monopolyBlock << endl;
		if (op->owner == this->currPlayer && op->monopolyBlock != "Gym" && op->monopolyBlock != "Residence"){
			Building* bp = static_cast<Building *>(op);
			if (isMonopoly(findProperty(bp->name))){
				cout << "in" << endl;
				bp->improve(this->players[this->currPlayer]);
			}
		}
		cout << "IMPROVE- AFTER - buildingsize: " << op->buildingSize << endl;
		notification->view->updateBuilding(findProperty(op->name), op->buildingSize);
	}
}

void Game::unimprove(string propName){
	if (isOwnable(this->board[findProperty(propName)])){
		Ownable* op = static_cast<Ownable *>(this->board[findProperty(propName)]);
		cout << "UNIMPROVE-BEFORE buildingsize: " << op->buildingSize << endl;
		if (op->owner == this->currPlayer && op->monopolyBlock != "Gym" && op->monopolyBlock != "Residence"){
			Building* bp = static_cast<Building *>(op);
			if (isMonopoly(findProperty(bp->name))){
				bp->unimprove(this->players[this->currPlayer]);
			}
		}
		cout << "UNIMPROVE- AFTER - buildingsize: " << op->buildingSize << endl;
		notification->view->updateBuilding(findProperty(op->name), op->buildingSize);

		this->players[currPlayer]->payDebts();
	}
}

void Game::save(string filename){
	if(!this->players[currPlayer]->owesMoney()){
	  ofstream file;
		cout << filename.c_str() << endl;
	  file.open(filename.c_str());
		int n=0;
		for(int i=0;i<numPlayers;i++){
			if(!this->players[i]->isBankrupt)
			  n++;
		}
	  file << n << endl;
	  file << savePlayers();
	  file << saveProperties();
	  file.close();
 }
}

string Game::intToStr(int n){
 ostringstream oss;
 oss << n;
 return oss.str();
}

string Game::savePlayers(){
  string str = "";
	int n = this->currPlayer;
  for(int i =0;i<numPlayers;i++){
		n = (n + i) % this->numPlayers;
    Player *pp = this->players[n];
		if(!this->players[n]->isBankrupt){
	    str += pp->name + " " + pp->symbol + " " + intToStr(Player::rollUpRim[n]) + " " + intToStr(pp->money) + " " + intToStr(pp->location);
		  if(pp->location == 10){
				str += (pp->jail != -1) ? (" 1 " + intToStr(pp->jail)) : "  0";
		  }
	  	str += "\n";
	  }
  }
  //cout << str << endl;
  return str;
}

string Game::saveProperties(){
  string str = "";
  for(int i=0;i<40;i++){
    if(this->isOwnable(this->board[i])){
	    Ownable* op = static_cast<Ownable *>(this->board[i]);
			string owner = (op->owner == -1) ? "BANK" : this->players[op->owner]->name;
	    str += op->name + " " + owner + " " + intToStr(op->buildingSize) + "\n";
  	}
  }
  //cout << str << endl;
  return str;
}

int Game::findPlayerIndex(string name){
	for(int i=0;i<this->numPlayers;i++){
		if(this->players[i]->name == name)
		  return i;
	}
	return -1;
}

void Game::load(string filename){
  ifstream file(filename.c_str());

	file >> this->numPlayers;
	this->loadPlayers(file);
	this->loadProperties(file);

	file.close();
}

void Game::loadPlayers(ifstream &file){
	for(int i=0; i < this->numPlayers; i++){
		string name;
		char sym;
		int timCards, money, location, jail;
		file >> name;
		file >> sym;
		file >> timCards;
		file >> money;
		file>> location;
		cout << "PLayer: " << name << endl;
		if(location == 10) {file >> jail;}
		if(jail == 1) {file >> jail;} else {jail = -1;}
		this->players[i] = new Player(name, sym, this, timCards, money, location, jail, i);
		notification->view->updatePlayer(0, location, i, sym);

	}
}

void Game::loadProperties(ifstream &file){
	for(int i=0;i<40;i++){
		if(this->board[i]->isOwnable){
			string owner;
			int size;
			file >> owner; // name of prop, ignore
			file >> owner;
			file >> size;
			//cout << "name: " <<  << endl;
			Ownable *op = static_cast<Ownable *>(this->board[i]);
			if (owner != "BANK"){
				op->transferOwnership(this->players[this->findPlayerIndex(owner)]);
			}
			op->setBuildingSize(size);
			notification->view->updateBuilding(findProperty(op->name), op->buildingSize);
		}
	}
}

void Game::listAssets(){
	this->players[this->currPlayer]->assets();
}

Player *Game::findPlayer(string pname){
	for(int i=0;i<this->numPlayers;i++){
		if(this->players[i]->name == pname)
		  return this->players[i];
	}
	return NULL;
}

void Game::trade(string pname, string str1, string str2){
	Player *p = this->findPlayer(pname);
	int m = -1;
	int m2 = -1;
	Ownable *op;
	Ownable *op2;

	if(isdigit(str1[0])){
    istringstream ( str1 ) >> m;
  }
	else{
		op = static_cast<Ownable *>(this->board[this->findProperty(str1)]);
		if(op->buildingSize >0 || !emptyMonopoly(findProperty(str1))){
			cout << "cant trade property/monoblock with improvements" << endl;
			return;
		}
	}

	if(isdigit(str2[0])){
    istringstream ( str2 ) >> m2;
  }
	else{
		op2 = static_cast<Ownable *>(this->board[this->findProperty(str2)]);
		if(op2->buildingSize >0){
			cout << "cant trade property with improvements" << endl;
			return;
		}
	}

  if(m != -1 && m2!=-1){
		cout << "can't trade money for money" << endl;
		return;
	}

	cout << p->name << " accept this trade? y/n" << endl;
	string cmd;
	cin >> cmd;

	if(cmd == "y"){
		if(m!=-1){
			if(this->players[currPlayer]->money<m){
				cout << "cant trade more money than you own" << endl;
				return;
			}
			this->players[currPlayer]->money -= m;
			p->money += m;
		}
		else{
			op->transferOwnership(p);
			this->players[currPlayer]->removeProperty(str1);
		}

		if(m2!=-1){
			if(p->money<m2){
				cout << "cant trade more money than you own" << endl;
				return;
			}
			this->players[currPlayer]->money += m2;
		  p->money -= m2;
		}
		else{
			op2->transferOwnership(this->players[currPlayer]);
			p->removeProperty(str2);
		}

		this->players[currPlayer]->payDebts();
	}
	else if(cmd == "n"){
		cout << "trade rejected" << endl;
	}
}

void Game::canAuction(){
	Property *p = this->board[this->players[currPlayer]->location];
	if(p->isOwnable){
		Ownable *op = static_cast<Ownable *> (p);
		if(op->owner == -1){
      this->auction(op);
		}
		else{
			cout << "cant this property, already owned" << endl;
		}
	}
	else{
		cout << "cant auction unownable property" << endl;
	}
}

bool Game::inList(list <int> index, int n){
	for(list<int>::iterator it = index.begin(); it != index.end(); it++){
		if (*it == n){
			return true;
		}
	}
	return false;
}

void Game::auction(Ownable *op){
	cout << op->name << " up for auction, original value: " << op->purchCost << endl;

	int bidders = 0;
	int highestBid = 0;
	int highestBidder = 0;
  list<int> indexes;
	for(int i=0;i<this->numPlayers;i++){
		if(!this->players[i]->isBankrupt){
			bidders++;
		  indexes.push_back(i);
		}
	}

	while(bidders > 1){
    for(int i=0;i<this->numPlayers;i++){
			if(inList(indexes, i)){
				cout << this->players[i]->name << "'s turn to raise bid, enter a bid? y/n" << endl;
				string cmd;
        			cin >> cmd;
				if(cmd=="y"){
					int bid;
					cin >> bid;
					if(bid > this->players[i]->money){
						cout << "can't bid more money than you have" << endl;
					}
					else if(bid > highestBid){
						highestBid = bid;
						highestBidder = i;
						cout << "new highest bid is: " << highestBid << endl;
					}
					else{
						cout << "can't underbid" << endl;
					  cout << "removed " << this->players[i]->name << " from bidding" << endl;
						indexes.remove(i);
						bidders--;
					}
				}
				else if(cmd=="n"){
					indexes.remove(i);
					bidders--;
				}
			}
		}
	}
  cout << "Winning player is: " << this->players[highestBidder]->name << "with bid: " << highestBid << endl;

	op->auction(this->players[highestBidder], highestBid);
	notification->view->updateOwner(findProperty(op->name), this->players[highestBidder]->symbol, op->monopolyBlock);
}

void Game::bankrupt(){
	if(this->players[currPlayer]->owesMoney()){
		cout << this->players[currPlayer]->name << " has gone bankrupt!" << endl;
    this->players[currPlayer]->bankrupt();
    if(this->gameWon()){
			return;
		}

		if(this->board[this->players[currPlayer]->location]->isOwnable){
			Ownable *op = static_cast <Ownable *> (this->board[this->players[currPlayer]->location]);
			cout << "Properties transfered over to " << this->players[op->owner] << endl;
			this->bankrupt(this->players[op->owner]); // transfer all property & tim cards
		}
		else{
			//bankrupt to bank
			cout << "Properties to be auctioned:" << endl;
      this->bankBankrupt();
		}
		// ignore bankrupt players, in bids & next
	}
	else{
		cout << "invalid bankrupt" << endl;
	}
}

void Game::bankrupt(Player *p){
  notification->view->removePlayer(this->players[this->currPlayer]->location, this->players[this->currPlayer]->symbol, this->players[this->currPlayer]->id);
  this->players[currPlayer]->transferAll(p);
  this->canRoll = false;
	this->players[currPlayer]->oweAmnt = 0;
  this->next();
}

void Game::bankBankrupt(){
  this->players[currPlayer]->bankBankrupt();
  notification->view->removePlayer(this->players[this->currPlayer]->location, this->players[this->currPlayer]->symbol, this->players[this->currPlayer]->id);
  this->canRoll = false;
	this->players[currPlayer]->oweAmnt = 0;
	this->next();
}

void Game::gameUpdate(string name, char sym, string monopolyBlock){
	notification->view->updateOwner(findProperty(name), sym, monopolyBlock);
}

void Game::addTims(string name){
	Player *p = findPlayer(name);
	p->rollUpRim[p->id] += 1;
	cout << p->name << "now has " << p->rollUpRim[p->id] << "rollUpRim's" << endl;
}

void Game::useTims(){
	if(this->players[currPlayer]->jail>-1 && this->players[this->currPlayer]->rollUpRim[this->players[currPlayer]->id]>0){
    this->players[this->currPlayer]->jail = -1;
		this->players[this->currPlayer]->rollUpRim[this->players[currPlayer]->id] --;
		cout << "used tims cup, got out of jail. Remianing tims cups:  " << this->players[this->currPlayer]->rollUpRim[this->players[currPlayer]->id] << endl;
	}
}

void Game::payTims(){
	if(this->players[currPlayer]->jail>-1){
		this->players[this->currPlayer]->jail = -1;
		this->players[this->currPlayer]->pay(NULL, 50);
		cout << "Paid $50 to get out of jail, remaining balance: " << this->players[currPlayer]->money << endl;
	}
}
