/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** window
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
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
        bool isAnyAllyShipLeft() const;
        void enemy_shooting(float dt);
        void shootEnemyBullet(int i, float x, float y);
        void startNextRound();
        void spawn_entity_boss();
        void destructionShipBoss(float x, float y);
        void updateMusic();

    private:
        sf::RenderWindow _window;
        Registry ally;
        Registry enemy;
        MusicManager musicManager;
        sf::Event _event;
        sf::Texture background;
        sf::Sprite sprite[3];
        sf::Texture textSprite;
        sf::Sprite spriteShip;
        sf::Texture textBullet;
        sf::Sprite spriteBullet;
        sf::Texture textEnemy;
        sf::Sprite spriteEnemy;
        sf::Texture textEnemyBullet;
        sf::Sprite spriteEnemyBullet;
        std::random_device rd;
        sf::Texture textBoss;
        sf::Sprite spriteBoss;
        sf::Texture textEplosion;
        sf::Sprite spriteExplosion;
        int activeAlly = 0;
        int currentRound = 1;
        int activeEnnemy = 0;
        int maxEnnemyKilled = 0;
        int allyMusicID;
        int bossMusicID;
        int bossHP[2] = {1, 1};
        sf::Clock clock;
        bool hasSongStarted = false;
        bool bossStarted = false;
};

std::streambuf *redirectCoutToFile(const std::string &filename);
void resetCout(std::streambuf *backup);
Registry registerComponentAlly(Registry &ally);
Registry registerComponentEnemy(Registry &enemy);
// std::pair<Registry&, bool> addSystemAlly(Registry &ally, bool &hasSongStarted, bool &bossStarted, sf::RenderWindow &window, MusicManager &musicManager);
// std::pair<Registry&, bool> addSystemEnemy(Registry &ally, bool &hasSongStarted, bool &bossStarted, sf::RenderWindow &window, MusicManager &musicManager);
#endif /* !WINDOW_HPP_ */
