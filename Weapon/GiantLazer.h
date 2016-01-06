//
// Created by corsad on 06/01/2016.
//

#ifndef COSC2131_PROJECT_S3445846_S3372771_GIANTLAZER_H
#define COSC2131_PROJECT_S3445846_S3372771_GIANTLAZER_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GiantLazer{
protected:
    Texture lazerIcon;
    Sprite sprite;
    FloatRect bounding;
    int x, y;

public:
    GiantLazer(){
        lazerIcon.loadFromFile("images/GiantLaser.png");
        lazerIcon.setSmooth(true);
        sprite.setTexture(lazerIcon);
        bounding = sprite.getGlobalBounds();
    }

    void updateGiantLazer(int xShip, int yShip){
        x = xShip - 5;
        y = 500;
        sprite.setPosition(x, y);
    }

    Sprite &getSprite(){
        sprite.setTexture(lazerIcon);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }

    bool checkIntersection(FloatRect r) {
        return bounding.intersects(r);
    }

    const FloatRect &getBounding() const {
        return bounding;
    }
};
#endif //COSC2131_PROJECT_S3445846_S3372771_GIANTLAZER_H
