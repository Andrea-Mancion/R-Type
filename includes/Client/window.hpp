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
#include <iostream>
#include <random>
#include "step.hpp"

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

class Window {
    public:
        Window();
        ~Window() = default;
        void startProject();
        void eventHandler();
        void shootBullet();
        void loadSprites();
        void spawn_entity();
        void checkCollision();
        bool isAnyAllyShipLeft() const;

    private:
        sf::RenderWindow _window;
        Registry ally;
        Registry enemy;
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
        int activeAlly = 0;
        int activeEnnemy = 0;
        const int maxEnnemy = 5;
};

#endif /* !WINDOW_HPP_ */
