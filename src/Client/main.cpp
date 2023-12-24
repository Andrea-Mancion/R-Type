#include <iostream>
#include "../../includes/Client/functions.hpp"

Window::Window()
{
    _sfml.getWindow().create(sf::VideoMode(1920, 1080), "R-Type");
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

    addSystemAlly(ally, hasSongStarted, bossStarted, _sfml.getWindow(), musicManager);
    addSystemEnemy(enemy, hasSongStarted, bossStarted, _sfml.getWindow(), musicManager);

    addAllyShip(ally, allyMusicID, _sfml.getSpriteShip());

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);
    
    addEnemy(enemy, _sfml.getSpriteEnemy(), mt, dist);
    
    while (_sfml.getWindow().isOpen()) {
        float time = _sfml.getClock().restart().asSeconds();
        eventHandler();
        if (!isAnyAllyShipLeft()) {
            std::cout << "Oh no you're dead Game Over" << std::endl;
            _sfml.getWindow().close();
        }
        _sfml.getSprite(0).move(-0.1, 0);
        _sfml.getSprite(1).move(-0.1, 0);
        _sfml.getSprite(2).move(-0.1, 0);
        if (_sfml.getSprite(0).getPosition().x <= -1920)
            _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
        if (_sfml.getSprite(1).getPosition().x <= -1920)
            _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
        if (_sfml.getSprite(2).getPosition().x <= -1920)
            _sfml.getSprite(2).setPosition(sf::Vector2f(3840, 0));

        _sfml.getWindow().clear();
        _sfml.getWindow().draw(_sfml.getSprite(0));
        _sfml.getWindow().draw(_sfml.getSprite(1));
        _sfml.getWindow().draw(_sfml.getSprite(2));
        updateMusic();
        ally.run_systems();
        enemy.run_systems();
        enemy_shooting(time);
        checkCollision();
        _sfml.getWindow().display();
    }
}

int main(int ac, char** av)
{
    try {
        if (ac == 2 && strcmp(av[1], "-h") == 0)
            printHelp();
        else {
            Window window;

            window.startProject();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}