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
    Font font, title;
    Text again;
    Text level, score;

public:
    GameOver() {
        font.loadFromFile("fonts/OpenSans-Bold.ttf");
        title.loadFromFile("fonts/Starjedi.ttf");

        gameOver.setString("GAME OVER!!!");
        again.setString("Press Esc to continue");
    }

    void display(RenderWindow &window, int lev, int s) {
        gameOver.setFont(title);
        gameOver.setColor(Color::Yellow);
        gameOver.setCharacterSize(80);
        gameOver.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = gameOver.getLocalBounds();
        gameOver.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        gameOver.setPosition(sf::Vector2f(1024 / 2.0f, 720 / 8.0f));

        level.setFont(font);
        level.setString("Level: " + to_string(lev));
        level.setCharacterSize(50);
        level.setStyle(sf::Text::Bold);
        textRect = level.getLocalBounds();
        level.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        level.setPosition(sf::Vector2f(1024/2.0f,720/2.5f));

        score.setFont(font);
        score.setString("Score: " + to_string(s));
        score.setCharacterSize(50);
        score.setStyle(sf::Text::Bold);
        textRect = score.getLocalBounds();
        score.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        score.setPosition(sf::Vector2f(1024/2.0f,720/2.0f));

        again.setFont(font);
        again.setCharacterSize(40);
        again.setColor(Color::Green);
        again.setStyle(sf::Text::Bold);
        textRect = again.getLocalBounds();
        again.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        again.setPosition(sf::Vector2f(1024/2.0f,720/1.5f));

        window.draw(gameOver);
        window.draw(level);
        window.draw(score);
        window.draw(again);
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAMEOVER_HPP
