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

    if (!_sfml.textEplosion.loadFromFile("includes/assets/sprites/r-typesheet44.gif"))
        std::cout << "Error" << std::endl;
    _sfml.spriteExplosion.setTexture(_sfml.textEplosion);
    _sfml.spriteExplosion.setTextureRect(sf::IntRect(120, 0, 35, 40));
    _sfml.spriteExplosion.setScale(sf::Vector2f(2, 2));
    _sfml.spriteExplosion.setPosition(x, y);

    addExplosion(enemy, _sfml.spriteExplosion, x, y);
}