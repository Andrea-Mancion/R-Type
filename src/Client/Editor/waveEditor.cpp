/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** waveEditor
*/

#include "../../../includes/Client/functions.hpp"

void Window::loadButtons()
{
    if (!_sfml.getTextMinus().loadFromFile("includes/assets/minus.png") || !_sfml.getTextPlus().loadFromFile("includes/assets/plus.png") || !_sfml.getTextConfirm().loadFromFile("includes/assets/buttons.png"))
        std::cout << "Error" << std::endl;
    _sfml.getSpriteMinus().setTexture(_sfml.getTextMinus());
    _sfml.getSpriteMinus().setTextureRect(sf::IntRect(0, 0, 420, 420));
    _sfml.getSpriteMinus().setScale(sf::Vector2f(0.2, 0.2));
    _sfml.getSpriteMinus().setPosition(sf::Vector2f(500, 100));

    _sfml.getSpritePlus().setTexture(_sfml.getTextPlus());
    _sfml.getSpritePlus().setTextureRect(sf::IntRect(0, 0, 190, 190));
    _sfml.getSpritePlus().setScale(sf::Vector2f(0.4, 0.4));
    _sfml.getSpritePlus().setPosition(sf::Vector2f(800, 100));

    _sfml.getSpriteConfirm().setTexture(_sfml.getTextConfirm());
    _sfml.getSpriteConfirm().setTextureRect(sf::IntRect(140, 17, 92, 25));
    _sfml.getSpriteConfirm().setScale(sf::Vector2f(3, 3));
    _sfml.getSpriteConfirm().setPosition(sf::Vector2f(800, 900));

    _sfml.addButton(buttons, _sfml.getSpriteMinus().getPosition().x, _sfml.getSpriteMinus().getPosition().y, _sfml.getSpriteMinus());
    _sfml.addButton(buttons, _sfml.getSpritePlus().getPosition().x, _sfml.getSpritePlus().getPosition().y, _sfml.getSpritePlus());
    _sfml.addButton(buttons, _sfml.getSpriteConfirm().getPosition().x, _sfml.getSpriteConfirm().getPosition().y, _sfml.getSpriteConfirm());
}

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
    _sfml.getText(1).setString(std::to_string(numberDefault));
    _sfml.getText(1).setPosition(sf::Vector2f(700, 100));

    loadButtons();
    
    _sfml.addText(textEditor, _sfml.getText(0).getPosition().x, _sfml.getText(0).getPosition().y, 0);
    _sfml.addText(textEditor, _sfml.getText(1).getPosition().x, _sfml.getText(1).getPosition().y, 1);
}