/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** waveEditor
*/

#include "../../../includes/Client/functions.hpp"

/**
 * @brief Loads and initializes graphical buttons for the game interface.
 *
 * This function loads button textures from files and sets up sprite properties
 * for various buttons used in the game interface, such as minus, plus, confirm,
 * and difficulty buttons. It also adds these buttons to the provided container.
 */

void Window::loadButtons()
{
    if (!_sfml.getTextMinus().loadFromFile("includes/assets/minus.png") || !_sfml.getTextPlus().loadFromFile("includes/assets/plus.png") || !_sfml.getTextConfirm().loadFromFile("includes/assets/buttons.png") || !_sfml.getTextDifficulty(0).loadFromFile("includes/assets/normal.png") || !_sfml.getTextDifficulty(1).loadFromFile("includes/assets/Hard.png"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteMinus(0).setTexture(_sfml.getTextMinus());
    _sfml.getSpriteMinus(0).setTextureRect(sf::IntRect(0, 0, 420, 420));
    _sfml.getSpriteMinus(0).setScale(sf::Vector2f(0.2, 0.2));
    _sfml.getSpriteMinus(0).setPosition(sf::Vector2f(500, 100));
    _sfml.getSpriteMinus(1).setTexture(_sfml.getTextMinus());
    _sfml.getSpriteMinus(1).setTextureRect(sf::IntRect(0, 0, 420, 420));
    _sfml.getSpriteMinus(1).setScale(sf::Vector2f(0.2, 0.2));
    _sfml.getSpriteMinus(1).setPosition(sf::Vector2f(500, 200));

    _sfml.getSpritePlus(0).setTexture(_sfml.getTextPlus());
    _sfml.getSpritePlus(0).setTextureRect(sf::IntRect(0, 0, 190, 190));
    _sfml.getSpritePlus(0).setScale(sf::Vector2f(0.4, 0.4));
    _sfml.getSpritePlus(0).setPosition(sf::Vector2f(800, 100));
    _sfml.getSpritePlus(1).setTexture(_sfml.getTextPlus());
    _sfml.getSpritePlus(1).setTextureRect(sf::IntRect(0, 0, 190, 190));
    _sfml.getSpritePlus(1).setScale(sf::Vector2f(0.4, 0.4));
    _sfml.getSpritePlus(1).setPosition(sf::Vector2f(800, 200));

    _sfml.getSpriteConfirm().setTexture(_sfml.getTextConfirm());
    _sfml.getSpriteConfirm().setTextureRect(sf::IntRect(140, 17, 92, 25));
    _sfml.getSpriteConfirm().setScale(sf::Vector2f(3, 3));
    _sfml.getSpriteConfirm().setPosition(sf::Vector2f(800, 900));

    _sfml.getSpriteDifficulty(0).setTexture(_sfml.getTextDifficulty(0));
    _sfml.getSpriteDifficulty(0).setTextureRect(sf::IntRect(0, 0, 500, 300));
    _sfml.getSpriteDifficulty(0).setScale(sf::Vector2f(1, 1));
    _sfml.getSpriteDifficulty(0).setPosition(sf::Vector2f(1400, 350));

    _sfml.getSpriteDifficulty(1).setTexture(_sfml.getTextDifficulty(1));
    _sfml.getSpriteDifficulty(1).setTextureRect(sf::IntRect(0, 0, 300, 170));
    _sfml.getSpriteDifficulty(1).setScale(sf::Vector2f(1, 1));
    _sfml.getSpriteDifficulty(1).setPosition(sf::Vector2f(1400, 600));

    _sfml.addButton(buttons, _sfml.getSpriteMinus(0).getPosition().x, _sfml.getSpriteMinus(0).getPosition().y, _sfml.getSpriteMinus(0));
    _sfml.addButton(buttons, _sfml.getSpritePlus(0).getPosition().x, _sfml.getSpritePlus(0).getPosition().y, _sfml.getSpritePlus(0));
    _sfml.addButton(buttons, _sfml.getSpriteMinus(1).getPosition().x, _sfml.getSpriteMinus(1).getPosition().y, _sfml.getSpriteMinus(1));
    _sfml.addButton(buttons, _sfml.getSpritePlus(1).getPosition().x, _sfml.getSpritePlus(1).getPosition().y, _sfml.getSpritePlus(1));
    _sfml.addButton(buttons, _sfml.getSpriteConfirm().getPosition().x, _sfml.getSpriteConfirm().getPosition().y, _sfml.getSpriteConfirm());
    _sfml.addButton(buttons, _sfml.getSpriteDifficulty(0).getPosition().x, _sfml.getSpriteDifficulty(0).getPosition().y, _sfml.getSpriteDifficulty(0));
    _sfml.addButton(buttons, _sfml.getSpriteDifficulty(1).getPosition().x, _sfml.getSpriteDifficulty(1).getPosition().y, _sfml.getSpriteDifficulty(1));
}

/**
 * @brief Sets up the editor panel for game configuration.
 *
 * This function initializes the graphical elements for the editor panel,
 * including background images, text elements, and buttons. It also populates
 * text elements with information about wave and round numbers. The editor panel
 * provides a visual interface for configuring game settings.
 */

void Window::panelEditor()
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

    if (!_sfml.getFont().loadFromFile("includes/assets/ARIAL.TTF"))
        std::cout << "Error" << std::endl;
    for (std::size_t i = 0; i < 4; i++) {
        _sfml.getText(i).setFont(_sfml.getFont());
        _sfml.getText(i).setCharacterSize(50);
        _sfml.getText(i).setFillColor(sf::Color::White);
        _sfml.getText(i).setStyle(sf::Text::Bold);
    }
    _sfml.getText(0).setString("Wave number: ");
    _sfml.getText(0).setPosition(sf::Vector2f(100, 100));
    _sfml.getText(1).setString(std::to_string(numberPerWave));
    _sfml.getText(1).setPosition(sf::Vector2f(700, 100));
    _sfml.getText(2).setString("Round number: ");
    _sfml.getText(2).setPosition(sf::Vector2f(100, 200));
    _sfml.getText(3).setString(std::to_string(numberPerRound));
    _sfml.getText(3).setPosition(sf::Vector2f(700, 200));


    loadButtons();
    
    _sfml.addText(textEditor, _sfml.getText(0).getPosition().x, _sfml.getText(0).getPosition().y, 0);
    _sfml.addText(textEditor, _sfml.getText(1).getPosition().x, _sfml.getText(1).getPosition().y, 1);
    _sfml.addText(textEditor, _sfml.getText(2).getPosition().x, _sfml.getText(2).getPosition().y, 2);
    _sfml.addText(textEditor, _sfml.getText(3).getPosition().x, _sfml.getText(3).getPosition().y, 3);
}