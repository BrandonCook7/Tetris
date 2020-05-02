
#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

typedef struct coordinate {
	int x;
	int y;
} Coordinate;

class game
{
protected:
	int gameState; // 1 is normal, 0 is lost, 2 is win
	int level; // indicates speed and points worth
	int dx; // distance moved on x-axis
public:
	game(){ //constructor
		level = 0;//intializes game variables
		dx = 0;
		gameState = 1;
	}
	~game() {

	}
	int virtual checkWin() { // fix later
		return true;
	}
	void printWin(); // declares that the player won or lost
	int getLevel() {
		return level;
	}
	void setLevel(int l) {
		level = l;
	}
    void virtual displayScore() {
        
    }
};

#endif /* game_hpp */
