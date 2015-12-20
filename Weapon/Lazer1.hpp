#ifndef COSC2131_PROJECT_S3445846_S3372771_LAZER1_HPP
#define COSC2131_PROJECT_S3445846_S3372771_LAZER1_HPP

#include "Weapon.hpp"

class Lazer1 : public Weapon {
public:
    Lazer1(int xMon, int yMon, unsigned int xSize, unsigned int ySize, int typeInput) {
        x = xMon + xSize / 3;
        y = yMon + ySize / 7;
        sprite.setPosition(x, y);
        type = typeInput;
    }

    void fire() {
        y += 5;
        sprite.setPosition(x, y);
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_LAZER1_HPP
