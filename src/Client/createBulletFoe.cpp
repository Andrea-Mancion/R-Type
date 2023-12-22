/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** createBulletFoe
*/

#include "../../includes/Client/functions.hpp"

void Window::shootEnemyBullet(int i, float x, float y) 
{
    float bulletSpeed = -1.0f;

    if (!textEnemyBullet.loadFromFile("includes/assets/sprites/r-typesheet14.gif"))
        std::cout << "Error" << std::endl;
    spriteEnemyBullet.setTexture(textEnemyBullet);
    spriteEnemyBullet.setTextureRect(sf::IntRect(0, 135, 10, 17));
    spriteEnemyBullet.setScale(sf::Vector2f(2, 2));
    spriteEnemyBullet.setPosition(x, y);

    addBullet(enemy, spriteEnemyBullet, x, y, bulletSpeed);
}

void Window::enemy_shooting(float dt)
{
    auto [position, timers] = getComponent<Position, Timer>(enemy);

    for (size_t i = 0; i < position.size() && i < timers.size(); i++) {
        if (position[i] && timers[i]) {
            auto &timer = timers[0];
            timer->elapsedTime += dt;

            if (timer->elapsedTime >= timer->shootInterval) {
                shootEnemyBullet(i, position[i]->x, position[i]->y);
                timer->elapsedTime = 0.0f;
                std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);
                timer->shootInterval = shootDis(rd);
            }
        }
    } 
}