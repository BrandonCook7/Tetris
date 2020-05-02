#include "game.h"
#include "tetris.h"

int main() {
    
    RenderWindow w(VideoMode(800, 800), "Tetris");

    Texture bg;
    if (!bg.loadFromFile("images/tetris-bg-darker.jpg")) {
        cout << "ERROR: Failed to load image tetris-bg\n";
    }
    Sprite background(bg);
    
    Font russianFont;
    if(!russianFont.loadFromFile("Russian-Dollmaker.ttf")) {
        cout << "ERROR: Failed to load Russian-Dollmarker.ttf\n";
    }
    
    Text menuText("Tetris", russianFont, 200);

    Text subText("Press Enter to Start", russianFont, 70);
    Text ruleHeader("Rules", russianFont, 60);
    Text rules("1. Use Arrow Keys to Move\n2. Don't let blocks touch top\n3. Blocks move faster each round\n", russianFont, 40);


    menuText.setFillColor(Color::White);
    menuText.setPosition(240, 70);

    subText.setFillColor(Color::White);
    subText.setPosition(225, 360);

    ruleHeader.setFillColor(Color::White);
    ruleHeader.setPosition(350, 450);

    rules.setFillColor(Color::White);
    rules.setPosition(220, 520);

    while (w.isOpen())
    {
        Event e;
        while (w.pollEvent(e))
        {
            if (e.type == Event::Closed || e.key.code == Keyboard::Enter)
                w.close();
        }

        w.clear(Color::White);
        w.draw(background);
        w.draw(subText);
        w.draw(menuText);
        w.draw(ruleHeader);
        w.draw(rules);
        
        w.display();
    }

    tetris test;
    return 0;
}
