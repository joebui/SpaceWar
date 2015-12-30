#ifndef COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP
#define COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include "../Weapon/Lazer1.hpp"
#include "../Ship.hpp"

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
    int type;
    float shootTimer;
    int score;

public:
    Monster() {
        texture.loadFromFile("lazer1.png");
        texture.setSmooth(true);
        x = 0;
        y = rand() % 300;
        health = 1;
        shootTimer = ((float) rand()) / (float) (RAND_MAX / 1);
        sprite.setPosition(x, y);
        score = 1;
    }

    Monster(int type): type{type}{
        switch (type){
            case 1:
                texture.loadFromFile("lazer1.png");
                texture.setSmooth(true);
                health = 1;
                score = 1;
                break;
            case 2:
                texture.loadFromFile("lazer2.png");
                texture.setSmooth(true);
                health = 2;
                score = 3;
                break;
            case 3:
                texture.loadFromFile("lazer3.png");
                texture.setSmooth(true);
                health = 3;
                score = 10;
                break;
        }


        x = 0;
        y = rand() % 300;
        shootTimer = ((float) rand()) / (float) (RAND_MAX / 1);
        sprite.setPosition(x, y);
    }

    void move() {
        x += 5;
        sprite.setPosition(x, y);
    }

    void followShip(int shipX){
        if (x > shipX) {
            x -= 3;
        }
        else {
            x += 3;
        }
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

        switch(type){
            case 3:
                if (fire.asSeconds() >= 1.5) {
                    Lazer1 lazer1 (x, y, texture.getSize().x, texture.getSize().y, type);
                    weapons.push_back(lazer1);
                    fireClock.restart();
                }

                break;
            default:
                if (fire.asSeconds() >= shootTimer) {
                    Lazer1 lazer1 (x, y, texture.getSize().x, texture.getSize().y, type);
                    weapons.push_back(lazer1);
                    fireClock.restart();
                    shootTimer = ((float) rand()) / (float) (RAND_MAX / 1);
                }
                break;
        }
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        Monster::x = x;
    }

    int getY() const {
        return y;
    }

    int getHealth() const {
        return health;
    }

    int getType() const {
        return type;
    }

    int getScore() const {
        return score;
    }

    Sprite &getSprite(Texture &texture) {
        sprite.setTexture(texture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_MONSTER_HPP
