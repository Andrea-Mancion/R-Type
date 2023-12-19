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
    float bulletSpeed = 1.0f;

    if (!textBullet.loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    spriteBullet.setTexture(textBullet);
    spriteBullet.setTextureRect(sf::IntRect(0, 0, 18, 17));
    spriteBullet.setScale(sf::Vector2f(2, 2));
    spriteBullet.setPosition(position[0]->x, position[0]->y);

    std::cout << "shoot bullet from " << spriteBullet.getPosition().x << ", " << spriteBullet.getPosition().y << std::endl;

    auto bulletEntity = ally.spawn_entity();
    ally.add_component(bulletEntity, Position{position[0]->x, position[0]->y});
    ally.add_component(bulletEntity, Velocity{bulletSpeed, 0});
    ally.add_component(bulletEntity, BulletTag{true});
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

void Window::spawn_entity() 
{
    for (int i = 0; i < currentRound * 5; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);
        std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

        auto entityEnnemy = enemy.spawn_entity();
        enemy.add_component(entityEnnemy, Position{1900, static_cast<float>(dis(gen))});
        enemy.add_component(entityEnnemy, Velocity{-0.4, 0});
        enemy.add_component(entityEnnemy, BulletTag{false});
        enemy.add_component(entityEnnemy, Timer{shootDis(gen)});
        enemy.add_component(entityEnnemy, EnemyTag{true});
        enemy.add_component(entityEnnemy, Drawanle{spriteEnemy});
    }
    activeEnnemy = currentRound * 5;
}