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

bool tetris::checkBounds()
{
    for (int i = 0; i < 4; i++)
        if (current[i].x < 0 || current[i].x >= 10 || current[i].y >= 20) 
            return false;
        else if (grid[current[i].y][current[i].x])
            return false;

    return true;
}

void tetris::checkLines()
{
    int temp = 20 - 1;
    for (int i = temp; i > 0; i--)
    {
        int count = 0;
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j])
            {
                count++;
            }
            grid[temp][j] = grid[i][j];
        }
        if (count < 10)
            temp--;
    }
}
