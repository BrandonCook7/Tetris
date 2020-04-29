#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int grid[20][10] = {0};

typedef struct coordinate {
    int x;
    int y;
} Coordinate;

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

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");

    // Set the Icon
//    sf::Image icon;
//    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
//        return EXIT_FAILURE;
//    }
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture block;
    if (!block.loadFromFile("images/block.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(block);
    sprite.setColor(sf::Color(0,255,0));
    
    sf::Sprite red(block);
    red.setColor(sf::Color(255,0,0));
    
    
    sf::Texture background;
    if (!background.loadFromFile("images/bg.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite bg(background);
    
    
    // Create a graphical text to display
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

        // Draw the sprites
        
        sprite.setPosition(42, 42); //board is 10 px in on each side
        red.setPosition(10,10);
        
        
        window.draw(bg);
        window.draw(sprite);
        window.draw(red);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return 0;
}
