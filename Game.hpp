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
#include "Features/Menu.hpp"
#include "Features/GameOver.hpp"
#include "Features/HighScore.hpp"
#include "Features/HowTo.hpp"

using namespace sf;

class Game {
private:
    bool changeLevel, isPaused;
    Ship ship;
    Clock clock, pause;
    Menu menu;
    HowTo howTo;
    GameOver gameOver;
    HighScore db;
    int monsterSize = 0;
    int x = 0;
    int choice = 0;
    Music music;

    Texture background, monsterTexture1, mobLazer1, monsterTexture2;
    Texture mobLazer2, monsterTexture3, mobLazer3, minusIcon;
    Sprite bg, bgNext;
    vector<Monster> monsters;
    vector<int> spawnMonstersList;
    vector<Lazer1> weapons;

    // Minus Health
    vector<MinusHealth> minusList;

    // Level
    Clock levelClock;
    Level level;
    int curLevel = 0;

    Text levelText;
    String levelString;
    Font font;

    // Score
    Text scoreText;
    String scoreString;

    // Score
    Text healthText;
    String healthString;

    Text cont;

public:
    Game() {
        db.listTopTenScores();
        changeLevel = false;
        isPaused = false;
        music.openFromFile("sounds/background.ogg");
        music.play(); music.setLoop(true);

        background.loadFromFile("images/background.jpg");
        cont.setString("GAME PAUSED\n\nPress Esc to continue\n\nPress R to return to main menu");

        monsterTexture1.loadFromFile("images/Monster1 1 HP.png");
        monsterTexture1.setSmooth(true);
        mobLazer1.loadFromFile("images/lazer1.png");
        mobLazer1.setSmooth(true);

        monsterTexture2.loadFromFile("images/Monster2 2 HP.png");
        monsterTexture2.setSmooth(true);
        mobLazer2.loadFromFile("images/lazer2.png");
        mobLazer2.setSmooth(true);

        monsterTexture3.loadFromFile("images/Monster3 3 HP.png");
        monsterTexture3.setSmooth(true);
        mobLazer3.loadFromFile("images/lazer3.png");
        mobLazer3.setSmooth(true);

        minusIcon.loadFromFile("images/ReduceHP.png");
        minusIcon.setSmooth(true);

        font.loadFromFile("fonts/arial.ttf");
    }

    void run() {
        RenderWindow window(VideoMode(1024, 720), "Space War", Style::Close, ContextSettings(32));
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(true);
        glEnable(GL_TEXTURE_2D);
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed){
                    window.close();
                }
                else if (event.type == sf::Event::Resized){
                    // adjust the viewport when the window is resized
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (x < 0)
                x = 1024;

            background.setSmooth(true);
            bg.setTexture(background);
            bg.setPosition(x - 1024, 0);
            bgNext.setTexture(background);
            bgNext.setPosition(x, 0);
            window.draw(bg);
            window.draw(bgNext);

            if (choice == 0) {
                menu.display(window, choice);
            } else if (choice == 1) {
                // Run game until player dies.
                if (!ship.isIsDead()) {
                    Time elap = pause.getElapsedTime();
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        if  (elap.asSeconds() >= 0.5) {
                            isPaused = !isPaused;
                            pause.restart();
                        }
                    } else if (!isPaused) {
                        x--;
                        // Change Level
                        Time levelElapsed = levelClock.getElapsedTime();
                        if (levelElapsed.asSeconds() >= 60 || curLevel == 0) {

                            curLevel++;
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
                        if (spawnMonstersList.size() == 0 || changeLevel) {
                            level.addMonster(spawnMonstersList, curLevel);
                            monsterSize = (int) spawnMonstersList.size();
                            changeLevel = false;
                        }

                        ship.controlMovement(window);
                        window.draw(ship.getSprite());

                        // Spawn new monster.
                        if (spawnMonstersList.size() != 0 && monsters.size() <= 20) {
                            spawnMonsters(monsters, window, spawnMonstersList.at(spawnMonstersList.size() - 1));
                            spawnMonstersList.pop_back();
                        }

                        drawShipAndBullet(window);

                        // check Shield
                        if (ship.isShieldUp()) {
                            ship.checkLazerShieldCollision(weapons);
                            window.draw(ship.getShield().getSprite());
                            ship.turnShieldOff();
                        }

                        // check GiantLazer
                        if (ship.isGiantLazerUp()) {
                            ship.checkGiantLazerCollision(weapons, monsters);
                            window.draw(ship.getGiantLazer().getSprite());
                            ship.turnLazerOff();
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
                    } else {
                        cont.setFont(font);
                        cont.setCharacterSize(50); // in pixels, not points!
                        cont.setColor(sf::Color::Green);
                        cont.setStyle(sf::Text::Bold);
                        auto textRect = cont.getLocalBounds();
                        cont.setOrigin(textRect.left + textRect.width/2.0f,
                                      textRect.top  + textRect.height/2.0f);
                        cont.setPosition(sf::Vector2f(1024/2.0f,720/2.0f));
                        window.draw(cont);

                        if (Keyboard::isKeyPressed(Keyboard::R)) {
                            monsters.clear();
                            spawnMonstersList.clear();
                            weapons.clear();
                            minusList.clear();
                            curLevel = 0;
                            ship.setScore(0);
                            choice = 0;
                            ship.getMissiles().clear();
                            ship.setHealth(100);
                            ship.setIsDead(false);
                            isPaused = false;
                        }
                    }

                } else {
                    // Clear the monster, player, bullets.
                    monsters.clear();
                    spawnMonstersList.clear();
                    weapons.clear();
                    minusList.clear();

                    gameOver.display(window, curLevel, ship.getScore());
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        db.saveResult(curLevel, ship.getScore());
                        db.listTopTenScores();

                        curLevel = 0;
                        ship.setScore(0);
                        choice = 0;
                        ship.setHealth(100);
                        ship.setIsDead(false);
                    }
                }
            } else if (choice == 2) {
                db.print(window);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    choice = 0;
                }
            } else if (choice == 3) {
                howTo.display(window);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    choice = 0;
                }
            } else { exit(EXIT_SUCCESS); }

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
    }

    void drawShipAndBullet(RenderWindow &window){
        // Remove monster going out of the screen boundary.
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i].getX() >= 1024 || monsters[i].getX() <= -1) {
                monsters.erase(monsters.begin() + i);
            } else {
                if(monsters[i].getType() !=3){
                    monsters[i].move();
                }
                else {
                    monsters[i].followShip(ship.getX());
                }
                monsters[i].fireBullet(weapons);

                // Assign texture for monster
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
                    default:break;
                }
            }
        }

        for (unsigned int i = 0; i < weapons.size(); ++i) {
            if (weapons[i].getY() > 720) {
                weapons.erase(weapons.begin() + i);
            } else {
                weapons[i].fire();

                // Assign texture for monster's weapon
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
                    default:break;
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
