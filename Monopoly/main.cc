#include "controller.h"
#include <iostream>
#include <sstream>
using namespace std;

int main (int argc, char* argv[]) {
    Controller c;
    /*if (argc == 2){ 
    	c.testing == true; 
    }
    else if (argc == 3){ 
    	c.loadFile = true; 
    	stringstream ss(argv[2]); 
    	ss >> c.file; 
    }*/   	
    c.play();
}
