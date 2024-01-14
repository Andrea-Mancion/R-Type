/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** event
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Handles the shooting of a bullet from the ally ship's position.
 * 
 * Loads the bullet sprite from a file, sets its texture and properties, and then spawns a bullet entity
 * at the ally ship's position with a specified speed. The function is responsible for visual setup and 
 * creation of a bullet in the game.
 * 
 * @note The function assumes the first entity in the ally registry is the ship from which the bullet is fired.
 *       It requires the bullet sprite to be present in 'includes/assets/sprites'.
 */

void Window::shootBullet()
{
    auto [position] = getComponent<Position>(ally);
    float bulletSpeed = 1.0f;

    if (!_sfml.getTextBullet().loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteBullet().setTexture(_sfml.getTextBullet());
    _sfml.getSpriteBullet().setTextureRect(sf::IntRect(0, 0, 18, 17));
    _sfml.getSpriteBullet().setScale(sf::Vector2f(2, 2));

    _sfml.addBullet(ally, position[0]->x, position[0]->y, bulletSpeed);
}

/**
 * @brief Initiates the shooting of bullets by the boss entity.
 *
 * This function sets up the properties of bullets fired by the boss entity,
 * including the bullet texture, size, and speed. It then adds the bullet to the
 * game's entities, specifically for the boss entity. The shooting behavior is
 * triggered by the boss entity, and the bullets are directed based on the boss's
 * position and speed.
 */

void Window::shootBulletForBoss()
{
    auto [position] = getComponent<Position>(ally);
    float bulletSpeed = 1.0f;

    if (!_sfml.getTextBullet().loadFromFile("includes/assets/sprites/r-typesheet42.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteBullet().setTexture(_sfml.getTextBullet());
    _sfml.getSpriteBullet().setTextureRect(sf::IntRect(0, 0, 18, 17));
    _sfml.getSpriteBullet().setScale(sf::Vector2f(2, 2));

    _sfml.addBulletBoss(ally, position[0]->x, position[0]->y, bulletSpeed);
}

/**
 * @brief Handles user input events and triggers corresponding actions.
 *
 * This function continuously polls for events in the game window and responds
 * to specific key and mouse button presses. It handles events such as closing
 * the window, shooting bullets, toggling visibility, entering editor mode, and
 * modifying game settings in the editor mode.
 */

void Window::eventHandler()
{
    while (_sfml.getWindow().pollEvent(_sfml.getEvent())) {
        if (_sfml.getEvent().type == sf::Event::Closed)
            _sfml.getWindow().close();
        if (_sfml.getEvent().type == sf::Event::KeyPressed && _sfml.getEvent().key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
            if (isStratChanged == false)
                shootBullet();
            else if (isStratChanged == true)
                shootBulletForBoss();
        } else if (_sfml.getEvent().type == sf::Event::KeyPressed && _sfml.getEvent().key.code == sf::Keyboard::X) {
            auto [bossUltime, enemyPosition] = getComponent<BossUltimateTag, Position>(enemy);
            isXPressed = true;
            for (std::size_t i = 0; i < enemyPosition.size(); i++) {
                if (isStratChanged == true && bossHP[1] <= 10) {
                    std::cout << "OK VISIBLE" << std::endl;
                    bossUltime[i]->isVisible = true;
                }
            }
        } else if (_sfml.getEvent().type == sf::Event::KeyPressed && _sfml.getEvent().key.code == sf::Keyboard::O) {
            isEditor = true;
            panelEditor();
        }

        if (isEditor == true && _sfml.getEvent().type == sf::Event::MouseButtonPressed && _sfml.getEvent().mouseButton.button == sf::Mouse::Left) {
            if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteMinus(0))) {
                if (numberPerWave > 0) {
                    auto it = _sfml.getEntityMap().find(1);
                    if (it != _sfml.getEntityMap().end())
                        killEntity(textEditor, it->second);
                    numberPerWave--;
                    _sfml.getText(1).setString(std::to_string(numberPerWave));
                    _sfml.addText(textEditor, _sfml.getText(1).getPosition().x, _sfml.getText(1).getPosition().y, 1);
                } else
                    std::cout << "Can't go below 0" << std::endl;
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpritePlus(0))) {
                auto it = _sfml.getEntityMap().find(1);
                if (it != _sfml.getEntityMap().end())
                     killEntity(textEditor, it->second);
                numberPerWave++;
                _sfml.getText(1).setString(std::to_string(numberPerWave));
                _sfml.addText(textEditor, _sfml.getText(1).getPosition().x, _sfml.getText(1).getPosition().y, 1);
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteMinus(1))) {
                if (numberPerRound > 0) {
                    auto it = _sfml.getEntityMap().find(3);
                    if (it != _sfml.getEntityMap().end())
                        killEntity(textEditor, it->second);
                    numberPerRound--;
                    _sfml.getText(3).setString(std::to_string(numberPerRound));
                    _sfml.addText(textEditor, _sfml.getText(3).getPosition().x, _sfml.getText(3).getPosition().y, 3);
                } else
                    std::cout << "Can't go below 0" << std::endl;
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpritePlus(1))) {
                auto it = _sfml.getEntityMap().find(3);
                if (it != _sfml.getEntityMap().end())
                    killEntity(textEditor, it->second);
                numberPerRound++;
                _sfml.getText(3).setString(std::to_string(numberPerRound));
                _sfml.addText(textEditor, _sfml.getText(3).getPosition().x, _sfml.getText(3).getPosition().y, 3);
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteDifficulty(0))) {
                if (normalDifficulty == true)
                    std::cout << "Normal difficulty already selected" << std::endl;
                else {
                    normalDifficulty = true;
                    hardDifficulty = false;
                    std::cout << "Normal difficulty selected" << std::endl;
                }
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteDifficulty(1))) {
                if (hardDifficulty == true)
                    std::cout << "Hard difficulty already selected" << std::endl;
                else {
                    hardDifficulty = true;
                    normalDifficulty = false;
                    numberPerWave = 5;
                    numberPerRound = 7;
                    std::cout << "Hard difficulty selected" << std::endl;
                }
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteConfirm()))
                isEditor = false;
        }
    }
}