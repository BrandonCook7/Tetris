#include "game.h"

int game::checkWin()
{
    return 1;
}

void game::displayFinalScore()
{
    RenderWindow endWindow(VideoMode(800, 800), "End");
    string winStatement;//creates string statement that tells whether player won or lost
    if (gameState == 0)//based on gamestate
        winStatement = "You Lost!";
    winStatement = "You Win!";

    string Score = to_string(score);//converts integer to string
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
    
    Text winText(winStatement, russianFont, 200);//Creates win statement
    Text pointsText("You Scored: ", russianFont, 70);//creates points statement
    Text scoreText(Score, russianFont, 70);//creates score text
   
    //Sets all text color and position
    winText.setFillColor(Color::Black);
    winText.setPosition(240, 70);

    pointsText.setFillColor(Color::Black);
    pointsText.setPosition(225, 360);

    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(225, 360);

    while (endWindow.isOpen())//while the window is open
    {
        Event e;
        while (endWindow.pollEvent(e))//Constantly checks for event
        {
            if (e.type == Event::Closed)//Iif it escapes
                endWindow.close();
        }
        endWindow.clear(Color::White);
        //Draws text
        endWindow.draw(winText);
        endWindow.draw(pointsText);
        endWindow.draw(scoreText);
        endWindow.display();//Displays all visuals
    }

}
