/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** shipExplode
*/

#include "../../includes/Client/window.hpp"

void Window::destructionShipBoss(float x, float y)
{
    auto &position = enemy.get_components<Position>();

    if (!textEplosion.loadFromFile("includes/assets/sprites/r-typesheet44.gif"))
        std::cout << "Error" << std::endl;
    spriteExplosion.setTexture(textEplosion);
    spriteExplosion.setTextureRect(sf::IntRect(120, 0, 35, 40));
    spriteExplosion.setScale(sf::Vector2f(2, 2));
    spriteExplosion.setPosition(x, y);

    addExplosion(enemy, spriteExplosion, x, y);
}