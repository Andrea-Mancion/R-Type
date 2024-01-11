/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** waveEditor
*/

#include "../../../includes/Client/functions.hpp"

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
    _sfml.getText().setFont(_sfml.getFont());
    _sfml.getText().setString("Wave number");
    _sfml.getText().setCharacterSize(50);
    _sfml.getText().setFillColor(sf::Color::White);
    _sfml.getText().setStyle(sf::Text::Bold);
    _sfml.getText().setPosition(sf::Vector2f(100, 100));
    _sfml.addText(textEditor, _sfml.getText().getPosition().x, _sfml.getText().getPosition().y);
}