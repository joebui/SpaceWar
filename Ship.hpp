#ifndef COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
#define COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapon/Missile.hpp"
#include "Monster/Monster.hpp"

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
    Clock clock;

public:
    Ship() {
        shipTexture.loadFromFile("Spaceship.png");
        shipTexture.setSmooth(true);
        missileTexture.loadFromFile("missile.png");
        missileTexture.setSmooth(true);

        sprite.setTexture(shipTexture);

        x = 1024 / 2;
        y = 630;
        sprite.setPosition(x, y);
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
                Missile missile {x, y, shipTexture.getSize().x, shipTexture.getSize().y};
                missiles.push_back(missile);
                clock.restart();
            }
        }

        fire(window);

        if (x > 924)
            x = 924;
        else if (x < 0)
            x = 0;

        sprite.setPosition(x, y);
    }

    void fire(RenderWindow &window) {
        for (unsigned int i = 0; i < missiles.size(); ++i) {
            if (missiles[i].getY() < 0) {
                missiles.erase(missiles.begin() + i);
                cout << "Missile removed" << endl;
            } else {
                missiles[i].fire();
                window.draw(missiles[i].getSprite(missileTexture));
            }
        }
    }

    void checkCollision(vector<Monster> &monsters) {
        for (int i = 0; i < monsters.size(); ++i) {
            for (int j = 0; j < missiles.size(); ++j) {
                if (monsters[i].checkIntersection(missiles[j].getBounding())) {
                    monsters[i].reduceHealth();
                    if (monsters[i].getHealth() <= 0)
                        monsters[i].setX(1024);

                    missiles[j].setY(-10);
                }
            }
        }
    }

    const Sprite &getSprite() const {
        return sprite;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
