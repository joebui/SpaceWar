//
// Created by Tan on 16/12/15.
//

#ifndef COSC2131_PROJECT_S3445846_S3372771_LEVEL_H
#define COSC2131_PROJECT_S3445846_S3372771_LEVEL_H

#include "Monster/Monster.hpp"

class Level{
private:

public:

    void addMonster(vector<int> &spawnMonsters, int curLevel){
        spawnMonsters.clear();
        switch(curLevel) {
            case 1:
                // 5 monster level 1
                for (int i = 0; i < 5; i++) {
                    spawnMonsters.push_back(1);
                }

                break;

            case 2:
                // 10 monster level 1
                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }
                break;

            case 3:
                // 5 monster 1 and 1 monster 2 every 5 second
                for (int i = 0; i < 5; i++) {
                    spawnMonsters.push_back(1);
                }
                spawnMonsters.push_back(2);

                break;

            case 4:
                // 10 monster 1 and 1 monster 2 every 5 second
                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }
                for (int i = 0; i < 2; i++) {
                    spawnMonsters.push_back(2);
                }

                break;

            case 5:
                // 10 monster 1 and 3 monster 2 every 5 second
                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }
                for (int i = 0; i < 3; i++) {
                    spawnMonsters.push_back(2);
                }
                break;

            case 6:
                // 20 monster 1 every 5 second
                for (int i = 0; i < 20; i++) {
                    spawnMonsters.push_back(1);
                }
                break;

            case 7:
                // 10 monster 1 and 1 monster 3 every 5 second
                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }

                spawnMonsters.push_back(3);
                break;

            case 8:
                // 10 monster 1, 1 monster 2 and 1 monster 3 every 5 second
                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }
                spawnMonsters.push_back(2);
                spawnMonsters.push_back(3);
                break;

            case 9:
                // 5 monster 2 and 1 monster 3 every 5
                for (int i = 0; i < 5; i++) {
                    spawnMonsters.push_back(2);
                }
                spawnMonsters.push_back(3);
                break;

            case 10:
                // 10 monster 1 spawn every 5 second, 1 boss
                // TODO boss

                for (int i = 0; i < 10; i++) {
                    spawnMonsters.push_back(1);
                }

                break;

            default:
                // 5 mons 1, 1 mons 2 and 1 mons 3 (+1 for every every level)
                int amount = curLevel - 11;
                for (int i = 0; i < 5 + amount; i++) {
                    spawnMonsters.push_back(1);
                }
                for (int i = 0; i < 1 + amount; i++) {
                    spawnMonsters.push_back(2);
                }
                for (int i = 0; i < 1 + amount; i++) {
                    spawnMonsters.push_back(3);
                }
                break;

        }
    }
};
#endif //COSC2131_PROJECT_S3445846_S3372771_LEVEL_H
