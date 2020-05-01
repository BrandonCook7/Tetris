#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>

#include <iostream>

typedef struct coordinate {
    int x;
    int y;
} Coordinate;

//bool valid(Coordinate arr[4], int grid[][10]) {
//    for(int i = 0; i < 4; i++) {
//        if(arr[i].x < 0 || arr[i].x >= 10 || arr[i].y >= 20) {
//            return 0;
//        } else if(grid[arr[i].y][arr[i].x]) {
//            return 0;
//        }
//    }
//
//    return 1;
//}

int main() {
    
    Coordinate shapes[7][4] = { // Creates block shapes using a 4x4 coordinate grid. Top left is {0,0}, bottom right is {3,3}
        {{1,0},{1,1},{1,2},{1,3}}, // I
        {{0,1},{1,1},{0,2},{1,2}}, // O (square)
        {{1,1},{2,1},{0,2},{1,2}}, // S
        {{0,1},{1,1},{1,2},{2,2}}, // Z
        {{1,0},{1,1},{1,2},{2,2}}, // L
        {{1,0},{1,1},{0,2},{1,2}}, // J
        {{0,1},{1,1},{2,1},{1,2}}  // T
    };
    
    Coordinate block[4] = {0}; // holds the 4 coordinates of a block
    int grid[20][10] = {0};
    
    int move = 0; // determines which direction to move
    bool rotate = false;
    
    srand( (unsigned) time(NULL));
    int randNum = 0;
    int tempNum = 0;
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    
    // Load textures and sprites
    
    sf::Texture blockTexture;
    if (!blockTexture.loadFromFile("images/blocks.jpg")) { // Image has 7 blocks of different color. Tried using just a grey scale image and setColor, but it made blocks too dark. This way allows us to change color by changing what part of the image a sprite uses
        return EXIT_FAILURE;
    }
    blockTexture.setSmooth(true);
    sf::Sprite sprite(blockTexture);
    
    sf::Texture gridTexture;
    if (!gridTexture.loadFromFile("images/grid.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite gridSprite(gridTexture);
    
    
    
    // Create text
    
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(400, 32);

    while (window.isOpen()) { // Starts game loop
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) window.close();
                if(event.key.code == sf::Keyboard::Left) move = -1;
                if(event.key.code == sf::Keyboard::Right) move = 1;
                if(event.key.code == sf::Keyboard::Up) rotate = true;
            }
        }
        
        // Move
        for(int i = 0; i < 4; i++) {
            block[i].x += move;
        }
        
        // Rotate
        if(rotate) { // need to add case preventing square block from being rotated
            
            Coordinate temp = block[1];
            
            for(int i = 0; i < 4; i++) {
                int x = block[i].y - temp.y;
                int y = block[i].x - temp.x;
                block[i].x = temp.x - x;
                block[i].y = temp.y + y;
            }
        }
        
        // Determine which block and set block array to hold its 4 coordinates
        if(tempNum == 0) { // make sure block only set to tetris shape when it first spawns in
            randNum = rand() % 7;
            std::cout << randNum << "\n";
            sprite.setTextureRect(sf::IntRect(randNum * 32,0,32,32)); // // set color of sprite.
            for(int i = 0; i < 4; i++) {
                block[i].x = shapes[randNum][i].x;
                block[i].y = shapes[randNum][i].y;
            }
            
            tempNum = 1;
        }
        
        move = 0;
        rotate = false;

        // Clear screen
        window.clear(sf::Color::White);
        window.draw(gridSprite);
        
        // Draw the sprite in correct spot
        for(int i = 0; i < 4; i++) {
            sprite.setPosition(block[i].x * 32, block[i].y * 32); // multiply by 32 so the block's dont overlap. (Each block is 32x32). Add 10 px to both values so they are within the grid. Grid image has 10px border
            window.draw(sprite);
        }
        
        window.draw(text);

        window.display(); // Update the window
    }

    return 0;
}
