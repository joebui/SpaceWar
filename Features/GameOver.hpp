//
// Created by Bui Quang Dien on 1/1/16.
//

#ifndef COSC2131_PROJECT_S3445846_S3372771_GAMEOVER_HPP
#define COSC2131_PROJECT_S3445846_S3372771_GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;
using namespace std;

class GameOver {
private:
    Text gameOver;
    Font font;
    Text again;
    Clock c;

public:
    GameOver() {
        font.loadFromFile("fonts/OpenSans-Bold.ttf");
    }

    void display(RenderWindow &window) {
        gameOver.setFont(font);
        gameOver.setString("GAME OVER :(");
        gameOver.setColor(Color::Yellow);
        gameOver.setCharacterSize(80);
        gameOver.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = gameOver.getLocalBounds();
        gameOver.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        gameOver.setPosition(sf::Vector2f(1024 / 2.0f, 720 / 8.0f));

        again.setFont(font);
        again.setString("Press Esc to continue");
        again.setCharacterSize(30);
        again.setColor(Color::Green);
        again.setStyle(sf::Text::Bold);
        textRect = again.getLocalBounds();
        again.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        again.setPosition(sf::Vector2f(1024/2.0f,720/2.5f));

        window.draw(gameOver);
        window.draw(again);
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAMEOVER_HPP
