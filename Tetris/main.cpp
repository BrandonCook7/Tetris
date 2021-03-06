#include "game.h"
#include "tetris.h"

int main() {
    srand(time(0));
    RenderWindow w(VideoMode(800, 800), "Main");//Creates Main Window

    Texture bg;
    if (!bg.loadFromFile("images/tetris-bg-darker.jpg")) {//Loads Tetris Menu Background
        cout << "ERROR: Failed to load image tetris-bg\n";//If Failed Prints out error message
    }
    Sprite background(bg);

    Font russianFont;
    if (!russianFont.loadFromFile("Russian-Dollmaker.ttf")) {//Loads text
        cout << "ERROR: Failed to load Russian-Dollmarker.ttf\n";
    }

    Text menuText("Tetris", russianFont, 200);//Creates menu text Title

    Text subText("Press Enter to Start", russianFont, 70);
    Text ruleHeader("Rules", russianFont, 60);
    Text rules("1. Use Arrow Keys to Move\n2. Don't let blocks touch top\n3. Each full row completed is 100 points\n", russianFont, 40);

    //Sets all text color and position
    menuText.setFillColor(Color::White);
    menuText.setPosition(240, 70);

    subText.setFillColor(Color::White);
    subText.setPosition(200, 360);

    ruleHeader.setFillColor(Color::White);
    ruleHeader.setPosition(350, 450);

    rules.setFillColor(Color::White);
    rules.setPosition(180, 520);

    while (w.isOpen())//while the window is open
    {
        Event e;
        while (w.pollEvent(e))//Constantly checks for event
        {
            if (e.type == Event::Closed || e.key.code == Keyboard::Enter)//If enter key is entered it closed the screen
                w.close();
        }

        w.clear(Color::White);
        //Draws text
        w.draw(background);
        w.draw(subText);
        w.draw(menuText);
        w.draw(ruleHeader);
        w.draw(rules);

        w.display();//Displays all visuals
    }

    tetris test;//starts tetris game for player
    test.displayFinalScore();//displays the score to the player
    return 0;
}
