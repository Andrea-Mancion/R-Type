/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** registerComponent
*/

#include "../../../includes/Client/step.hpp"

Registry registerComponentAlly(Registry &ally)
{
    ally.register_component<Position>();
    ally.register_component<Velocity>();
    ally.register_component<Controllable>();
    ally.register_component<BulletTag>();
    ally.register_component<Timer>();
    ally.register_component<EnemyTag>();
    ally.register_component<BossTag>();
    ally.register_component<ExplosionTag>();
    ally.register_component<Song>();
    ally.register_component<Drawable>();

    return ally;
}

Registry registerComponentEnemy(Registry &enemy)
{
    enemy.register_component<Position>();
    enemy.register_component<Velocity>();
    enemy.register_component<BulletTag>();
    enemy.register_component<Timer>();
    enemy.register_component<EnemyTag>();
    enemy.register_component<BossTag>();
    enemy.register_component<ExplosionTag>();
    enemy.register_component<Song>();
    enemy.register_component<Drawable>();

    return enemy;
}