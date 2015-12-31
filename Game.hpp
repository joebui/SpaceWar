#ifndef COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
#define COSC2131_PROJECT_S3445846_S3372771_GAME_HPP

#include <SFML/System.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <sstream>
#include "Ship.hpp"
#include "Monster/Monster.hpp"
#include "Level.h"
#include "Monster/MinusHealth.h"

using namespace sf;

class Game {
private:
    Ship ship;
    Clock clock;
    Texture monsterTexture1;
    Texture mobLazer1;
    Texture monsterTexture2;
    Texture mobLazer2;
    Texture monsterTexture3;
    Texture mobLazer3;
    vector<Monster> monsters;
    vector<int> spawnMonstersList;
    int monsterSize;
    vector<Lazer1> weapons;

    // Minus Health
    Texture minusIcon;
    vector<MinusHealth> minusList;

    // Level
    Clock levelClock;
    Level level;
    int curLevel = 0;
    bool changeLevel = false;

    Text levelText;
    String levelString;
    Font font;

    // Score
    Text scoreText;
    String scoreString;

    // Score
    Text healthText;
    String healthString;
public:
    Game() {
        monsterTexture1.loadFromFile("Monster1 1 HP.png");
        monsterTexture1.setSmooth(true);
        mobLazer1.loadFromFile("lazer1.png");
        mobLazer1.setSmooth(true);

        monsterTexture2.loadFromFile("Monster2 2 HP.png");
        monsterTexture2.setSmooth(true);
        mobLazer2.loadFromFile("lazer2.png");
        mobLazer2.setSmooth(true);

        monsterTexture3.loadFromFile("Monster3 3 HP.png");
        monsterTexture3.setSmooth(true);
        mobLazer3.loadFromFile("lazer3.png");
        mobLazer3.setSmooth(true);

        minusIcon.loadFromFile("ReduceHP.png");
        minusIcon.setSmooth(true);

        font.loadFromFile("arial.ttf");
    }

    void run() {
        RenderWindow window(VideoMode(1024, 720), "Space War", Style::Default, ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        glEnable(GL_TEXTURE_2D);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                else if (event.type == sf::Event::Resized)
                    // adjust the viewport when the window is resized
                    glViewport(0, 0, event.size.width, event.size.height);
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Run game until player dies.
            if (!ship.isIsDead()) {

                // Change Level
                Time levelElapsed = levelClock.getElapsedTime();
                if(levelElapsed.asSeconds () >= 10 || curLevel == 0){

                    curLevel += 1;
                    changeLevel = true;
                    // Print Current level here
                    levelClock.restart();
                    setLevelText();
                }

                // Draw Level String
                window.draw(levelText);

                // Draw Score String
                setScoreText();
                window.draw(scoreText);

                // Draw Health String
                setHealthText();
                window.draw(healthText);

                // check for spawnMonster vector size
                if(spawnMonstersList.size() == 0 || changeLevel){
                    level.addMonster(spawnMonstersList, curLevel);
                    monsterSize = spawnMonstersList.size();
                    changeLevel = false;
                }

                ship.controlMovement(window);
                window.draw(ship.getSprite());
                // Spawn new monster.

                if(spawnMonstersList.size() != 0){
                    spawnMonsters(monsters, window, spawnMonstersList.at(spawnMonstersList.size() -1 ));
                    spawnMonstersList.pop_back();
                }

                // check Shield
                if(ship.isShieldUp()){
                    ship.checkLazerShieldCollision(weapons);
                    window.draw(ship.getShield().getSprite());
                    ship.turnShieldOff();
                }

                // Check missile collion with monsters.
                ship.checkBulletMonsterCollision(monsters, minusList);
                ship.checkLazerPlayerCollision(weapons);

                //Show Hit Icon
                for (unsigned int i = 0; i < minusList.size(); ++i) {
                    if (minusList[i].getY() > 720) {
                        minusList.erase(minusList.begin() + i);
                    } else {
                        minusList[i].move();
                        window.draw(minusList[i].getSprite(minusIcon));
                        minusList[i].checkTimer();
                    }
                }
            }
            // Control ship movement.
            window.display();
        }
    }

    void spawnMonsters(vector<Monster> &monsters, RenderWindow &window, int type) {
        // Spawn monster every 1s.
        Time elapsed = clock.getElapsedTime();

        float monsterSpawnTime = (float) 10 / monsterSize * 1000;

        if (elapsed.asMilliseconds () >= monsterSpawnTime) {
            Monster monster(type);
            monsters.push_back(monster);
            clock.restart();
        }

        // Remove monster going out of the screen boundary.
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i].getX() >= 1024) {
                monsters.erase(monsters.begin() + i);
            } else {
                if(monsters[i].getType() !=3){
                    monsters[i].move();
                }
                else {
                    monsters[i].followShip(ship.getX());
                }
                monsters[i].fireBullet(weapons);

                switch (monsters[i].getType()){
                    case 1:
                        window.draw(monsters[i].getSprite(monsterTexture1));
                        break;
                    case 2:
                        window.draw(monsters[i].getSprite(monsterTexture2));
                        break;
                    case 3:
                        window.draw(monsters[i].getSprite(monsterTexture3));
                        break;
                }
            }
        }

        for (unsigned int i = 0; i < weapons.size(); ++i) {
            if (weapons[i].getY() > 720) {
                weapons.erase(weapons.begin() + i);
            } else {
                weapons[i].fire();

                switch (weapons[i].getType()){
                    case 1:
                        window.draw(weapons[i].getSprite(mobLazer1));
                        break;
                    case 2:
                        window.draw(weapons[i].getSprite(mobLazer2));
                        break;
                    case 3:
                        window.draw(weapons[i].getSprite(mobLazer3));
                        break;
                }


            }
        }
    }

    void setLevelText(){
        // Set Level String Data
        stringstream type;
        type << curLevel;
        levelString = "Level : " + type.str();
        levelText.setString(levelString);
        levelText.setCharacterSize(30);
        levelText.setStyle(sf::Text::Bold);
        levelText.setFont(font);
        levelText.setPosition(10, 2);
    }

    void setScoreText(){
        // Set Level String Data
        stringstream type;
        type << ship.getScore();
        scoreString = "Score : " + type.str();
        scoreText.setString(scoreString);
        scoreText.setCharacterSize(30);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setFont(font);
        scoreText.setPosition(850, 2);
    }

    void setHealthText(){
        // Set Level String Data
        stringstream type;
        type << ship.getHealth();
        healthString = "Health : " + type.str();
        healthText.setString(healthString);
        healthText.setCharacterSize(30);
        healthText.setStyle(sf::Text::Bold);
        healthText.setFont(font);
        healthText.setPosition(400, 2);
    }

};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
