#ifndef COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
#define COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Weapon/Missile.hpp"
#include "Monster/Monster.hpp"
#include "Monster/MinusHealth.h"
#include "Weapon/Shield.h"

using namespace sf;
using namespace std;

class Ship {
private:
    Texture shipTexture;
    Texture missileTexture;
    Sprite sprite;
    FloatRect bounding;
    vector<Missile> missiles;
    int x, y;
    bool isDead;
    Clock clock;
    int score = 0;
    int health = 1;
    Clock immuTimer;
    bool shieldUp;
    Shield shield;
    float immuTime = 0.5;

    SoundBuffer rocket;
    Sound rocketSound;

public:
    Ship() {
        shipTexture.loadFromFile("images/Spaceship.png");
        shipTexture.setSmooth(true);
        missileTexture.loadFromFile("images/missile.png");
        missileTexture.setSmooth(true);

        sprite.setTexture(shipTexture);
        bounding = sprite.getGlobalBounds();

        rocket.loadFromFile("sounds/rocket.wav");

        x = 1024 / 2;
        y = 630;
        isDead = false;
        sprite.setPosition(x, y);
        shieldUp = false;
    }


    int getX() const {
        return x;
    }

    int getScore() const {
        return score;
    }

    int getHealth() const {
        return health;
    }

    Shield &getShield() {
        return shield;
    }

    bool isShieldUp() const {
        return shieldUp;
    }

// Move the ship with keyboard.
    void controlMovement(RenderWindow &window) {
        // Move right.
        if (Keyboard::isKeyPressed(Keyboard::Right))
            x += 7;
        // Move left.
        if (Keyboard::isKeyPressed(Keyboard::Left))
            x -= 7;

        // Fire rocket.
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            // get time passed
            Time elapsed = clock.getElapsedTime();
            // if 0.5 sec has passed, shoot
            if(elapsed.asSeconds() >= 0.5){
                rocketSound.setBuffer(rocket);
                rocketSound.play();
                Missile missile1 {x, y, shipTexture.getSize().x, shipTexture.getSize().y, 2};
                Missile missile2 {x, y, shipTexture.getSize().x, shipTexture.getSize().y, 10};
                missiles.push_back(missile1); missiles.push_back(missile2);
                clock.restart();
            }
        }

        fire(window);

        if (x > 924)
            x = 924;
        else if (x < 0)
            x = 0;

        if(shieldUp){
            shield.updateShield(x,y);
        }

        sprite.setPosition(x, y);
    }

    void fire(RenderWindow &window) {
        // Fire missiles.
        for (unsigned int i = 0; i < missiles.size(); ++i) {
            if (missiles[i].getY() < 0) {
                missiles.erase(missiles.begin() + i);
            } else {
                missiles[i].fire();
                window.draw(missiles[i].getSprite(missileTexture));
            }
        }
    }

    void checkBulletMonsterCollision(vector<Monster> &monsters, vector<MinusHealth> &minusList) {
        // Check collision with monsters.
        for (int i = 0; i < monsters.size(); ++i) {
            for (int j = 0; j < missiles.size(); ++j) {
                if (monsters[i].checkIntersection(missiles[j].getBounding())) {
                    monsters[i].reduceHealth();
                    MinusHealth healthReducedIcon {monsters[i].getX(), monsters[i].getY()};
                    minusList.push_back(healthReducedIcon);
                    if (monsters[i].getHealth() <= 0){
                        monsters[i].setX(1024);
                        score += monsters[i].getScore();
                    }
                        missiles[j].setY(-10);
                }
            }
        }
    }

    void checkLazerPlayerCollision(vector<Lazer1> &lazers) {
        // Check lazer collision with ship.
        for (int i = 0; i < lazers.size(); ++i) {
            if (bounding.intersects(lazers[i].getBounding())) {
                Time hitTime = immuTimer.getElapsedTime();

                cout << "Hit player" << endl;
                lazers[i].setY(721);
                if(hitTime.asSeconds() >= immuTime){
                    health -= lazers[i].getType();
                    if(health <= 0){
                        missiles.clear();
                        isDead = true;
                    }
                    immuTimer.restart();
                    shieldUp = true;
                }
            }
        }
    }

    void checkLazerShieldCollision(vector<Lazer1> &lazers) {
        // Check lazer collision with ship.
        for (int i = 0; i < lazers.size(); ++i) {
            if (shield.checkIntersection(lazers[i].getBounding())) {
                lazers[i].setY(721);
            }
        }
    }

    void turnShieldOff(){
        Time hitTime = immuTimer.getElapsedTime();
        if(hitTime.asSeconds() >= immuTime){
            shieldUp = false;
        }
    }

    const Sprite &getSprite() {
        sprite.setTexture(shipTexture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }

    bool isIsDead() const {
        return isDead;
    }

    void setIsDead(bool isDead) {
        Ship::isDead = isDead;
    }

    void setHealth(int health) {
        Ship::health = health;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
