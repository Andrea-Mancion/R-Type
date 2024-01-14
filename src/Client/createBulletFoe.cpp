/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** createBulletFoe
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Creates and shoots an enemy bullet in the game.
 *
 * This method is responsible for generating a new enemy bullet and initializing its properties.
 * It sets the texture, size, scale, and initial position of the bullet. The bullet is then added
 * to the game world with a specified speed in a downward direction (indicated by the negative speed value).
 *
 * The method begins by loading the bullet's texture from a specified file. If the texture loading fails,
 * it outputs an error message. Once the texture is set, the bullet's appearance is configured by setting
 * the texture rectangle, scale, and initial position based on the provided coordinates (x, y).
 *
 * Finally, the bullet is added to the game with a call to `_sfml.addBullet`, which handles the integration
 * of the bullet into the game's mechanics, such as movement and collision detection.
 *
 * @param i An integer index representing the bullet's unique identifier or related enemy entity.
 * @param x The x-coordinate for the initial position of the bullet.
 * @param y The y-coordinate for the initial position of the bullet.
 */

void Window::shootEnemyBullet(int i, float x, float y) 
{
    (void)i;
    float bulletSpeed = -1.0f;

    if (bossTimer[1] == 0) {
        if (!_sfml.getTextEnemyBullet().loadFromFile("includes/assets/sprites/r-typesheet14.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteEnemyBullet().setTexture(_sfml.getTextEnemyBullet());
        _sfml.getSpriteEnemyBullet().setTextureRect(sf::IntRect(0, 135, 10, 17));
        _sfml.getSpriteEnemyBullet().setScale(sf::Vector2f(2, 2));
        _sfml.getSpriteEnemyBullet().setPosition(x, y);
    } else if (bossTimer[1] == 1) {
        if (!_sfml.getTextEnemyBullet().loadFromFile("includes/assets/sprites/r-typesheet9.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteEnemyBullet().setTexture(_sfml.getTextEnemyBullet());
        _sfml.getSpriteEnemyBullet().setTextureRect(sf::IntRect(0, 60, 10, 17));
        _sfml.getSpriteEnemyBullet().setScale(sf::Vector2f(2, 2));
        _sfml.getSpriteEnemyBullet().setPosition(x, y);
    }
    _sfml.addBullet(enemy, x, y, bulletSpeed);
}

/**
 * @brief Shoots a bullet for the Boss Ultime entity.
 *
 * This function is responsible for shooting a bullet for the Boss Ultime entity at the specified
 * position (x, y). The bullet is fired in the upward direction with a predefined speed. It loads the
 * appropriate texture for the Boss Ultime bullet, sets its properties, and adds it to the game registry.
 *
 * @param i Unused parameter (index), included for compatibility.
 * @param x The x-coordinate of the position where the bullet is fired.
 * @param y The y-coordinate of the position where the bullet is fired.
 */

void Window::shootBossUltimeBullet(int i, float x, float y)
{
    (void)i;
    float bulletSpeed = -1.0f;

    if (!_sfml.getTextEnemyBullet().loadFromFile("includes/assets/sprites/r-typesheet9.gif"))
            std::cout << "Error" << std::endl;
    _sfml.getSpriteEnemyBullet().setTexture(_sfml.getTextEnemyBullet());
    _sfml.getSpriteEnemyBullet().setTextureRect(sf::IntRect(0, 60, 10, 17));
    _sfml.getSpriteEnemyBullet().setScale(sf::Vector2f(2, 2));
    _sfml.getSpriteEnemyBullet().setPosition(x, y);

    _sfml.addBulletBoss(enemy, x, y, bulletSpeed);
}

/**
 * @brief Handles the shooting mechanism for enemy entities.
 *
 * This method is responsible for managing the shooting actions of enemy entities in the game.
 * It iterates through the enemies, checking and updating their shooting timers, and triggers
 * the shooting of bullets when appropriate.
 *
 * The method retrieves the position and timer components of each enemy. For each enemy,
 * it increments the timer by the elapsed time (`dt`). When the timer exceeds a specified
 * shooting interval, the enemy shoots a bullet. The shooting position is determined by
 * the enemy's current position. After shooting, the timer is reset, and the shooting interval
 * is randomized for varied shooting patterns.
 *
 * The method uses a `std::uniform_real_distribution` to randomize the shooting interval,
 * making the enemy shooting behavior less predictable and more dynamic.
 *
 * @param dt Delta time - the time elapsed since the last game update, used to increment timers.
 */

void Window::enemy_shooting(float dt)
{
    auto [position, timers, bossUltime] = getComponent<Position, Timer, BossUltimateTag>(enemy);

    for (size_t i = 0; i < position.size() && i < timers.size(); i++) {
        if (position[i] && timers[i]) {
            auto &timer = timers[0];
            timer->elapsedTime += dt;

            std::cout << "STRAT CHA?NGED: " << isStratChanged << std::endl;
            if (timer->elapsedTime >= timer->shootInterval && bossUltime[i]->isBoss == true && isStratChanged == true) {
                shootBossUltimeBullet(i, position[i]->x, position[i]->y);
                timer->elapsedTime = 0.0f;
                std::uniform_real_distribution<float> shootDis(0.0f, 3.0f);
                timer->shootInterval = shootDis(rd);
            } else if (timer->elapsedTime >= timer->shootInterval && isStratChanged == false) {
                shootEnemyBullet(i, position[i]->x, position[i]->y);
                timer->elapsedTime = 0.0f;
                std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);
                timer->shootInterval = shootDis(rd);
            }
        }
    } 
}