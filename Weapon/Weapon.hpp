#ifndef COSC2131_PROJECT_S3445846_S3372771_WEAPON_HPP
#define COSC2131_PROJECT_S3445846_S3372771_WEAPON_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Weapon {
protected:
    Sprite sprite;
    FloatRect bounding;
    int x, y;
    int type;

public:
    virtual void fire() {}

    const Sprite &getSprite(Texture &texture) {
        sprite.setTexture(texture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Weapon::y = y;
    }

    int getType() const {
        return type;
    }

    const FloatRect &getBounding() const {
        return bounding;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_WEAPON_HPP
