#include "controller.h"
#include "game.h"
#include "view.h"
#include <iostream>
using namespace std;

Controller::Controller(){
  game = new Game();
  view = new View();
  this->testing = false;
  //this->loadFile = false;
}

void Controller::notify(){

}

void Controller::play(){
  bool init = false;
  string cmd;
  int numPlayers = -1;
  string playerName;
  char symbol;

  // setup game
  cout << "new or -load game?" << endl;
  cin >> cmd;
  if(cmd == "-load"){
    cout << "enter file name" << endl;
    string fileName;
    cin >> fileName;
    game->init(this);
    game->load(fileName);
    cout << "current player turn is " << game->players[0]->name << endl;
    this->playGame();
  }
  else if(cmd == "-testing"){
    cout << "Testing mode started" << endl;
    this->testing = true;
    this->play();
  }
  else if(cmd == "new"){
    cout << "Enter number of players" << endl;
    if(cin >> numPlayers && numPlayers > 0 && numPlayers < 9){
        for(int i=0;i<numPlayers;i++){
          cout << "enter name and symbol for player number " << i << endl;
          cin >> playerName;
          cin >> symbol;
          game->addPlayer(playerName, symbol);
          this->view->updatePlayer(0, 0, i, symbol);
        }
        init = true;
    }
    cout << "done making players" << endl;
    game->init(this);
    cout << "current player turn is " << game->players[0]->name << endl;
    this->playGame();
  }
  else if(cmd == "quit"){
    cout << "game ended" << endl;
    return;
  }
}

void Controller::playGame(){
  if(game->gameWon())
    return;
  //if (this->loadFile)
    //game->load(file);
  string cmd;
  while(cin >> cmd){
    if(cmd == "roll"){
      if(testing){
        int die1, die2;
        cin >> die1;
        cin >> die2;
        game->roll(die1, die2);
      }
      else{
        game->roll();
      }
    }
    else if(cmd == "useTims"){
      game->useTims();
    }
    else if(cmd == "payTims"){
      game->payTims();
    }
	  else if(cmd == "set"){
      if(testing){
	      int n;
	      cin >> n;
  	    game->setPosition(n);
      }
  	}
    else if(cmd == "tims"){
      if(testing){
        string name;
        cin >> name;
        game->addTims(name);
      }
    }
    else if(cmd == "next"){
      game->next();
    }
    else if(cmd == "trade"){
      //fix later
      string pname, give, receive;
      cin >> pname;
      cin >> give;
      cin >> receive;
      game->trade(pname,give, receive);
    }
    else if(cmd == "improve"){
      string prop;
	    cin >> prop;
	    string buy;
	    cin >> buy;
	    if(buy == "buy"){
	      game->improve(prop);
	    }
	    else if(buy == "sell"){
	      game->unimprove(prop);
	    }
    }
    else if(cmd == "mortgage"){
      string prop;
	    cin >> prop;
	    game->mortgage(prop);
    }
    else if(cmd == "unmortgage"){
      string prop;
	    cin >> prop;
	    game->unmortgage(prop);
    }
    else if(cmd == "bankrupt"){
      game->bankrupt();
      if(game->gameWon())
        break;
    }
    else if(cmd == "assets"){
      game->listAssets();
    }
    else if(cmd == "save"){
      string fileName;
	    cin >> fileName;
	    game->save(fileName);
    }
    else if(cmd == "-load"){
      string fileName;
      cin >> fileName;
      game->load(fileName);
    }
    else if(cmd == "-testing"){
      this->testing = true;
    }
    else if(cmd == "quit"){
      cout << "game ended" << endl;
      return;
    }
  }
}
