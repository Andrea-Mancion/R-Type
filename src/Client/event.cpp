/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** event
*/

#include "../../includes/Client/window.hpp"

void Window::shootBullet()
{
    auto &position = ally.get_components<Position>();
    auto &drawable = ally.get_components<Drawanle>();
    float bulletSpeed = 1.0f;

    if (!textBullet.loadFromFile("includes/assets/sprites/r-typesheet3.gif"))
        std::cout << "Error" << std::endl;
    spriteBullet.setTexture(textBullet);
    spriteBullet.setTextureRect(sf::IntRect(0, 0, 18, 17));
    spriteBullet.setScale(sf::Vector2f(2, 2));
    spriteBullet.setPosition(position[0]->x, position[0]->y);

    std::cout << "shoot bullet from " << spriteBullet.getPosition().x << ", " << spriteBullet.getPosition().y << std::endl;

    auto bulletEntity = ally.spawn_entity();
    ally.add_component(bulletEntity, Position{position[0]->x, position[0]->y});
    ally.add_component(bulletEntity, Velocity{bulletSpeed, 0});
    ally.add_component(bulletEntity, BulletTag{true});
    ally.add_component(bulletEntity, Drawanle{spriteBullet});

    std::cout << "Yeah it's created with the ID " << bulletEntity << std::endl;
}

void Window::eventHandler()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Space) {
            std::cout << "Space pressed" << std::endl;
            shootBullet();
        }
    }
}

void Window::spawn_entity() 
{
    for (int i = 0; i < currentRound * 5; ++i) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<> dis(-16, 959);
        std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

        auto entityEnnemy = enemy.spawn_entity();
        enemy.add_component(entityEnnemy, Position{1900, static_cast<float>(dis(gen))});
        enemy.add_component(entityEnnemy, Velocity{-0.4, 0});
        enemy.add_component(entityEnnemy, BulletTag{false});
        enemy.add_component(entityEnnemy, Timer{shootDis(gen)});
        enemy.add_component(entityEnnemy, EnemyTag{true});
        enemy.add_component(entityEnnemy, BossTag{false});
        enemy.add_component(entityEnnemy, ExplosionTag{false});
        enemy.add_component(entityEnnemy, Song{enemyMusicID, true});
        enemy.add_component(entityEnnemy, Drawanle{spriteEnemy});
    }
    activeEnnemy = currentRound * 5;
}

void Window::spawn_entity_boss()
{
    if (!textBoss.loadFromFile("includes/assets/sprites/r-typesheet20.gif"))
        std::cout << "Error" << std::endl;
    spriteBoss.setTexture(textBoss);
    spriteBoss.setTextureRect(sf::IntRect(15, 67, 35, 30));
    spriteBoss.setScale(sf::Vector2f(3, 3));

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    auto ennemyBoss = enemy.spawn_entity();
    enemy.add_component(ennemyBoss, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(ennemyBoss, Velocity{-0.4, 0});
    enemy.add_component(ennemyBoss, BulletTag{false});
    enemy.add_component(ennemyBoss, Timer{0.0f});
    enemy.add_component(ennemyBoss, EnemyTag{true});
    enemy.add_component(ennemyBoss, BossTag{true});
    enemy.add_component(ennemyBoss, ExplosionTag{false});
    enemy.add_component(ennemyBoss, Song{enemyMusicID, true});
    enemy.add_component(ennemyBoss, Drawanle{spriteBoss});
    activeEnnemy = 1;
}

void Window::destructionShip(float x, float y)
{
    auto &position = enemy.get_components<Position>();

    if (!textEplosion.loadFromFile("includes/assets/sprites/r-typesheet44.gif"))
        std::cout << "Error" << std::endl;
    spriteExplosion.setTexture(textEplosion);
    spriteExplosion.setTextureRect(sf::IntRect(120, 0, 35, 40));
    spriteExplosion.setScale(sf::Vector2f(2, 2));
    spriteExplosion.setPosition(x, y);

    auto explosion = enemy.spawn_entity();
    enemy.add_component(explosion, Position{x, y});
    enemy.add_component(explosion, Velocity{0, 0});
    enemy.add_component(explosion, BulletTag{false});
    enemy.add_component(explosion, Timer{0.0f});
    enemy.add_component(explosion, EnemyTag{false});
    enemy.add_component(explosion, BossTag{false});
    enemy.add_component(explosion, ExplosionTag{true});
    enemy.add_component(explosion, Drawanle{spriteExplosion});
}