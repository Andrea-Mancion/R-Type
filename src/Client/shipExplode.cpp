/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** shipExplode
*/

#include "../../includes/Client/functions.hpp"

void Window::destructionShipBoss(float x, float y)
{
    auto [position] = getComponent<Position>(enemy);

    if (!_sfml.getTextExplosion().loadFromFile("includes/assets/sprites/r-typesheet44.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteExplosion().setTexture(_sfml.getTextExplosion());
    _sfml.getSpriteExplosion().setTextureRect(sf::IntRect(120, 0, 35, 40));
    _sfml.getSpriteExplosion().setScale(sf::Vector2f(2, 2));
    _sfml.getSpriteExplosion().setPosition(x, y);

    _sfml.addExplosion(enemy, x, y);
}