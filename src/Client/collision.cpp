/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** collision
*/

#include "../../includes/Client/window.hpp"

static sf::FloatRect getBoundingBox(const sf::Sprite &sprite)
{
    return sprite.getGlobalBounds();
}

static bool collisions(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    return getBoundingBox(sprite1).intersects(getBoundingBox(sprite2));
}

void Window::startNextRound()
{
    currentRound++;
    maxEnnemyKilled = 0;
    if (currentRound % 5 != 0)
        spawn_entity();
    else {
        bossHP[0] *= 2;
        bossHP[1] = bossHP[0];
        spawn_entity_boss();
    }
}

void Window::checkCollision() 
{
    auto &allyPosition = ally.get_components<Position>();
    auto &allyDrawable = ally.get_components<Drawanle>();
    auto &allyBullet = ally.get_components<BulletTag>();
    auto &ennemyPosition = enemy.get_components<Position>();
    auto &ennemyDrawable = enemy.get_components<Drawanle>();
    auto &enemyBullet = enemy.get_components<BulletTag>();
    auto &boss = enemy.get_components<BossTag>();

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i] && (!allyBullet[i] || !allyBullet[i]->isBullet)) { // Exclude ally bullets
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j] && enemyBullet[j] && enemyBullet[j]->isBullet) { // Include only enemy bullets
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        ally.kill_entity(ally.entity_from_index(i));
                        enemy.kill_entity(enemy.entity_from_index(j));
                    }
                }
            }
        }
    }

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i] && allyBullet[i] && allyBullet[i]->isBullet) {
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j] && enemyBullet[j] && enemyBullet[j]->isBullet) {
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        ally.kill_entity(ally.entity_from_index(i));
                        enemy.kill_entity(enemy.entity_from_index(j));
                    }
                }
            }
        }
    }

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i] && allyBullet[i] && allyBullet[i]->isBullet) {
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j] && (!enemyBullet[j] || !enemyBullet[j]->isBullet)) {
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        ally.kill_entity(ally.entity_from_index(i));
                        if (boss[j]->isBoss) {
                            bossHP[1]--;
                        }
                        if (boss[j]->isBoss && bossHP[1] <= 0) {
                            destructionShip(ennemyPosition[j]->x, ennemyPosition[j]->y);
                            enemy.kill_entity(enemy.entity_from_index(j));
                            maxEnnemyKilled++;
                        } else if (!boss[j]->isBoss) {
                            enemy.kill_entity(enemy.entity_from_index(j));
                            maxEnnemyKilled++;
                        }
                        if (maxEnnemyKilled >= activeEnnemy)
                            startNextRound();
                        return;
                    }
                }
            }
        }
    }

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i] && (!allyBullet[i] || !allyBullet[i]->isBullet)) {
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j] && (!enemyBullet[j] || !enemyBullet[j]->isBullet)) {
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        ally.kill_entity(ally.entity_from_index(i));
                        enemy.kill_entity(enemy.entity_from_index(j));
                        maxEnnemyKilled++;
                        if (maxEnnemyKilled >= activeEnnemy)
                            startNextRound();
                        return;
                    }
                }
            }
        }
    }
}