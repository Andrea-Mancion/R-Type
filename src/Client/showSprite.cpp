/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** showSprite
*/

#include "../../includes/Client/functions.hpp"

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

void Window::spawn_entity_foe() 
{
    for (int i = 0; i < currentRound * 3; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);

        addEnemy(enemy, _sfml.getSpriteEnemy(), gen, dis);
    }
    activeEnnemy = currentRound * 3;
}

void Window::spawn_entity_boss()
{
    hasSongStarted = false;
    std::cout << "JE SUIS AU BOSSSSSSSSSS" << std::endl;
    if (!_sfml.getTextBoss().loadFromFile("includes/assets/sprites/r-typesheet20.gif"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteBoss().setTexture(_sfml.getTextBoss());
    _sfml.getSpriteBoss().setTextureRect(sf::IntRect(15, 67, 35, 30));
    _sfml.getSpriteBoss().setScale(sf::Vector2f(3, 3));

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    addBoss(enemy, _sfml.getSpriteBoss(), mt, dist, bossMusicID);
    updateMusic();
    activeEnnemy = 1;
}