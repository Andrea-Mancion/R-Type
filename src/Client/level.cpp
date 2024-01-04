/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** level
*/

#include "../../includes/Client/functions.hpp"

void Window::checkLevel()
{
    if (bossTimer[1] == 1 && canCheckLevel) {
        if (!_sfml.getBackground().loadFromFile("includes/assets/SpacePlanet.png"))
            std::cout << "Error" << std::endl;
        _sfml.getSprite(0).setTexture(_sfml.getBackground());
        _sfml.getSprite(0).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
        _sfml.getSprite(1).setTexture(_sfml.getBackground());
        _sfml.getSprite(1).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
        _sfml.getSprite(2).setTexture(_sfml.getBackground());
        _sfml.getSprite(2).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
        _sfml.getSprite(2).setPosition(sf::Vector2f(-1920, 0));

        if (!_sfml.getTextEnemy().loadFromFile("includes/assets/sprites/r-typesheet9.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteEnemy().setTexture(_sfml.getTextEnemy());
        _sfml.getSpriteEnemy().setTextureRect(sf::IntRect(0, 0, 50, 50));
        _sfml.getSpriteEnemy().setScale(sf::Vector2f(3, 3));

        canCheckLevel = false;
    }
}