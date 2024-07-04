

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>          //#includee <time.h> is a header file in C and C++ programming languages that contains various functions related to time and date manipulation.
#include "utils.h"         //a header file that contains declarations of functions, variables, or other constructs that are needed in a C++ program.
#include "pieces.h"        //These declarations may include the names of the pieces, their movements, and any other relevant information about them.
#include "functionality.h" //used to include external header files that contain declarations of functions, variables, and other constructs that are needed in a program.
#include <fstream>         //used to include the standard C++ library header file that provides input and output operations on files
#include <string.h>        //preprocessor directive in C and C++ programming languages that includes the string manipulation functions in the standard C library.
using namespace sf;        // tells the compiler that the code will use the sf namespace, so there's no need to specify it every time you use an SFML function or object.
using namespace std;
int main()
{
    srand(time(0));                                  // is a C++ function that is used to seed the random number generator. The time(0) function is used to generate a seed value for the random number generator based on the current time.
    RenderWindow window(VideoMode(320, 480), title); // creates a RenderWindow object named window with a specified size of 320x480 pixels and a specified title.
    Texture obj1, obj2, obj3, obj4, obj5, obj6;      // class in SFML library used to render images on the screen using sprites
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj1.loadFromFile("img/tiles.png"); // loads an image file named "tiles.png" from the "img" folder into a Texture object called obj1.
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/Menu.jpg");
    obj5.loadFromFile("img/pause.jpg");
    obj6.loadFromFile("img/gameover.jpg");
    Sprite sprite(obj1), background(obj2), frame(obj3), Shadow(obj1), next(obj1), main_display(obj4), pause_menu(obj5), over(obj6);
    int delta_x = 0, colorNum = 1, colorNum_1 = 1, level = 1;
    float timer = 0, delay = 0.3, timer_1 = 0;
    bool rotate = 0, pause = 0, hard_drop = 0, bombing = 0, close = 0;
    int score = 0;
    int shadow[4][2], next_piece[4][2];
    sf::Font Algerian;                         // font used for rendering text in SFML.The variable will be used to store a font named Algerian
    Algerian.loadFromFile("img/Algerian.ttf"); // used to load a font file named "Algerian.ttf" from the "img" directory.
    sf::Text my_text;                          // an instance of the class that can be used to display and manipulate text
    my_text.setFont(Algerian);
    fstream myFile;                        // an instance of the class that can be used to handle file operations.
    Clock clock;                           // instance can be used to track and measure time,
    Music music, lineclear_s;              // classes to handle audio files or music playback.
    music.openFromFile("Music/sound.wav"); // audio file to be opened and loaded for playback.
    while (window.isOpen())                // This code structure allows for a continuously updated window display and enables the program to respond to keyboard input, particularly the "Enter" key, to control the flow of execution.
    {
        window.clear(Color::Black);                  // clears the contents of the window with a black color. This ensures a clean slate for rendering new content.
        window.draw(main_display);                   // draws the main_display object onto the window.
        window.display();                            // updates the window to show the newly drawn content.
        if (Keyboard::isKeyPressed(Keyboard::Enter)) // If the "Enter" key is pressed, the break statement is executed,
            break;
    }
    music.play();         // music object is an instance of a class responsible for audio playback, such as the sf::Music
    bool cricket = false; // declares a boolean variable named "cricket" and initializes it with the value false.
    while (window.isOpen())
    {
        while (1 && !cricket) // The while (1 && !cricket) condition creates a loop that continues to execute as long as the condition 1 && !cricket evaluates to true. The value 1 is equivalent to true in C++, and !cricket checks if the cricket variable is currently false.
        {
            window.clear(Color::White); // clears the contents of the window with a white color.
            window.draw(main_display);  // draws the main_display object onto the window.
            window.display();           // updates the window to show the newly drawn content.
            Event f;                    // // Event is occurring - until the game is in running state
            while (window.pollEvent(f))
            {                                // Event is occurring - until the game is in running state
                if (f.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // Opened window disposes
                if (f.type == Event::KeyPressed)
                {                                      // If any other key (not cross) is pressed
                    if (f.key.code == Keyboard::Enter) // Check if the other key pressed is UP key
                    {
                        cricket = true; // If the condition is true, the cricket variable is set to true, breaking the loop and ending the program or transitioning to the next section of code outside the loop.
                        break;
                    }
                }
            }
        }
        float time = clock.getElapsedTime().asSeconds(); // retrieves the elapsed time
        clock.restart();
        timer += time;
        timer_1 += time;
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            {                                           // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                    rotate = true;                      // Rotation gets o
                else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                    delta_x = -1;                       // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                    delta_x = 1;
                else if (e.key.code == Keyboard::P)
                    pause = true;
                else if (e.key.code == Keyboard::Space)
                    hard_drop = true;
                // Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && !bombing) // Just another way to detect key presses without event listener
            delay = 0.05;                                       // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        if (Keyboard::isKeyPressed(Keyboard::P))                // checks the current state of a specified key.
            while (pause)
            {
                window.clear(Color::White); // Clears the contents of the window, filling it with a white color.
                window.draw(pause_menu);    // representation of a pause menu or screen.
                window.display();
                if (Keyboard::isKeyPressed(Keyboard::C)) // performs several actions like resetting the score, level, and some variables
                    break;
                if (Keyboard::isKeyPressed(Keyboard::N)) // close or exit the game.
                {
                    score = 0;
                    level = 1;
                    varreset(delay, level); // initialize certain variables or settings related to the game or program
                    restart_game();
                    break;
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    close = true;
                    break;
                }
            }
        if (close)
        {
            close = false; // done to ensure that the window is closed only once,
            window.close();
        }
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        get_level(score, level, delay); // designed to calculate or determine the appropriate level based on the current score

        fallingPiece(timer, timer_1, delay, colorNum, &bombing, score, colorNum_1, next_piece); // represent elapsed time or countdowns.,timing of falling game pieces.,representation of the falling game piece.
        if (!bombing)                                                                           // checks if bombing is not true.
        {
            move(delta_x); // horizontal movement by a specific distance.
            if (rotate)    // perform a rotation operation.
                rotation(rotate);
            if (hard_drop) // object is instantly moved to the lowest possible position.
                hard_ddrop(hard_drop);
        }
        lineclear(score);       // updating the score based on the number of lines cleared
        rowplacement();         // responsible for handling the placement or positioning of rows in a game or application.
        varreset(delay, level); // designed to reset or initialize certain variables
        varreset(rotate);       // resetting the rotate variable.
        varreset(hard_drop);    // resetting the hard_drop variable.
        disp_shadow(shadow);    // displaying or handling the shadow of an object or element.
        if (!checkgameover())
        {
            bool check = true;
            while (check)
            {
                window.clear(Color::White); // Clears the contents of the window, filling it with a white color.
                window.draw(over);
                window.display();                             // Updates the window to display the changes made in the previous steps.
                if (Keyboard::isKeyPressed(Keyboard::Escape)) // the intention to close the game, and breaks out of the while loop
                {
                    close = true;
                    break;
                }

                if (close)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::N))
                {
                    level = 1;
                    varreset(delay, level);
                    restart_game();
                    break;
                }
            }
            static int i = 0;
            High_Score[i] = score;
            i++;
            myFile.open("img/Score_Cout.txt", ios::app); // Edit
            if (myFile.is_open())
            {
                myFile << High_Score[i - 1] << endl;
            }
            myFile.close();
            if (i == 10)
                i = 0;
            score = 0;
            clock.restart();
        }
        std::string string_scoring = std::to_string(score);
        sf::Text Score(string_scoring, Algerian);
        Score.setCharacterSize(20);
        Score.setFillColor(sf::Color::Black);
        Score.setPosition(265, 70);
        sf::Text text;
        text.setFont(Algerian);
        text.setString("SCORE:");
        text.setCharacterSize(27);
        text.setFillColor(sf::Color::Black);
        text.setPosition(240, 20);
        std::string string_level = std::to_string(level);
        sf::Text Level(string_level, Algerian);
        Level.setCharacterSize(20);
        Level.setFillColor(sf::Color::Black);
        Level.setPosition(265, 135);
        sf::Text text_1;
        text_1.setFont(Algerian);
        text_1.setString("LEVEL:");
        text_1.setCharacterSize(27);
        text_1.setFillColor(sf::Color::Black);
        text_1.setPosition(240, 100);
        sf::Text text_2;
        text_2.setFont(Algerian);
        text_2.setString("NEXT\nBLOCK:");
        text_2.setCharacterSize(23);
        text_2.setFillColor(sf::Color::Black);
        text_2.setPosition(240, 190);
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        window.clear(Color::Black);
        window.draw(background);

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }
        for (int i = 0; i < 4; i++)
        {
            Shadow.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            Shadow.setColor(sf::Color(0, 0, 0, 135));
            Shadow.setPosition(shadow[i][0] * 18, shadow[i][1] * 18);
            Shadow.move(28, 31);
            window.draw(Shadow);
        }
        for (int i = 0; i < 4; i++)
        {
            next.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            next.setPosition(next_piece[i][0] * 18, next_piece[i][1] * 18);
            next.move(240, 270);
            window.draw(next);
        }
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(Score);
        window.draw(Level);
        window.draw(text_1);
        window.draw(text_2);
        window.draw(text);
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
