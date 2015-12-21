#ifndef COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
#define COSC2131_PROJECT_S3445846_S3372771_GAME_HPP

#include <SFML/System.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Ship.hpp"
#include "Monster/Monster.hpp"
#include "Level.h"

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
    Clock levelClock;
    Level level;
    int curLevel = 1;
    bool changeLevel = false;
    bool spawnMonster = true;
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
                if(levelElapsed.asSeconds () >= 10){

                    curLevel += 1;
                    changeLevel = true;
                    // Print Current level here
                    levelClock.restart();
                }

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

                    // if Monster should spawn
                    if(spawnMonster){
                        spawnMonstersList.pop_back();
                    }
                }
                // Check missile collion with monsters.
                ship.checkBulletMonsterCollision(monsters);
                ship.checkLazerPlayerCollision(weapons);
            }
            // Control ship movement.
            window.display();
        }
    }

    void spawnMonsters(vector<Monster> &monsters, RenderWindow &window, int type) {
        // Spawn monster every 1s.
        Time elapsed = clock.getElapsedTime();
        float monsterSpawnTime = (float)10 / monsterSize * 1000;
        if (elapsed.asMilliseconds () >= monsterSpawnTime) {
            Monster monster(type);
            monsters.push_back(monster);
            clock.restart();
            spawnMonster = true;
        } else {
            spawnMonster = false;
        }

        // Remove monster going out of the screen boundary.
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i].getX() >= 1024) {
                monsters.erase(monsters.begin() + i);
            } else {
                monsters[i].move();
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


};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
