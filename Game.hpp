#ifndef COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
#define COSC2131_PROJECT_S3445846_S3372771_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Ship.hpp"
#include "Monster/Monster.hpp"

using namespace sf;

class Game {
private:
    Ship ship;
    Clock clock;
    Texture monsterTexture;
    Texture lazer;
    vector<Monster> monsters;
    vector<Lazer1> weapons;

public:
    Game() {
        monsterTexture.loadFromFile("Monster1 2 HP.png");
        monsterTexture.setSmooth(true);
        lazer.loadFromFile("lazer.png");
        lazer.setSmooth(true);
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
                ship.controlMovement(window);
                window.draw(ship.getSprite());
                // Spawn new monster.
                spawnMonsters(monsters, window, monsterTexture);
                // Check missile collion with monsters.
                ship.checkBulletMonsterCollision(monsters);
                ship.checkLazerPlayerCollision(weapons);
            }
            // Control ship movement.
            window.display();
        }
    }

    void spawnMonsters(vector<Monster> &monsters, RenderWindow &window, Texture &texture) {
        // Spawn monster every 1s.
        Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 1) {
            Monster monster;
            monsters.push_back(monster);
            clock.restart();
        }

        // Remove monster going out of the screen boundary.
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i].getX() >= 1024) {
                monsters.erase(monsters.begin() + i);
            } else {
                monsters[i].move();
                monsters[i].fireBullet(weapons);
                window.draw(monsters[i].getSprite(texture));
            }
        }

        for (unsigned int i = 0; i < weapons.size(); ++i) {
            if (weapons[i].getY() > 720) {
                weapons.erase(weapons.begin() + i);
            } else {
                weapons[i].fire();
                window.draw(weapons[i].getSprite(lazer));
            }
        }
    }
};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
