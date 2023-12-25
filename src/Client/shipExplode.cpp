/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** shipExplode
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Handles the destruction animation of a boss ship.
 *
 * This method is responsible for triggering the explosion animation when a boss ship is destroyed.
 * It sets up the explosion sprite using a specific texture and positions it at the location of the
 * destroyed boss ship.
 *
 * The method begins by loading the explosion texture from a specified file. If the texture loading
 * fails, it outputs an error message. Once the texture is set, the explosion sprite's appearance
 * is configured by setting the texture rectangle, scale, and initial position based on the provided
 * coordinates (x, y).
 *
 * Finally, the explosion is added to the game with a call to `_sfml.addExplosion`, which integrates
 * the explosion animation into the game's dynamics, such as rendering and possibly affecting other
 * game entities.
 *
 * @param x The x-coordinate for the initial position of the explosion.
 * @param y The y-coordinate for the initial position of the explosion.
 */

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