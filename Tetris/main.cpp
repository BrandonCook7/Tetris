#include "game.h"
#include "tetris.h"
int main() {
    sf::RenderWindow w(sf::VideoMode(800, 800), "Tetris");

    sf::Font russianFont;
    russianFont.loadFromFile("Russian-Dollmaker.ttf");

    sf::Texture bg;
    if (!bg.loadFromFile("images/tetris-bg.jpg")) {
        cout << "unable to load image tetris-bg" << endl;
    }
    sf::Sprite background(bg);
    w.draw(background);

    while (w.isOpen())
    {
        Event e;
        while (w.pollEvent(e))
        {
            if (e.type == Event::Closed)
                w.close();
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Enter)
                    w.close();
            }
        }

        sf::Text menuText("Tetris", russianFont, 200);

        sf::Text subText("Press Enter to Start", russianFont, 70);
        sf::Text ruleHeader("Rules", russianFont, 60);
        sf::Text rules("1. Use Arrow Keys to Move\n2. Don't let blocks touch top\n3. Blocks move faster each round\n", russianFont, 40);


        menuText.setFillColor(sf::Color::Black);
        menuText.setPosition(240, 70);

        subText.setFillColor(sf::Color::Black);
        subText.setPosition(225, 360);

        ruleHeader.setFillColor(sf::Color::Black);
        ruleHeader.setPosition(350, 450);

        rules.setFillColor(sf::Color::Black);
        rules.setPosition(220, 520);

        w.draw(subText);
        w.draw(menuText);
        w.draw(ruleHeader);
        w.draw(rules);
    }

    tetris test;
    return 0;
}

/* old test menu
void menu(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");
    sf::Text menuText("Menu", font, 50);
    menuText.setFillColor(sf::Color::Black);
    menuText.setPosition(400, 100);
    window.draw(menuText);
}
*/