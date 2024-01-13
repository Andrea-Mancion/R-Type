/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** collision
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Retrieves the bounding box of a given sprite.
 *
 * This function calculates and returns the axis-aligned bounding box of a sprite.
 * The bounding box is represented as a `sf::FloatRect`, which includes the position
 * and size of the rectangle that completely encloses the sprite.
 *
 * The bounding box is useful for various purposes such as collision detection,
 * rendering optimizations, and spatial queries. This function utilizes the
 * `getGlobalBounds` method of the SFML `sf::Sprite` class, which calculates the bounding
 * box based on the transformed (scaled, rotated, etc.) sprite.
 *
 * @param sprite A constant reference to the `sf::Sprite` object whose bounding box is needed.
 * @return `sf::FloatRect` representing the sprite's bounding box in global coordinates.
 */

static sf::FloatRect getBoundingBox(const sf::Sprite &sprite)
{
    return sprite.getGlobalBounds();
}

/**
 * @brief Determines if two sprites are colliding.
 *
 * This function checks for a collision between two sprites by determining
 * if their bounding boxes intersect. It uses the `getBoundingBox` function
 * to obtain the axis-aligned bounding boxes of each sprite and then checks
 * for intersection between these rectangles.
 *
 * The function is useful in scenarios such as collision detection in a game,
 * where it is necessary to know if two game entities (represented by sprites)
 * are overlapping or touching each other.
 *
 * @param sprite1 A constant reference to the first `sf::Sprite` object.
 * @param sprite2 A constant reference to the second `sf::Sprite` object.
 * @return `true` if the bounding boxes of the sprites intersect; `false` otherwise.
 */

static bool collisions(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    return getBoundingBox(sprite1).intersects(getBoundingBox(sprite2));
}

/**
 * @brief Checks and handles collisions between ally and enemy entities.
 *
 * This method is responsible for detecting collisions between various ally and enemy entities
 * in a game and handling the consequences of such collisions. It covers different scenarios
 * such as ally vs enemy bullets, ally bullets vs enemy bullets, and direct collisions between
 * ally and enemy entities.
 *
 * The method uses the `getComponent` function to retrieve the positions, drawable components,
 * and bullet tags of allies and enemies. It then iterates through these components, using
 * the `collisions` function to detect intersections. Upon detecting a collision, appropriate
 * actions are taken, which may include killing the colliding entities and triggering specific
 * game events like boss health reduction, ship destruction, music update, and starting the next
 * round of the game.
 *
 * The method handles different types of collisions:
 * - Ally (excluding bullets) vs enemy bullets.
 * - Ally bullets vs enemy bullets.
 * - Ally bullets vs enemies (including boss entities).
 * - Ally (excluding bullets) vs enemies (excluding bullets).
 *
 * The logic also includes specific handling for boss entities, such as decrementing boss health
 * and triggering boss-specific behaviors.
 */

void Window::checkCollision() 
{
    auto [allyPosition, allyDrawable, allyBullet] = getComponent<Position, Drawable, BulletTag>(ally);
    auto [ennemyPosition, ennemyDrawable, enemyBullet, boss, bossUltime] = getComponent<Position, Drawable, BulletTag, BossTag, BossUltimateTag>(enemy);

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
                        if (boss[j]->isBoss && !bossUltime[j]->isBoss) {
                            bossHP[1]--;
                        } else if (!boss[j]->isBoss && bossUltime[j]->isBoss) {
                            bossHP[1]--;
                        }
                        if (boss[j]->isBoss && bossHP[1] <= 0 && !bossUltime[j]->isBoss) {
                            destructionShipBoss(ennemyPosition[j]->x, ennemyPosition[j]->y);
                            killEntity(enemy, j);
                            hasSongStarted = false;
                            bossStarted = false;
                            updateMusic();
                            maxEnnemyKilled++;
                            bossTimer[0]++;
                            canCheckLevel = true;
                        } else if (!boss[j]->isBoss && bossUltime[j]->isBoss && bossHP[1] <=0) {
                            destructionShipBoss(ennemyPosition[j]->x, ennemyPosition[j]->y);
                            killEntity(enemy, j);
                            std::cout << "GG you've won the game" << std::endl;
                            _sfml.getWindow().close();
                        } else if (!boss[j]->isBoss && !bossUltime[j]->isBoss) {
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

bool Window::isMouseClickedOnSprite(sf::RenderWindow &window, sf::Sprite &sprite)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
    sf::FloatRect mouseRect(mouseWorldPos.x, mouseWorldPos.y, 1, 1);

    if (sprite.getGlobalBounds().intersects(mouseRect))
        return true;
    return false;
}