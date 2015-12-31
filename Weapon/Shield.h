//
// Created by corsad on 12/30/15.
//

#ifndef COSC2131_PROJECT_S3445846_S3372771_SHIELD_H
#define COSC2131_PROJECT_S3445846_S3372771_SHIELD_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Shield{
protected:
    Texture shieldIcon;
    Sprite sprite;
    FloatRect bounding;
    int x, y;
public:
    Shield(){
        shieldIcon.loadFromFile("Shield.png");
        shieldIcon.setSmooth(true);
        sprite.setTexture(shieldIcon);
        bounding = sprite.getGlobalBounds();
    }

    void updateShield(int xShip, int yShip){
        x = xShip - 5;
        y = yShip - 35;
        sprite.setPosition(x, y);
    }

    Sprite &getSprite(){
        sprite.setTexture(shieldIcon);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }

    bool checkIntersection(FloatRect r) {
        return bounding.intersects(r);
    }
};
#endif //COSC2131_PROJECT_S3445846_S3372771_SHIELD_H
