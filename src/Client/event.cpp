/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** event
*/

#include "../../includes/Client/functions.hpp"

void Window::shootBullet()
{
    auto [position] = getComponent<Position>(ally);
    float bulletSpeed = 1.0f;

    if (!_sfml.textBullet.loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    _sfml.spriteBullet.setTexture(_sfml.textBullet);
    _sfml.spriteBullet.setTextureRect(sf::IntRect(0, 0, 18, 17));
    _sfml.spriteBullet.setScale(sf::Vector2f(2, 2));

    addBullet(ally, _sfml.spriteBullet, position[0]->x, position[0]->y, bulletSpeed);
}

void Window::eventHandler()
{
    while (_sfml._window.pollEvent(_sfml._event)) {
        if (_sfml._event.type == sf::Event::Closed)
            _sfml._window.close();
        if (_sfml._event.type == sf::Event::KeyPressed && _sfml._event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
            shootBullet();
        }
    }
}