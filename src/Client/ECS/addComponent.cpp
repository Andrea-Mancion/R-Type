/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** addComponent
*/

#include "../../../includes/Client/functions.hpp"
#include <random>

void SFML::addAllyShip(Registry &ally, int allyMusicID)
{
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
}

void SFML::addEnemy(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist)
{
    auto entityEnemy = enemy.spawn_entity();
    std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

    enemy.add_component(entityEnemy, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(entityEnemy, Velocity{-0.4, 0});
    enemy.add_component(entityEnemy, BulletTag{false});
    enemy.add_component(entityEnemy, Timer{shootDis(mt)});
    enemy.add_component(entityEnemy, EnemyTag{true});
    enemy.add_component(entityEnemy, BossTag{false});
    enemy.add_component(entityEnemy, ExplosionTag{false});
    enemy.add_component(entityEnemy, Drawable{spriteEnemy});
}

void SFML::addBoss(Registry &enemy, std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID)
{
    std::uniform_real_distribution<float> shootDis(0.0f, 5.0f);

    auto ennemyBoss = enemy.spawn_entity();
    enemy.add_component(ennemyBoss, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(ennemyBoss, Velocity{-0.4, 0});
    enemy.add_component(ennemyBoss, BulletTag{false});
    enemy.add_component(ennemyBoss, Timer{shootDis(mt)});
    enemy.add_component(ennemyBoss, EnemyTag{true});
    enemy.add_component(ennemyBoss, BossTag{true});
    enemy.add_component(ennemyBoss, ExplosionTag{false});
    enemy.add_component(ennemyBoss, Song{bossMusicID, true, true, false});
    enemy.add_component(ennemyBoss, Drawable{spriteBoss});
}

void SFML::addBullet(Registry &reg, float x, float y, float bulletSpeed)
{
    auto [enemy] = getComponent<EnemyTag>(reg);
    auto bulletEntity = reg.spawn_entity();

    reg.add_component(bulletEntity, Position{x, y});
    reg.add_component(bulletEntity, Velocity{bulletSpeed, 0});
    reg.add_component(bulletEntity, BulletTag{true});
    if (enemy[0]->isEnemy)
        reg.add_component(bulletEntity, Drawable{spriteEnemyBullet});
    else
        reg.add_component(bulletEntity, Drawable{spriteBullet});
}

void SFML::addExplosion(Registry &reg,  float x, float y)
{
    auto explosion = reg.spawn_entity();
    reg.add_component(explosion, Position{x, y});
    reg.add_component(explosion, Velocity{0, 0});
    reg.add_component(explosion, BulletTag{false});
    reg.add_component(explosion, Timer{0.0f});
    reg.add_component(explosion, EnemyTag{false});
    reg.add_component(explosion, BossTag{false});
    reg.add_component(explosion, ExplosionTag{true});
    reg.add_component(explosion, Drawable{spriteExplosion});
}