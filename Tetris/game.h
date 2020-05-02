#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

typedef struct coordinate {
	int x;
	int y;
} Coordinate;

//game is a general class that can be derived to create different games. tetris, asteroids, etc.
class game
{
protected:
	int gameState; // 1 is normal, 0 is lost
	int dx; // distance moved on x-axis
	int score=0;
public:
	game(){ //constructor
		//intializes game variables
		dx = 0;
		gameState = 1;
		score = 0;
	}
	~game() {}//destructor
	int virtual checkWin();//pure virtual function for checking to win. returns 1
	int getScore() {//getter
		return score;
	}
	void setScore(int s) {//setter
		score = s;
	}
	void virtual displayFinalScore();//shows final score and if the player won. pure virtual function
};

#endif /* game_hpp */