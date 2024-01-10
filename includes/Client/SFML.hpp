/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** SFML
*/

/**
 * @file SFML.hpp
 * @brief SFML class for managing SFML-related resources and operations.
 *
 * This file contains the declaration of the SFML class which encapsulates various SFML
 * resources such as window, events, textures, and sprites. It provides accessors for these
 * resources and methods for adding game entities like ships, enemies, bullets, and handling
 * explosions.
 * 
 * @version 1.0
 * @date 2023-12-24
 * @author Andrea Mancion
 * 
 * @note This file is part of the Epitech Project, B-CPP-500-REN-5-2-rtype-andrea.mancion.
 */

#include "ECS/step.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <random>

#ifndef SFML_HPP_
#define SFML_HPP_

class SFML {
    public:
        sf::RenderWindow& getWindow() { return _window; };
        sf::Event& getEvent() { return _event; };
        sf::Clock& getClock() { return clock; };
        sf::Texture& getBackground() { return background; };
        sf::Sprite& getSprite(int i) { return sprite[i]; };
        sf::Texture& getTextSprite() { return textSprite; };
        sf::Sprite& getSpriteShip() { return spriteShip; };
        sf::Texture& getTextBullet() { return textBullet; };
        sf::Sprite& getSpriteBullet() { return spriteBullet; };
        sf::Texture& getTextEnemy() { return textEnemy; };
        sf::Sprite& getSpriteEnemy() { return spriteEnemy; };
        sf::Texture& getTextEnemyBullet() { return textEnemyBullet; };
        sf::Sprite& getSpriteEnemyBullet() { return spriteEnemyBullet; };
        sf::Texture& getTextBoss() { return textBoss; };
        sf::Sprite& getSpriteBoss() { return spriteBoss; };
        sf::Texture& getTextExplosion() { return textEplosion; };
        sf::Sprite& getSpriteExplosion() { return spriteExplosion; };

        void addAllyShip(Registry &ally, int allyMusicID);
        void addEnemy(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist);
        std::pair<Registry&, bool> addSystemAlly(Registry &ally, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager);
        std::pair<Registry&, bool> addSystemEnemy(Registry &enemy, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager);
        void addExplosion(Registry &reg, float x, float y);
        void addBoss(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID);
        void addBossUltimate(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID, bool isVisible);
        void addBullet(Registry &reg, float x, float y, float bulletSpeed);
        void addBulletBoss(Registry &reg, float x, float y, float bulletSpeed);

    private:
        sf::RenderWindow _window;
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
        sf::Texture textBoss;
        sf::Sprite spriteBoss;
        sf::Texture textEplosion;
        sf::Sprite spriteExplosion;
        sf::Clock clock;
};

#endif /* !SFML_HPP_ */
