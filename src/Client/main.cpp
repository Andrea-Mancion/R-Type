#include <iostream>
#include "../../includes/Client/window.hpp"

Window::Window()
{
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    redirectCoutToFile("log.txt");
}

Window::~Window()
{
    resetCout(redirectCoutToFile("log.txt"));
}

bool Window::isAnyAllyShipLeft() const
{
    auto &position = ally.get_components<Position>();
    auto &bullet = ally.get_components<BulletTag>();
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

    addSystemAlly(ally, hasSongStarted, bossStarted, _window, musicManager);
    addSystemEnemy(enemy, hasSongStarted, bossStarted, _window, musicManager);

    // ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     logging_system(r, position, velocity);
    // });

    // ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     position_system(r);
    // });

    // ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     control_system(r);
    // });

    // ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     if (!this->hasSongStarted && !this->bossStarted) {
    //         song_system(r, musicManager);
    //         this->hasSongStarted = true;
    //     }
    // });

    // ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     draw_system(r, _window);
    // });

    // enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     logging_system(r, position, velocity);
    // });

    // enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     position_system(r);
    // });

    // enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     if (!this->hasSongStarted && this->bossStarted) {
    //         song_system(r, musicManager);
    //         this->hasSongStarted = true;
    //     }
    // });

    // enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
    //     draw_system(r, _window);
    // });

    auto entityAlly = ally.spawn_entity();

    ally.add_component(entityAlly, Position{500, 500});
    ally.add_component(entityAlly, Velocity{0, 0});
    ally.add_component(entityAlly, Controllable{});
    ally.add_component(entityAlly, BulletTag{false});
    ally.add_component(entityAlly, Timer{0.0f});
    ally.add_component(entityAlly, EnemyTag{false});
    ally.add_component(entityAlly, BossTag{false});
    ally.add_component(entityAlly, ExplosionTag{false});
    ally.add_component(entityAlly, Song{allyMusicID, false, true, false});
    ally.add_component(entityAlly, Drawable{spriteShip});

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);
    
    auto entityEnemy = enemy.spawn_entity();

    enemy.add_component(entityEnemy, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(entityEnemy, Velocity{-0.4, 0});
    enemy.add_component(entityEnemy, BulletTag{false});
    enemy.add_component(entityEnemy, Timer{0.0f});
    enemy.add_component(entityEnemy, EnemyTag{true});
    enemy.add_component(entityEnemy, BossTag{false});
    enemy.add_component(entityEnemy, ExplosionTag{false});
    enemy.add_component(entityEnemy, Drawable{spriteEnemy});

    while (_window.isOpen()) {
        float time = clock.restart().asSeconds();
        eventHandler();
        if (!isAnyAllyShipLeft()) {
            std::cout << "Oh no you're dead Game Over" << std::endl;
            _window.close();
        }
        sprite[0].move(-0.1, 0);
        sprite[1].move(-0.1, 0);
        sprite[2].move(-0.1, 0);
        if (sprite[0].getPosition().x <= -1920)
            sprite[0].setPosition(sf::Vector2f(0, 0));
        if (sprite[1].getPosition().x <= -1920)
            sprite[1].setPosition(sf::Vector2f(1920, 0));
        if (sprite[2].getPosition().x <= -1920)
            sprite[2].setPosition(sf::Vector2f(3840, 0));

        _window.clear();
        _window.draw(sprite[0]);
        _window.draw(sprite[1]);
        _window.draw(sprite[2]);
        updateMusic();
        ally.run_systems();
        enemy.run_systems();
        enemy_shooting(time);
        checkCollision();
        _window.display();
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