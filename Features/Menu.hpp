#ifndef COSC2131_PROJECT_S3445846_S3372771_MENU_HPP
#define COSC2131_PROJECT_S3445846_S3372771_MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;
using namespace std;

class Menu {
private:
    Text title;
    Text play;
    Text records;
    Text howto;
    Text esc;
    int choice;
    Clock time;
    Font font;
    Font font1;

public:
    Menu() {
        choice = 1;
        font.loadFromFile("fonts/OpenSans-Bold.ttf");
        font1.loadFromFile("fonts/Starjedi.ttf");
    }

    // Display the main menu.
    void display(RenderWindow &window, int &c) {
        play.setFont(font); // font is a sf::Font
        title.setFont(font1);

        keyboardInput(c);

        title.setString("SPACE WAR");
        title.setCharacterSize(60); // in pixels, not points!
        title.setColor(sf::Color::Yellow);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        title.setPosition(sf::Vector2f(1024/2.0f,720/8.0f));

        ////
        if (choice == 1)
            play.setString("> PLAY <");
        else
            play.setString("PLAY");

        play.setCharacterSize(30); // in pixels, not points!
        play.setColor(sf::Color::Green);
        play.setStyle(sf::Text::Bold);
        textRect = play.getLocalBounds();
        play.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        play.setPosition(sf::Vector2f(1024/2.0f,720/3.5f));

        /////////////////////
        records.setFont(font); // font is a sf::Font

        if (choice == 2)
            records.setString("> Hall of Fame <");
        else
            records.setString("Hall of Fame");

        records.setCharacterSize(30); // in pixels, not points!
        records.setColor(sf::Color::Green);
        records.setStyle(sf::Text::Bold);
        textRect = records.getLocalBounds();
        records.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        records.setPosition(sf::Vector2f(1024/2.0f,720/2.2f));

        /////////////////////
        howto.setFont(font); // font is a sf::Font

        if (choice == 3)
            howto.setString("> How-to <");
        else
            howto.setString("How-to");

        howto.setCharacterSize(30); // in pixels, not points!
        howto.setColor(sf::Color::Green);
        howto.setStyle(sf::Text::Bold);
        textRect = howto.getLocalBounds();
        howto.setOrigin(textRect.left + textRect.width/2.0f,
                          textRect.top  + textRect.height/2.0f);
        howto.setPosition(sf::Vector2f(1024/2.0f,720/1.5f));

        /////////////////////
        esc.setFont(font); // font is a sf::Font

        if (choice == 4)
            esc.setString("> Exit <");
        else
            esc.setString("Exit");

        esc.setCharacterSize(30); // in pixels, not points!
        esc.setColor(sf::Color::Green);
        esc.setStyle(sf::Text::Bold);
        textRect = esc.getLocalBounds();
        esc.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
        esc.setPosition(sf::Vector2f(1024/2.0f,720/1.2f));

        window.draw(title);
        window.draw(play);
        window.draw(records);
        window.draw(howto);
        window.draw(esc);
    }

    void keyboardInput(int &c) {
        Time levelElapsed = time.getElapsedTime();
        // Move the arrows up in the option list.
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (levelElapsed.asSeconds() >= 0.2) {
                choice--;
                time.restart();
                if (choice < 1)
                    choice = 4;
            }
        }

        // Move the arrows down in the option list.
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (levelElapsed.asSeconds () >= 0.2) {
                choice++;
                time.restart();
                if (choice > 4)
                    choice = 1;
            }
        }

        // Press Enter to make your choice.
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            if (levelElapsed.asSeconds () >= 0.2) {
                switch (choice) {
                    case 1:
                        c = 1;
                        break;
                    case 2:
                        c = 2;
                        break;
                    case 3:
                        c = 3;
                        break;
                    case 4:
                        c = 4;
                        break;
                    default:
                        break;
                }
            }
        }
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_MENU_HPP
