#include "game.h"


void menu() {

    sf::RenderWindow w(sf::VideoMode(800, 800), "Tetris");

    sf::Font russianFont;
    russianFont.loadFromFile("Russian-Dollmaker.ttf");

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


    sf::Texture bg;
    if (!bg.loadFromFile("images/tetris-bg.jpg")) {

    }
    sf::Sprite background(bg);
    w.draw(background);

    w.draw(subText);
    w.draw(menuText);
    w.draw(ruleHeader);
    w.draw(rules);
}
