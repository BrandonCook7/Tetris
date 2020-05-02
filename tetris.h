
#ifndef tetris_h
#define tetris_h

#include "game.h"

class tetris : public game
{
private:
    int score;
    int randNum;
    int hasSpawned;
    bool needsRotation;
    float timer; // timer
    float delay; // delay in milliseconds
    Clock clock; // clock

    int grid[20][10] = { 0 }; // playing field
    Coordinate shapes[7][4] = // different pieces
    {
        {{0,1},{1,1},{2,1},{3,1}}, // I
        {{0,1},{1,1},{0,2},{1,2}}, // O (square)
        {{1,1},{2,1},{0,2},{1,2}}, // S
        {{0,1},{1,1},{1,2},{2,2}}, // Z
        {{1,0},{1,1},{1,2},{2,2}}, // L
        {{1,0},{1,1},{0,2},{1,2}}, // J
        {{0,1},{1,1},{2,1},{1,2}}  // T
    };
    Coordinate current[4], prev[4]; // keeps track of block's current position and previous position
public:
    tetris();
    bool checkWin();
    bool checkBounds();
    void checkLines();
    void rotate();
    void move();
    void spawn(Sprite& sprite);
    void displayScore();
};

#endif /* tetris_hpp */
