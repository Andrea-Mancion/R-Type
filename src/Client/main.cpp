#include <iostream>
#include "../../includes/Client/functions.hpp"

Window::Window()
{
    _sfml._window.create(sf::VideoMode(1920, 1080), "R-Type");
    redirectCoutToFile("log.txt");
}

Window::~Window()
{
    resetCout(redirectCoutToFile("log.txt"));
}

bool Window::isAnyAllyShipLeft()
{
    auto [position, bullet] = getComponent<Position, BulletTag>(ally);
    int count = 0;

    for (std::size_t i = 0; i < position.size(); i++) {
        if (position[i] && !bullet[i]->isBullet)
            count++;
    }

    return count > 0;
}

void Window::startProject()
{
    allyMusicID = musicManager.loadMusic("includes/assets/SpaceMusic.ogg");
    bossMusicID = musicManager.loadMusic("includes/assets/BossTheme.ogg");

    loadSprites();
    registerComponentAlly(ally);
    registerComponentEnemy(enemy);

    addSystemAlly(ally, hasSongStarted, bossStarted, _sfml._window, musicManager);
    addSystemEnemy(enemy, hasSongStarted, bossStarted, _sfml._window, musicManager);

    addAllyShip(ally, allyMusicID, _sfml.spriteShip);

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);
    
    addEnemy(enemy, _sfml.spriteEnemy, mt, dist);
    
    while (_sfml._window.isOpen()) {
        float time = _sfml.clock.restart().asSeconds();
        eventHandler();
        if (!isAnyAllyShipLeft()) {
            std::cout << "Oh no you're dead Game Over" << std::endl;
            _sfml._window.close();
        }
        _sfml.sprite[0].move(-0.1, 0);
        _sfml.sprite[1].move(-0.1, 0);
        _sfml.sprite[2].move(-0.1, 0);
        if (_sfml.sprite[0].getPosition().x <= -1920)
            _sfml.sprite[0].setPosition(sf::Vector2f(0, 0));
        if (_sfml.sprite[1].getPosition().x <= -1920)
            _sfml.sprite[1].setPosition(sf::Vector2f(1920, 0));
        if (_sfml.sprite[2].getPosition().x <= -1920)
            _sfml.sprite[2].setPosition(sf::Vector2f(3840, 0));

        _sfml._window.clear();
        _sfml._window.draw(_sfml.sprite[0]);
        _sfml._window.draw(_sfml.sprite[1]);
        _sfml._window.draw(_sfml.sprite[2]);
        updateMusic();
        ally.run_systems();
        enemy.run_systems();
        enemy_shooting(time);
        checkCollision();
        _sfml._window.display();
    }
}

int main(int ac, char** av)
{
    Window window;

    try {
        window.startProject();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}