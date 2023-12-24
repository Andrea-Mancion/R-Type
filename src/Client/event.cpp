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

    if (!_sfml.getTextBullet().loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteBullet().setTexture(_sfml.getTextBullet());
    _sfml.getSpriteBullet().setTextureRect(sf::IntRect(0, 0, 18, 17));
    _sfml.getSpriteBullet().setScale(sf::Vector2f(2, 2));

    addBullet(ally, _sfml.getSpriteBullet(), position[0]->x, position[0]->y, bulletSpeed);
}

void Window::eventHandler()
{
    while (_sfml.getWindow().pollEvent(_sfml.getEvent())) {
        if (_sfml.getEvent().type == sf::Event::Closed)
            _sfml.getWindow().close();
        if (_sfml.getEvent().type == sf::Event::KeyPressed && _sfml.getEvent().key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
            shootBullet();
        }
    }
}