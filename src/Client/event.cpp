/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** event
*/

#include "../../includes/Client/window.hpp"

void Window::shootBullet()
{
    auto &position = ally.get_components<Position>();
    auto &drawable = ally.get_components<Drawanle>();

    if (!textBullet.loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    spriteBullet.setTexture(textBullet);
    spriteBullet.setTextureRect(sf::IntRect(0, 0, 18, 17));
    spriteBullet.setScale(sf::Vector2f(2, 2));
    spriteBullet.setPosition(position[0]->x, position[0]->y);

    std::cout << "shoot bullet from " << spriteBullet.getPosition().x << ", " << spriteBullet.getPosition().y << std::endl;

    auto bulletEntity = ally.spawn_entity();
    ally.add_component(bulletEntity, Position{position[0]->x, position[0]->y});
    ally.add_component(bulletEntity, Drawanle{spriteBullet});

    std::cout << "Yeah it's created with the ID " << bulletEntity << std::endl;
}

void Window::eventHandler()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
            shootBullet();
        }
    }
}