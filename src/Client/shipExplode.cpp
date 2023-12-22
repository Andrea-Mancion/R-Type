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

    auto explosion = enemy.spawn_entity();
    enemy.add_component(explosion, Position{x, y});
    enemy.add_component(explosion, Velocity{0, 0});
    enemy.add_component(explosion, BulletTag{false});
    enemy.add_component(explosion, Timer{0.0f});
    enemy.add_component(explosion, EnemyTag{false});
    enemy.add_component(explosion, BossTag{false});
    enemy.add_component(explosion, ExplosionTag{true});
    enemy.add_component(explosion, Drawable{spriteExplosion});
}