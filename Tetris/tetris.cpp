#include "tetris.h"

tetris::tetris()
{
    srand(time(0));
    RenderWindow window(VideoMode(800, 800), "Tetris In C++"); // creates window
    float timer = 0; // timer
    float delay = 0.3; // delay in milliseconds
    Clock clock; // clock
    hasSpawned = 0;
    int isSquare = 0;
    // Load textures and sprites
    // Blocks.jpg has 7 blocks of different color. Tried using just a grey scale image and setColor, but it made blocks too dark. This way allows us to change color by changing what part of the image a sprite uses
    Texture blockTexture;
    if (!blockTexture.loadFromFile("images/blocks.jpg")) {
        cout << "Unable to open images/blocks.jpg" << endl;
    }
    blockTexture.setSmooth(true);
    Sprite sprite(blockTexture);

    Texture gridTexture;
    if (!gridTexture.loadFromFile("images/grid.jpg")) {
        cout << "Unable to open images/grid.jpg" << endl;
    }
    Sprite gridSprite(gridTexture);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        // Process events
        Event event;
        while (window.pollEvent(event)) {

            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) window.close();
                if (event.key.code == Keyboard::Left) dx = -1;
                if (event.key.code == Keyboard::Right) dx = 1;
                if (event.key.code == Keyboard::Up) needsRotation = true;
                if (event.key.code == Keyboard::Down) delay = 0.05;
            }
        }
        move();
        if (needsRotation && !isSquare) rotate();
        spawn(sprite, isSquare);
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                prev[i] = current[i];
                current[i].y += 1;
            }
            if (!checkBounds())
            {
                for (int i = 0; i < 4; i++)
                    current[i].y = prev[i].y;
            }
            timer = 0;
        }
        checkLines();
        dx = 0; needsRotation = false; delay = 0.3;

     //drawing
        // Clear screen
        window.clear(Color::White);
        window.draw(gridSprite);
        // Draw the sprite in correct spot
        for (int i = 0; i < 4; i++) {
            sprite.setPosition(current[i].x * 32 + 10, current[i].y * 32 + 10); // multiply by 32 so the block's dont overlap. (Each block is 32x32). Add 10 px to both values so they are within the grid. Grid image has 10px border
            window.draw(sprite);
        }
        // add display score here
        window.display(); // Update the window
    }
}

bool tetris::checkBounds()
{
    for (int i = 0; i < 4; i++)
    {
        if (current[i].x < 0 || current[i].x >= 10 || current[i].y >= 20)
        {
            return false;
        }
        else if (grid[current[i].y][current[i].x])
        {
            return false;
        }
    }
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

void tetris::rotate() {
    Coordinate temp = current[1];
    int x = 0, y = 0;

    for (int i = 0; i < 4; i++) {
        x = current[i].y - temp.y;
        y = current[i].x - temp.x;
        current[i].x = temp.x - x;
        current[i].y = temp.y + y;
    }
}

void tetris::move() {
    for (int i = 0; i < 4; i++) {
        prev[i].x = current[i].x; // used to restore block's position if it goes out of bounds
        current[i].x += dx;
    }

    if (!checkBounds()) { // went out of bounds
        for (int i = 0; i < 4; i++) {
            current[i].x = prev[i].x;
        }
    }
}

void tetris::spawn(Sprite& sprite, int &isSquare) {
    if (hasSpawned == 0) { // check if a block has been spawned already
        int randNum = rand() % 7;
        if (randNum == 1) isSquare = 1;
        sprite.setTextureRect(IntRect(randNum * 32, 0, 32, 32)); // set color of sprite
        for (int i = 0; i < 4; i++) {
            current[i].x = shapes[randNum][i].x;
            current[i].y = shapes[randNum][i].y;
        }
        hasSpawned = 1;
    }
}

bool tetris::checkWin() {
    return true;
}