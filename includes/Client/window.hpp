/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** window
*/

#include "SFML.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "step.hpp"

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

class Window {
    public:
        Window();
        ~Window();
        void startProject();
        void eventHandler();
        void shootBullet();
        void loadSprites();
        void spawn_entity_foe();
        void checkCollision();
        bool isAnyAllyShipLeft();
        void enemy_shooting(float dt);
        void shootEnemyBullet(int i, float x, float y);
        void startNextRound();
        void spawn_entity_boss();
        void destructionShipBoss(float x, float y);
        void updateMusic();

    private:
        SFML _sfml;
        Registry ally;
        Registry enemy;
        MusicManager musicManager;
        std::random_device rd;
        int activeAlly = 0;
        int currentRound = 1;
        int activeEnnemy = 0;
        int maxEnnemyKilled = 0;
        int allyMusicID;
        int bossMusicID;
        int bossHP[2] = {1, 1};
        bool hasSongStarted = false;
        bool bossStarted = false;
};
#endif /* !WINDOW_HPP_ */
