/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** collision
*/

#include "../../includes/Client/functions.hpp"

static sf::FloatRect getBoundingBox(const sf::Sprite &sprite)
{
    return sprite.getGlobalBounds();
}

static bool collisions(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    return getBoundingBox(sprite1).intersects(getBoundingBox(sprite2));
}

void Window::checkCollision() 
{
    auto [allyPosition, allyDrawable, allyBullet] = getComponent<Position, Drawable, BulletTag>(ally);
    auto [ennemyPosition, ennemyDrawable, enemyBullet, boss] = getComponent<Position, Drawable, BulletTag, BossTag>(enemy);

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i] && (!allyBullet[i] || !allyBullet[i]->isBullet)) { // Exclude ally bullets
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j] && enemyBullet[j] && enemyBullet[j]->isBullet) { // Include only enemy bullets
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        killEntity(ally, i);
                        killEntity(enemy, j);
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
                        killEntity(ally, i);
                        killEntity(enemy, j);
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
                        killEntity(ally, i);
                        if (boss[j]->isBoss) {
                            bossHP[1]--;
                        }
                        if (boss[j]->isBoss && bossHP[1] <= 0) {
                            destructionShipBoss(ennemyPosition[j]->x, ennemyPosition[j]->y);
                            killEntity(enemy, j);
                            hasSongStarted = false;
                            bossStarted = false;
                            updateMusic();
                            maxEnnemyKilled++;
                        } else if (!boss[j]->isBoss) {
                            killEntity(enemy, j);
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
                        killEntity(ally, i);
                        killEntity(enemy, j);
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