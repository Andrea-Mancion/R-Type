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

/**
 * @file WINDOW_HPP
 * @brief Header file defining the Window class for game management.
 *
 * This header file declares the Window class which encapsulates the game logic,
 * event handling, entity management, and interactions within a game. It controls
 * game flow, such as starting the game, handling user input, managing entity
 * spawning, collisions, and rounds.
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

/**
 * @class Window
 * @brief Manages the main game window and game state.
 *
 * The Window class is responsible for the creation of the game window,
 * handling game events, and managing the game state. It provides methods
 * to handle game logic such as shooting bullets, spawning enemies, checking
 * for collisions, and updating game rounds.
 * 
 * @version 1.0
 * @date 2023-12-25
 * @author Andrea Mancion
 * 
 * @note This file is part of the Epitech Project, B-CPP-500-REN-5-2-rtype-andrea.mancion.
 */

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
