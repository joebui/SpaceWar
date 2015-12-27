//
// Created by corsad on 12/27/15.
//

#ifndef COSC2131_PROJECT_S3445846_S3372771_MINUSHEALTH_H
#define COSC2131_PROJECT_S3445846_S3372771_MINUSHEALTH_H
#include <SFML/Graphics.hpp>
#include <thread>

using namespace sf;
using namespace std;
class MinusHealth{
protected:
    Sprite sprite;
    FloatRect bounding;
    int x,y;
    Clock showClock;

public:

    MinusHealth(int x, int y): x{x}, y{y}{
        showClock.restart();
        sprite.setPosition(x, y);
    }

    void move(){
        y -= 1;
        sprite.setPosition(x, y);
    }

    Sprite &getSprite(Texture &texture) {
        sprite.setTexture(texture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }

    void checkTimer(){
        Time showed = showClock.getElapsedTime();
        if (showed.asSeconds() >= 1) {
            y = 721;
        }
    }
    int getY() const {
        return y;
    }

    void setY(int y) {
        MinusHealth::y = y;
    }
};
#endif //COSC2131_PROJECT_S3445846_S3372771_MINUSHEALTH_H
