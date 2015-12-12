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
    vector<Monster> monsters;

public:
    Game() {
        monsterTexture.loadFromFile("Monster1 2 HP.png");
        monsterTexture.setSmooth(true);
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

            // Spawn new monster.
            spawnMonsters(monsters, window, monsterTexture);
            // Check missile collion with monsters.
            ship.checkCollision(monsters);
            // Control ship movement.
            ship.controlMovement(window);

            window.draw(ship.getSprite());
            window.display();
        }
    }

    void spawnMonsters(vector<Monster> &monsters, RenderWindow &window, Texture &texture) {
        // Spawn monster every 1s.
        Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 1) {
            Monster monster;
            monsters.push_back(monster);
//            Thread t (&Monster::fireBullet, &monster);
//            t.launch();
            clock.restart();
        }

        // Remove monster going out of the screen boundary.
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i].getX() >= 1024) {
                monsters.erase(monsters.begin() + i);
                cout << "Monster removed" << endl;
            } else {
                monsters[i].move();
                window.draw(monsters[i].getSprite(texture));
            }
//
//            for (unsigned int i = 0; i < monsters[i].getWeapons().size(); ++i) {
//                if (monsters[i].getWeapons()[i].getY() > 720) {
//                    monsters[i].getWeapons().erase(monsters[i].getWeapons().begin() + i - 1);
//                } else {
//                    monsters[i].getWeapons()[i].fire();
//                    window.draw(monsters[i].getWeapons()[i].getSprite(texture));
//                }
//            }
        }
    }


};

#endif //COSC2131_PROJECT_S3445846_S3372771_GAME_HPP
