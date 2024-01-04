/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** addComponent
*/

#include "../../../includes/Client/functions.hpp"
#include <random>

/**
 * @brief Adds an ally ship entity to the game with various components.
 * 
 * Spawns a new ally entity and adds several components to it, including position, velocity, 
 * control, and various tags. Sets the initial position and velocity, and also assigns the 
 * music ID for the ally ship. The ally ship is also assigned a drawable component to handle its rendering.
 * 
 * @param ally The registry to which the ally ship is added.
 * @param allyMusicID The music ID associated with the ally ship.
 * 
 * @note This function is part of the setup for player-controlled entities in the game.
 */

void SFML::addAllyShip(Registry &ally, int allyMusicID)
{
    auto entityAlly = ally.spawn_entity();

    ally.add_component(entityAlly, Position{500, 500});
    ally.add_component(entityAlly, Velocity{0, 0});
    ally.add_component(entityAlly, Controllable{});
    ally.add_component(entityAlly, BulletTag{false});
    ally.add_component(entityAlly, Timer{0.0f});
    ally.add_component(entityAlly, EnemyTag{false});
    ally.add_component(entityAlly, BossTag{false});
    ally.add_component(entityAlly, BossUltimateTag{false});
    ally.add_component(entityAlly, ExplosionTag{false});
    ally.add_component(entityAlly, Song{allyMusicID, false, true, false});
    ally.add_component(entityAlly, Drawable{spriteShip});
}

/**
 * @brief Adds an enemy entity to the game with various components.
 * 
 * Spawns a new enemy entity and adds components such as position, velocity, bullet tag, 
 * and timer for shooting. The position is initialized based on a random distribution to 
 * vary the spawn locations of enemies. The enemy is also assigned a drawable component.
 * 
 * @param enemy The registry to which the enemy is added.
 * @param mt The Mersenne Twister random number generator used for position and timer.
 * @param dist The distribution to determine the enemy's initial Y-position.
 * 
 * @note This function is used to populate the game with enemy entities, each having randomized behavior.
 */

void SFML::addEnemy(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist)
{
    auto entityEnemy = enemy.spawn_entity();
    std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

    enemy.add_component(entityEnemy, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(entityEnemy, Velocity{-0.4, 0});
    enemy.add_component(entityEnemy, BulletTag{false});
    enemy.add_component(entityEnemy, Timer{shootDis(mt)});
    enemy.add_component(entityEnemy, EnemyTag{true});
    enemy.add_component(entityEnemy, BossTag{false});
    enemy.add_component(entityEnemy, BossUltimateTag{false});
    enemy.add_component(entityEnemy, ExplosionTag{false});
    enemy.add_component(entityEnemy, Drawable{spriteEnemy});
}

/**
 * @brief Adds a boss entity to the game with various components.
 * 
 * Spawns a new boss entity and adds components such as position, velocity, bullet tag,
 * and timer for shooting. The position is determined by a random distribution. The boss
 * entity is also set up with music and drawable components specific to boss entities.
 * 
 * @param enemy The registry to which the boss entity is added.
 * @param mt The Mersenne Twister random number generator used for random positioning.
 * @param dist The distribution to determine the boss's initial Y-position.
 * @param bossMusicID The music ID associated with the boss entity.
 * 
 * @note This function is crucial for introducing boss-level challenges in the game.
 */

void SFML::addBoss(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID)
{
    std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

    auto ennemyBoss = enemy.spawn_entity();
    enemy.add_component(ennemyBoss, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(ennemyBoss, Velocity{-0.4, 0});
    enemy.add_component(ennemyBoss, BulletTag{false});
    enemy.add_component(ennemyBoss, Timer{shootDis(mt)});
    enemy.add_component(ennemyBoss, EnemyTag{true});
    enemy.add_component(ennemyBoss, BossTag{true});
    enemy.add_component(ennemyBoss, BossUltimateTag{false});
    enemy.add_component(ennemyBoss, ExplosionTag{false});
    enemy.add_component(ennemyBoss, Song{bossMusicID, true, true, false});
    enemy.add_component(ennemyBoss, Drawable{spriteBoss});
}

void SFML::addBossUltimate(Registry &enemy,  std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID)
{
    std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

    auto ennemyBoss = enemy.spawn_entity();
    enemy.add_component(ennemyBoss, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(ennemyBoss, Velocity{-0.4, 0});
    enemy.add_component(ennemyBoss, BulletTag{false});
    enemy.add_component(ennemyBoss, Timer{shootDis(mt)});
    enemy.add_component(ennemyBoss, EnemyTag{true});
    enemy.add_component(ennemyBoss, BossTag{false});
    enemy.add_component(ennemyBoss, BossUltimateTag{true});
    enemy.add_component(ennemyBoss, ExplosionTag{false});
    enemy.add_component(ennemyBoss, Song{bossMusicID, true, true, false});
    enemy.add_component(ennemyBoss, Drawable{spriteBoss});
}

/**
 * @brief Adds a bullet entity to the game with specified attributes.
 * 
 * Spawns a new bullet entity at the given coordinates and assigns it a velocity. The bullet is tagged 
 * and given a drawable component, which varies depending on whether the bullet is allied or enemy-fired.
 * 
 * @param reg The registry to which the bullet entity is added.
 * @param x The initial x-coordinate of the bullet.
 * @param y The initial y-coordinate of the bullet.
 * @param bulletSpeed The speed of the bullet along the x-axis.
 * 
 * @note This function is used for creating bullets that entities fire during the game.
 */

void SFML::addBullet(Registry &reg, float x, float y, float bulletSpeed)
{
    auto [enemy] = getComponent<EnemyTag>(reg);
    auto bulletEntity = reg.spawn_entity();

    reg.add_component(bulletEntity, Position{x, y});
    reg.add_component(bulletEntity, Velocity{bulletSpeed, 0});
    reg.add_component(bulletEntity, BulletTag{true});
    if (enemy[0]->isEnemy)
        reg.add_component(bulletEntity, Drawable{spriteEnemyBullet});
    else
        reg.add_component(bulletEntity, Drawable{spriteBullet});
}

/**
 * @brief Adds an explosion entity to the game at a specified location.
 * 
 * Spawns a new explosion entity and sets its position based on the given coordinates. The explosion
 * is stationary (zero velocity) and is tagged as an explosion. It is also assigned a drawable component
 * for its visual representation.
 * 
 * @param reg The registry to which the explosion entity is added.
 * @param x The x-coordinate where the explosion will occur.
 * @param y The y-coordinate where the explosion will occur.
 * 
 * @note This function is typically called when an entity, like a ship or bullet, is destroyed.
 */

void SFML::addExplosion(Registry &reg,  float x, float y)
{
    auto explosion = reg.spawn_entity();
    reg.add_component(explosion, Position{x, y});
    reg.add_component(explosion, Velocity{0, 0});
    reg.add_component(explosion, BulletTag{false});
    reg.add_component(explosion, Timer{0.0f});
    reg.add_component(explosion, EnemyTag{false});
    reg.add_component(explosion, BossTag{false});
    reg.add_component(explosion, BossUltimateTag{false});
    reg.add_component(explosion, ExplosionTag{true});
    reg.add_component(explosion, Drawable{spriteExplosion});
}