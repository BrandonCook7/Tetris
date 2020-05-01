#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

typedef struct coordinate {
	int x;
	int y;
}Coordinate;
class game
{
protected:
	int gameState;//1 is normal, 0 is lost, 2 is win
	int level;//indicates speed and points worth
	int dx;//speed of horizontal movement
	Coordinate block[4]; // used to hold the 4 coordinates of a block
public:
	game();
	~game();
	void delay(int ms);
	void move(Event event);
	bool virtual checkWin();
	void printWin();
	int getdx();
	void setdx();
	int getLevel();
	void setLevel();
};
