#include "tetris.h"

tetris::tetris()
{
    RenderWindow window(VideoMode(800, 800), "Tetris In C++"); // creates window
    timer = 0; // timer
    delay = 0.3; // delay in milliseconds
    Clock clock; // clock
    hasSpawned = 0;
    // Load textures and sprites
    // Blocks.jpg has 7 blocks of different color. Tried using just a grey scale image and setColor, but it made blocks too dark. This way allows us to change color by changing what part of the image a sprite uses
   
    Texture blockTexture;
    if (!blockTexture.loadFromFile("images/blocks.jpg")) {
        cout << "Unable to open images/blocks.jpg" << endl;
    }
    blockTexture.setSmooth(true);
    Sprite sprite(blockTexture);//block sprite

    Texture gridTexture;
    if (!gridTexture.loadFromFile("images/grid.jpg")) {
        cout << "Unable to open images/grid.jpg" << endl;
    }
    Sprite gridSprite(gridTexture);//boundary sprite

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();//gets elasped time since executable started
        clock.restart();//restarts
        timer += time;//adds time to the timer
        // Process events
        Event event;
        while (window.pollEvent(event)) {//checks events

            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) window.close();//exits window
                if (event.key.code == Keyboard::Left) dx = -1;//moves left
                if (event.key.code == Keyboard::Right) dx = 1;//moves right
                if (event.key.code == Keyboard::Up) needsRotation = true;//rotates
                if (event.key.code == Keyboard::Down) delay = 0.05;//increases downward speed
            }
        }

        move();//moves position of block sprite using current and previous arrays
        if (grid[1][1] != 0) { // game over. hit top part
            gameState = 0;
        }

        if (checkWin() == 0) {
            window.close();
        }
        spawn(sprite);//sets color and position
        if (needsRotation && randNum != 1 && (current[0].x != 0 && current[1].x != 0 && current[2].x != 0 && current[3].x != 0 && current[0].x != 9 && current[1].x != 9 && current[2].x != 9 && current[3].x != 9)) rotate();//rotates
    
        //if timer passes the delay of the timer.
        //moves block sprite down 1
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                prev[i] = current[i];//sets the current coordinates to the previosu coordinates array
                current[i].y += 1;//moves the entire sprite one block down
            }
            if (!checkBounds()) // block has hit boundaries
            {
                for (int i = 0; i < 4; i++) {
                    current[i].y = prev[i].y;//reverts back to previous position
                    grid[current[i].y][current[i].x] = randNum+ 1;
                }
                hasSpawned = 0;
            }
            timer = 0;//resets timer
        }
        checkLines();//adds score and clears line completed
        dx = 0; needsRotation = false; delay = 0.3;//resets every variable

        // Clear screen
        window.clear(Color::White);
        window.draw(gridSprite);

        //sets position of blocks already placed on the bottom
        //and draws them on screen
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
            {
                if (grid[i][j] == 0) continue;
                sprite.setTextureRect(IntRect(grid[i][j] * 32, 0, 32, 32));
                sprite.setPosition(j * 32 + 10, i * 32 + 10);
                window.draw(sprite);
            }

        // Draws block sprite in correct spot
        for (int i = 0; i < 4; i++) {
            sprite.setPosition(current[i].x * 32 + 10, current[i].y * 32 + 10); // multiply by 32 so the block's dont overlap. (Each block is 32x32). Add 10 px to both values so they are within the grid. Grid image has 10px border
            window.draw(sprite);
        }
        // display score here
        displayScore(window);
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
            if (grid[i][j] != 0)
            {
                count++;
            }
            grid[temp][j] = grid[i][j];
        }
        if (count < 10)
            temp--;
        else
            score += 100;
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

void tetris::spawn(Sprite& sprite) {
    if (hasSpawned == 0) { // check if a block has been spawned already
        randNum = rand() % 7;
        sprite.setTextureRect(IntRect(randNum * 32, 0, 32, 32)); // set color of sprite
        for (int i = 0; i < 4; i++) {
            current[i].x = shapes[randNum][i].x;
            current[i].y = shapes[randNum][i].y;
        }
        hasSpawned = 1;
    }
}

void tetris::displayScore(RenderWindow &window)
{
    Font russianFont;
    if (!russianFont.loadFromFile("Russian-Dollmaker.ttf")) {//Loads text
        cout << "ERROR: Failed to load Russian-Dollmarker.ttf\n";
    }
    string Score = to_string(score);
    Text curScoreText(Score, russianFont, 70);//Creates score text
    Text textText("Score: ", russianFont, 70);// text statement
   
    //Sets all text color and position
    curScoreText.setFillColor(Color::Black);
    curScoreText.setPosition(600, 300);

    textText.setFillColor(Color::Black);
    textText.setPosition(550, 200);

    window.draw(textText);
    window.draw(curScoreText);

}

int tetris::checkWin() {
    return gameState;
}

void tetris::displayFinalScore()
{
    RenderWindow endWindow(VideoMode(800, 800), "End");
    string winStatement;//creates string statement that tells whether player won or lost
    if (gameState == 0)//based on gamestate
        winStatement = "You Lost Tetris!";
    winStatement = "You Win Tetris!";

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

    Text winText(winStatement, russianFont, 70);//Creates win statement
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

