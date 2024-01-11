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
 * @brief Handles all the events occurring in the game window.
 * 
 * Processes events from the SFML window, such as window closure and key presses. 
 * If the 'Close' event is triggered, it closes the window. It also listens for the 
 * 'Space' key press to trigger the shooting of a bullet.
 * 
 * @note This function is a central part of the game's input handling, responding to user interactions.
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
            std::cout << "Implemente the Waves editor" << std::endl;
            isEditor = true;
            panelEditor();
        }

        if (isEditor == true && _sfml.getEvent().type == sf::Event::MouseButtonPressed && _sfml.getEvent().mouseButton.button == sf::Mouse::Left) {
            if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteMinus())) {
                numberDefault--;
                _sfml.getText(1).setString(std::to_string(numberDefault));
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpritePlus())) {
                numberDefault++;
                _sfml.getText(1).setString(std::to_string(numberDefault));
            } else if (isMouseClickedOnSprite(_sfml.getWindow(), _sfml.getSpriteConfirm()))
                isEditor = false;
        }
    }
}