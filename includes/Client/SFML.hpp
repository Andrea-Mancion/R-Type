/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** SFML
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

#ifndef SFML_HPP_
#define SFML_HPP_

struct SFML_t {
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
