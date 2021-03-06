#ifndef COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
#define COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Weapon/Missile.hpp"
#include "Monster/Monster.hpp"
#include "Monster/MinusHealth.h"
#include "Weapon/Shield.h"
#include "Weapon/GiantLazer.h"

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
    int score;
    int health;

    // Shield
    bool shieldUp;
    Shield shield;
    float immuTime = 0.5;
    Clock immuTimer;

    // Giant Lazer
    bool canShootLazer = false;
    bool giantLazerUp;
    GiantLazer giantLazer;
    float fireTime = 0.5;
    Clock firingTimer;
    int nextScore = 1;

    SoundBuffer rocket;
    Sound rocketSound;

public:
    Ship() {
        score = 0;
        health = 100;
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

    vector<Missile> &getMissiles() {
        return missiles;
    }

    int getX() const {
        return x;
    }

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        Ship::score = score;
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

    bool isIsDead() const {
        return isDead;
    }

    bool isGiantLazerUp() const {
        return giantLazerUp;
    }

    GiantLazer &getGiantLazer() {
        return giantLazer;
    }

    void setIsDead(bool isDead) {
        Ship::isDead = isDead;
    }

    void setHealth(int health) {
        Ship::health = health;
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
                rocketSound.setVolume(50);
                rocketSound.play();
                Missile missile1 {x, y, shipTexture.getSize().x, shipTexture.getSize().y, 2};
                Missile missile2 {x, y, shipTexture.getSize().x, shipTexture.getSize().y, 10};
                missiles.push_back(missile1); missiles.push_back(missile2);
                clock.restart();
            }
        }

        // Fire Lazer
        if (Keyboard::isKeyPressed(Keyboard::C)) {
            if(canShootLazer){
                fireGiantLazer();
            }
        }

        fire(window);

        if (x > 924)
            x = 924;
        else if (x < 0)
            x = 0;

        // Update Shield's position
        if(shieldUp){
            shield.updateShield(x,y);
        }

        // Update Lazer's position
        if(giantLazerUp){
            giantLazer.updateGiantLazer(x,y);
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

                        // if score reach 100, 200, 300... Player can shoot Lazer 1
                        if(score >= nextScore * 100){
                            canShootLazer = true;
                            nextScore++;
                        }
                    }
                        missiles[j].setY(-10);
                }
            }
        }
    }

    // Activate Lazer
    void fireGiantLazer(){
        giantLazerUp = true;
        canShootLazer = false;
        firingTimer.restart();
    }

    void checkLazerPlayerCollision(vector<Lazer1> &lazers) {
        // Check lazer collision with ship.
        for (int i = 0; i < lazers.size(); ++i) {
            if (bounding.intersects(lazers[i].getBounding())) {
                Time hitTime = immuTimer.getElapsedTime();

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

    // Remove bullet that hit shield
    void checkLazerShieldCollision(vector<Lazer1> &lazers) {
        // Check lazer collision with ship.
        for (int i = 0; i < lazers.size(); ++i) {
            if (shield.checkIntersection(lazers[i].getBounding())) {
                lazers[i].setY(721);
            }
        }
    }

    // Remove monster and bullet that hit Lazer, add Point based on Monster removed
    void checkGiantLazerCollision(vector<Lazer1> &lazers, vector<Monster> &monsters){
        // Check monster
        for (int i = 0; i < monsters.size(); ++i) {
                if (monsters[i].checkIntersection(giantLazer.getBounding())) {
                    monsters[i].reduceHealth();
                    if (monsters[i].getHealth() <= 0){
                        monsters[i].setX(1024);
                        score += monsters[i].getScore();
                        // if score reach 100, 200, 300... Player can shoot Lazer 1
                        if(score >= nextScore * 100){
                            canShootLazer = true;
                            nextScore++;
                        }
                    }
                }
        }

        // Check Lazer
        for (int i = 0; i < lazers.size(); ++i) {
            if (giantLazer.checkIntersection(lazers[i].getBounding())) {
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

    void turnLazerOff(){
        Time hitTime = firingTimer.getElapsedTime();
        if(hitTime.asSeconds() >= fireTime){
            giantLazerUp = false;
        }
    }

    const Sprite &getSprite() {
        sprite.setTexture(shipTexture);
        bounding = sprite.getGlobalBounds();
        return sprite;
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_SHIP_HPP
