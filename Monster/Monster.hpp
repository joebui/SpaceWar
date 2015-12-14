#ifndef COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP
#define COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include "../Weapon/Lazer1.hpp"

using namespace sf;
using namespace std;

class Monster {
private:
    Sprite sprite;
    // Weapon texture.
    Texture texture;
    FloatRect bounding;
    Clock fireClock;
    int x;
    int y;
    int health;

public:
    Monster() {
        texture.loadFromFile("lazer.png");
        texture.setSmooth(true);
        x = 0;
        y = rand() % 300;
        health = 1;

        sprite.setPosition(x, y);
    }

    void move() {
        x += 5;
        sprite.setPosition(x, y);
    }

    void reduceHealth() {
        health--;
    }

    bool checkIntersection(FloatRect r) {
        return bounding.intersects(r);
    }

    void fireBullet(vector<Lazer1> &weapons) {
        Time fire = fireClock.getElapsedTime();
        if (fire.asSeconds() >= 1) {
            Lazer1 lazer1 (x, y, texture.getSize().x, texture.getSize().y);
            weapons.push_back(lazer1);
            fireClock.restart();
        }
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        Monster::x = x;
    }

    int getHealth() const {
        return health;
    }

    const Sprite &getSprite(Texture &texture) {
        sprite.setTexture(texture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP
