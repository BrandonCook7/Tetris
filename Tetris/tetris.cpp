#include "tetris.h"

tetris::tetris()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "Tetris In C++"); // creates window
    float timer = 0; // timer
    float delay = 0.3; // delay in milliseconds
    Clock clock; // clock
    
    hasSpawned = 0;
    
    // Load textures and sprites
    
    // Blocks.jpg has 7 blocks of different color. Tried using just a grey scale image and setColor, but it made blocks too dark. This way allows us to change color by changing what part of the image a sprite uses
    
    Texture blockTexture;
    if (!blockTexture.loadFromFile("images/blocks.jpg")) {
        return EXIT_FAILURE;
    }
    blockTexture.setSmooth(true);
    Sprite sprite(blockTexture);
    
    Texture gridTexture;
    if (!gridTexture.loadFromFile("images/grid.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite gridSprite(gridTexture);
    
    
    /* Text code. Move somewhere later
     
     sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(400, 32);

     
     */
    
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) window.close();
                if(event.key.code == sf::Keyboard::Left) dx = -1;
                if(event.key.code == sf::Keyboard::Right) dx = 1;
                if(event.key.code == sf::Keyboard::Up) needsRotation = true;
            }
        }
        
        move();
        rotate();
        spawn(sprite);
        
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

void tetris::rotate() {
    Coordinate temp = block[1];
    int x = 0, y = 0;
    
    for(int i = 0; i < 4; i++) {
        x = current[i].y - temp.y;
        y = current[i].x - temp.x;
        current[i].x = temp.x - x;
        current[i].y = temp.y + y;
    }
}

void tetris::move() {
    for(int i = 0; i < 4; i++) {
        prev[i].x = current[i].x; // used to restore block's position if it goes out of bounds
        current[i].x += dx;
    }
    
    if(!checkBounds()) { // went out of bounds
        for(int i = 0; i < 4; i++) {
            current[i].x = prev[i].x;
        }
    }
}

void tetris::spawn(Sprite sprite) {
    
    if(hasSpawned == 0) { // check if a block has been spawned already
        int randNum = rand() % 7;
        sprite.setTextureRect(sf::IntRect(randNum * 32,0,32,32)); // set color of sprite
        for(int i = 0; i < 4; i++) {
            current[i].x = shapes[randNum][i].x;
            current[i].y = shapes[randNum][i].y;
        }
        
        hasSpawned = 1;
    }
}
