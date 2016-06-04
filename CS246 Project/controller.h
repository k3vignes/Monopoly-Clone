#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "view.h"
#include "game.h"

class Controller{
	Game* game;
	public:
	View* view;
	bool testing;
	//bool loadFile;
	//string file; 
	
	Controller();  // Constructor
	//~Controller(); // Destructor

	void notify(); // notifies the view of any changes
	void play(); //
	void playGame();
	//bool checkRollOnce(); // checks if the player has already rolled once

};

#endif
