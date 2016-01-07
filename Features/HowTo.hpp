#ifndef COSC2131_PROJECT_S3445846_S3372771_HOWTO_HPP
#define COSC2131_PROJECT_S3445846_S3372771_HOWTO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

using namespace sf;

class HowTo {
private:
    Font font;
    Text title, howTo, info;

public:
    HowTo() {
        font.loadFromFile("fonts/OpenSans-Bold.ttf");
    }

    void display(RenderWindow &window) {
        title.setFont(font);

        title.setString("HOW-TO");
        title.setCharacterSize(60); // in pixels, not points!
        title.setColor(sf::Color::Yellow);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = title.getLocalBounds();
        title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        title.setPosition(sf::Vector2f(1024/2.0f,720/8.0f));

        howTo.setFont(font);
        howTo.setString("Use LEFT and RIGHT arrow to move the ship.\n"
                                "Hold SPACE to fire.\n"
                                "You can press Esc at anytime to pause the game.\n"
                                "When your score reach 100, 200, 300 or, ... you can \n"
                                "press C to fire a big lazer beam for only once.\n\n"
                                "The game will be endless until your health reaches 0.");
        howTo.setStyle(sf::Text::Bold);
        textRect = howTo.getLocalBounds();
        howTo.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        howTo.setPosition(sf::Vector2f(1024/2.0f,720/2.0f));

        info.setFont(font);
        info.setString("Press Esc to return");
        info.setCharacterSize(30); // in pixels, not points!
        info.setColor(Color::Green);
        textRect = info.getLocalBounds();
        info.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        info.setPosition(sf::Vector2f(1024/2.0f,720/1.2f));

        window.draw(title);
        window.draw(howTo);
        window.draw(info);
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_HOWTO_HPP
