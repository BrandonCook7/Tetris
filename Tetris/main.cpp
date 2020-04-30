#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef struct coordinate {
    int x;
    int y;
} Coordinate;

int main() {
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");

    // Create block shapes using 4x4 coordinate grid. Starts at {0,0} top left and ends at {3,3} bottom right.
    Coordinate shapes[7][4] = {
        {{1,0},{1,1},{1,2},{1,3}}, // I
        {{0,1},{1,1},{0,2},{1,2}}, // O (square)
        {{1,1},{2,1},{0,2},{1,2}}, // S
        {{0,1},{1,1},{1,2},{2,2}}, // Z
        {{1,0},{1,1},{1,2},{2,2}}, // L
        {{1,0},{1,1},{0,2},{1,2}}, // J
        {{0,1},{1,1},{2,1},{1,2}}  // T
    };

    Coordinate block[4]; // used to hold the 4 coordinates of a block

    int grid[20][10] = {0};

    // Load block texture and sprites
    sf::Texture blockTexture;
    if (!blockTexture.loadFromFile("images/block.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Sprite green(blockTexture);
    green.setColor(sf::Color(0,255,0));
    
    sf::Sprite red(blockTexture);
    red.setColor(sf::Color(255,0,0));
    
    // Load grid texture and sprite
    sf::Texture gridTexture;
    if (!gridTexture.loadFromFile("images/grid.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite gridSprite(gridTexture);
    
    
    // Create text to display
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(400, 32);

    // Start the game loop
    while (window.isOpen()) {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::White);
        
        // Test code. Delete later. Sets block to be I
        for(int i = 0; i < 4; i++) {
            block[i].x = shapes[0][i].x;
            block[i].y = shapes[0][i].y;
        }
        
        window.draw(gridSprite);
        
        // Test code. Delete later. Sets red sprite to be each block in I and draws it to screen.
        for(int i = 0; i < 4; i++) {
            red.setPosition(10 + block[i].x * 32, 10 + block[i].y * 32); // multiply by 32 so the block's dont overlap. (Each block is 32x32). Add 10 px to both values so they are within the grid. Grid image has 10px border
            window.draw(red);
        }
        

        // Draw the text
        window.draw(text);

        // Update the window
        window.display();
    }

    return 0;
}
