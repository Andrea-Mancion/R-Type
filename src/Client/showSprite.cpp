/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** showSprite
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Loads and configures the sprites used in the game.
 * 
 * This function is responsible for loading the background, player ship, and enemy ship textures from files.
 * It sets up the textures for each sprite, configures their texture rectangles, positions, and scales. 
 * If any texture fails to load, it outputs an error message.
 * 
 * @note The function assumes the existence of specific assets in the 'includes/assets' directory.
 *       It is vital for the visual setup of the game, ensuring that all sprites are correctly displayed.
 */

void Window::loadSprites() 
{
    if (!_sfml.getBackground().loadFromFile("includes/assets/Space.png"))
        std::cout << "Error" << std::endl;
    _sfml.getSprite(0).setTexture(_sfml.getBackground());
    _sfml.getSprite(0).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
    _sfml.getSprite(1).setTexture(_sfml.getBackground());
    _sfml.getSprite(1).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
    _sfml.getSprite(2).setTexture(_sfml.getBackground());
    _sfml.getSprite(2).setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    _sfml.getSprite(2).setPosition(sf::Vector2f(-1920, 0));

    if (!_sfml.getTextSprite().loadFromFile("includes/assets/sprites/r-typesheet27.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteShip().setTexture(_sfml.getTextSprite());
    _sfml.getSpriteShip().setTextureRect(sf::IntRect(33, 0, 33, 17));
    _sfml.getSpriteShip().setScale(sf::Vector2f(3, 3));

    if (!_sfml.getTextEnemy().loadFromFile("includes/assets/sprites/r-typesheet14.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteEnemy().setTexture(_sfml.getTextEnemy());
    _sfml.getSpriteEnemy().setTextureRect(sf::IntRect(0, 0, 50, 50));
    _sfml.getSpriteEnemy().setScale(sf::Vector2f(3, 3));
}

/**
 * @brief Spawns enemy entities based on the current game round.
 * 
 * Generates a number of enemy entities proportional to the current round (three times the round number).
 * Each enemy's position is randomly determined within specified bounds. The function updates the count
 * of active enemies after spawning them.
 * 
 * @note This function is integral to the game's progression, increasing the difficulty in each round.
 *       It utilizes C++'s random number generation facilities to position enemies.
 */

void Window::spawn_entity_foe() 
{
    for (int i = 0; i < currentRound * numberPerWave; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);

        _sfml.addEnemy(enemy, gen, dis);
    }
    activeEnnemy = currentRound * numberPerWave;
}

/**
 * @brief Spawns a specified number of foe entities based on the current round.
 *
 * This function generates and adds a specified number of foe entities to the game registry
 * based on the product of the current round and the provided 'number'. It uses random positions
 * within a specified range to determine the initial positions of the foe entities.
 *
 * @param number The factor that determines the number of foe entities to spawn.
 */

void Window::spawn_entity_foe(int number) 
{
    for (int i = 0; i < currentRound * number; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);

        _sfml.addEnemy(enemy, gen, dis);
    }
    activeEnnemy = currentRound * number + 1;
}

/**
 * @brief Spawns the boss entity and prepares the game for the boss round.
 * 
 * Resets the music start flag and announces the boss round. Loads the boss sprite from a file, 
 * sets up its texture, texture rectangle, and scale. It then spawns the boss entity with a random
 * position within specified bounds and updates the music for the boss round. The active enemy count
 * is set to one, indicating the presence of the boss.
 * 
 * @note This function is called to initiate a boss round, marking a significant event in the game's progression.
 *       It also handles the visual and audio setup specific to the boss entity.
 */

void Window::spawn_entity_boss()
{
    hasSongStarted = false;
    std::cout << "JE SUIS AU BOSSSSSSSSSS" << std::endl;
    if (bossTimer[1] == 0) {
        if (!_sfml.getTextBoss().loadFromFile("includes/assets/sprites/r-typesheet20.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteBoss().setTexture(_sfml.getTextBoss());
        _sfml.getSpriteBoss().setTextureRect(sf::IntRect(15, 67, 35, 30));
        _sfml.getSpriteBoss().setScale(sf::Vector2f(3, 3));
    } else if (bossTimer[1] == 1) {
        if (!_sfml.getTextBoss().loadFromFile("includes/assets/sprites/r-typesheet17.gif"))
            std::cout << "Error" << std::endl;
        _sfml.getSpriteBoss().setTexture(_sfml.getTextBoss());
        _sfml.getSpriteBoss().setTextureRect(sf::IntRect(0, 0, 65, 130));
        _sfml.getSpriteBoss().setScale(sf::Vector2f(3, 3));
    }

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    _sfml.addBoss(enemy, mt, dist, bossMusicID);
    updateMusic();
    activeEnnemy = 1;
}

/**
 * @brief Spawns the ultimate boss entity in the game.
 *
 * This function is responsible for spawning the ultimate boss entity, initializing its
 * appearance and properties. It also ensures that the boss music starts playing and updates
 * the status of active enemies.
 *
 * The ultimate boss entity is represented by the sprite "r-typesheet33.gif" and has specific
 * dimensions and scaling.
 */

void Window::spawn_entity_boss_ultimate()
{
    hasSongStarted = false;
    if (!_sfml.getTextBoss().loadFromFile("includes/assets/sprites/r-typesheet33.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteBoss().setTexture(_sfml.getTextBoss());
    _sfml.getSpriteBoss().setTextureRect(sf::IntRect(0, 0, 255, 140));
    _sfml.getSpriteBoss().setScale(sf::Vector2f(2, 2));

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    _sfml.addBossUltimate(enemy, mt, dist, bossMusicID, true);
    updateMusic();
    activeEnnemy = 1;
}