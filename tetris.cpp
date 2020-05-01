#include "tetris.h"

tetris::tetris()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "Tetris In C++");//creates window
    float timer = 0;//timer 
    float delay = 0.3;//delay in milliseconds
    Clock clock;//clock

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
    }
}
