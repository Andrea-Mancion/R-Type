/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** level
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Checks and updates the game level based on the boss timer.
 *
 * This function checks the value of the boss timer (`bossTimer[1]`) and updates the game level
 * accordingly. It changes the background and enemy sprite depending on the boss timer value.
 * The function ensures that the level check is performed only once during the specified boss timer values.
 *
 * If the boss timer is equal to 1, the function sets the background to "SpacePlanet.png" and updates
 * the enemy sprite to "r-typesheet9.gif".
 *
 * If the boss timer is equal to 2, the function sets the background to "BlackHole.png" and updates
 * the enemy sprite to "r-typesheet23.gif".
 *
 * The function sets `canCheckLevel` to false after performing the level check to prevent repeated checks.
 */

void Window::checkLevel()
{
    if (bossTimer[1] == 1 && canCheckLevel) {
        if (!_sfml.getBackground().loadFromFile("includes/assets/SpacePlanet.png"))
            std::cout << "Error" << std::endl;
        _sfml.getSprite(0).setTexture(_sfml.getBackground());
        _sfml.getSprite(0).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
        _sfml.getSprite(1).setTexture(_sfml.getBackground());
        _sfml.getSprite(1).setTextureRect(sf::IntRect(_sfml.getBackground().getSize().x, 0, -_sfml.getBackground().getSize().x, _sfml.getBackground().getSize().y));
        _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
        _sfml.getSprite(2).setTexture(_sfml.getBackground());
        _sfml.getSprite(2).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(2).setPosition(sf::Vector2f(-1920, 0));

        if (!_sfml.getTextEnemy().loadFromFile("includes/assets/sprites/r-typesheet9.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteEnemy().setTexture(_sfml.getTextEnemy());
        _sfml.getSpriteEnemy().setTextureRect(sf::IntRect(0, 0, 56, 52));
        _sfml.getSpriteEnemy().setScale(sf::Vector2f(3, 3));

    } else if (bossTimer[1] == 2 && canCheckLevel) {
        if (!_sfml.getBackground().loadFromFile("includes/assets/BlackHole.png"))
            std::cout << "Error" << std::endl;
        _sfml.getSprite(0).setTexture(_sfml.getBackground());
        _sfml.getSprite(0).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
        _sfml.getSprite(1).setTexture(_sfml.getBackground());
        _sfml.getSprite(1).setTextureRect(sf::IntRect(_sfml.getBackground().getSize().x, 0, -_sfml.getBackground().getSize().x, _sfml.getBackground().getSize().y));
        _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
        _sfml.getSprite(2).setTexture(_sfml.getBackground());
        _sfml.getSprite(2).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(2).setPosition(sf::Vector2f(-1920, 0));

        if (!_sfml.getTextEnemy().loadFromFile("includes/assets/sprites/r-typesheet23.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteEnemy().setTexture(_sfml.getTextEnemy());
        _sfml.getSpriteEnemy().setTextureRect(sf::IntRect(0, 0, 32, 20));
        _sfml.getSpriteEnemy().setScale(sf::Vector2f(3, 3));
    }
    canCheckLevel = false;
}