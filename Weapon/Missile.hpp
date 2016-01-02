#ifndef COSC2131_PROJECT_S3445846_S3372771_MISSILE_HPP
#define COSC2131_PROJECT_S3445846_S3372771_MISSILE_HPP

#include <SFML/Graphics.hpp>
#include "Weapon.hpp"

using namespace sf;

class Missile : public Weapon {
public:
    Missile(int xShip, int yShip, unsigned int xSize, unsigned int ySize, int xDiv) {
        x = xShip + xSize / xDiv;
        y = yShip + ySize / 7;
        sprite.setPosition(x, y);
    }

    void fire() {
        y -= 7;
        sprite.setPosition(x, y);
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_MISSILE_HPP
