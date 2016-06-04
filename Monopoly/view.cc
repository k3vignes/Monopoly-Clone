#include "view.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

View::View(){
	string line;
	ifstream infile("board.txt");
	int i =0;
	while (getline(infile, line) && i < 67){
 		for (int j = 0; j < 121; j++){
 			this->board[i][j] = line[j];
 		}
		i++;
	}
}

void View::init(string name, bool ownable){
	string line; 
	ifstream infile("board.txt"); 
	int i =0; 
	while (getline(infile, line) && i < 67){
 		for (int j = 0; j < 121; j++){ 
 			this->board[i][j] = line[j]; 
 		}
		i++; 
	}
}

void View::print(ostream &out){
	for (int h = 0; h < 67; h++){
		for (int w = 0; w < 122; w++){
			out << this->board[h][w];
		}
		out << endl;
	}
}

int View::locateHeightSqr(int loc){
	if (loc >= 0 && loc < 11){
		return 0;
	}
	else if (loc > 10 && loc < 20){
		return (loc % 10) * 6;
	}
	else if (loc > 19 && loc < 31){
		return 60;
	}
	else {
		//[31,39]
		return 60 - (loc % 10) * 6;
	}


}

int View::locateWidthSqr(int loc){
	if (loc >= 0 && loc < 11){
		 return (loc * 11);
	}
	else if (loc > 10 && loc < 20){
		return 110;
	}
	else if (loc > 19 && loc < 31){
		return 110 - (loc % 10) * 11;
	}
	else {
		//[31,39]
		return 0;
	}
}


// gives updated view of improving a building
void View::updatePlayer(int oldLoc, int newLoc, int playerId, char symbol){
	removePlayer(oldLoc, symbol, playerId); 
	this->board[locateHeightSqr(newLoc) + 5][locateWidthSqr(newLoc) + playerId + 2] = symbol;
	print(cout);
}


void View::updateOwner(int square, char symbol, string monopolyBlock){
	int locW = locateWidthSqr(square);
	int locH = locateHeightSqr(square);
	if (monopolyBlock == "Gym" || monopolyBlock == "Residence"){ 
		this->board[locH + 1][locW + 5] = symbol; 
	}
	else{
		this->board[locH + 1][locW + 1] = symbol;
	}
	print(cout);
}

void View::updateBuilding(int square, int buildingSize){
	int locW = locateWidthSqr(square);
	int locH = locateHeightSqr(square);
	for (int i = 3; i < 10; i++){ 
		if(buildingSize != 0) { 
			this->board[locH + 1][locW + i] = 'I';
			buildingSize--; 
		}	 
		else{ 
			this->board[locH + 1][locW + i] = ' ';
		}
	}
	this->print(cout);
}

void View::removePlayer(int square, char symbol, int playerId){
	int oldLocW = locateWidthSqr(square);
	int oldLocH = locateHeightSqr(square);
	this->board[locateHeightSqr(square) + 5][locateWidthSqr(square) + playerId + 2] = ' ';	
}
