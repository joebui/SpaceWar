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
    Text esc;
    int choice;
    Clock c;
    Font font;
    Font font1;

public:
    Menu() {
        choice = 1;
        font.loadFromFile("fonts/OpenSans-Bold.ttf");
        font1.loadFromFile("fonts/Starjedi.ttf");
    }

    void display(RenderWindow &window, bool &g) {
        play.setFont(font); // font is a sf::Font
        title.setFont(font1);

        keyboardInput(g);

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
        records.setPosition(sf::Vector2f(1024/2.0f,720/1.8f));

        /////////////////////
        esc.setFont(font); // font is a sf::Font

        if (choice == 3)
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
        window.draw(esc);
    }

    void keyboardInput(bool &g) {
        Time levelElapsed = c.getElapsedTime();
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (levelElapsed.asSeconds() >= 0.2) {
                choice--;
                c.restart();
                if (choice < 1)
                    choice = 3;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (levelElapsed.asSeconds () >= 0.2) {
                choice++;
                c.restart();
                if (choice > 3)
                    choice = 1;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            if (levelElapsed.asSeconds () >= 0.2) {
                switch (choice) {
                    case 1:
                        g = true;
                        break;
                    case 2:
                        break;
                    case 3:
                        exit(EXIT_SUCCESS);
                    default:
                        break;
                }
            }
        }
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_MENU_HPP
