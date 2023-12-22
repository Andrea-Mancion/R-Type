/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** showSprite
*/

#include "../../includes/Client/window.hpp"

void Window::loadSprites() 
{
    if (!background.loadFromFile("includes/assets/Space.png"))
        std::cout << "Error" << std::endl;
    sprite[0].setTexture(background);
    sprite[0].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[0].setPosition(sf::Vector2f(0, 0));
    sprite[1].setTexture(background);
    sprite[1].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[1].setPosition(sf::Vector2f(1920, 0));
    sprite[2].setTexture(background);
    sprite[2].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[2].setPosition(sf::Vector2f(-1920, 0));

    if (!textSprite.loadFromFile("includes/assets/sprites/r-typesheet27.gif"))
        std::cout << "Error" << std::endl;
    spriteShip.setTexture(textSprite);
    spriteShip.setTextureRect(sf::IntRect(33, 0, 33, 17));
    spriteShip.setScale(sf::Vector2f(3, 3));

    if (!textEnemy.loadFromFile("includes/assets/sprites/r-typesheet14.gif"))
        std::cout << "Error" << std::endl;
    spriteEnemy.setTexture(textEnemy);
    spriteEnemy.setTextureRect(sf::IntRect(0, 0, 50, 50));
    spriteEnemy.setScale(sf::Vector2f(3, 3));
}

void Window::spawn_entity_foe() 
{
    for (int i = 0; i < currentRound * 3; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);

        addEnemy(enemy, spriteEnemy, gen, dis);
    }
    activeEnnemy = currentRound * 3;
}

void Window::spawn_entity_boss()
{
    hasSongStarted = false;
    std::cout << "JE SUIS AU BOSSSSSSSSSS" << std::endl;
    if (!textBoss.loadFromFile("includes/assets/sprites/r-typesheet20.gif"))
        std::cout << "Error" << std::endl;
    spriteBoss.setTexture(textBoss);
    spriteBoss.setTextureRect(sf::IntRect(15, 67, 35, 30));
    spriteBoss.setScale(sf::Vector2f(3, 3));

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    addBoss(enemy, spriteBoss, mt, dist, bossMusicID);
    updateMusic();
    activeEnnemy = 1;
}