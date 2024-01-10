/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** registerComponent
*/

#include "../../../includes/Client/ECS/step.hpp"

/**
 * @brief Registers various component types for an ally entity in a registry.
 *
 * This function is used to initialize a registry with all the necessary components
 * that an ally entity might require in a game. It adds various components such as
 * position, velocity, controllability, and different tags that could be used to
 * differentiate between various entity types like bullets, enemies, bosses, and so on.
 *
 * The function ensures that the registry is prepared to handle different aspects
 * of an ally entity's behavior and characteristics in the game world, including
 * its movement, actions, and interactions with other entities.
 *
 * Components registered include:
 * - Position: For storing the entity's position.
 * - Velocity: For handling the entity's movement.
 * - Controllable: To mark the entity as player-controllable.
 * - BulletTag: To tag the entity as a bullet.
 * - Timer: For time-based events or behaviors.
 * - EnemyTag: To tag the entity as an enemy.
 * - BossTag: To tag the entity as a boss.
 * - BossUltimateTag: To tag the entity as a boss ultime.
 * - ExplosionTag: To tag the entity for explosion effects.
 * - Song: For associating music or sound effects.
 * - Drawable: To make the entity renderable in the game.
 *
 * @param ally Reference to the Registry object where components are to be registered.
 */

void registerComponentAlly(Registry &ally)
{
    ally.register_component<Position>();
    ally.register_component<Velocity>();
    ally.register_component<Controllable>();
    ally.register_component<BulletTag>();
    ally.register_component<Timer>();
    ally.register_component<TimerVisible>();
    ally.register_component<EnemyTag>();
    ally.register_component<BossTag>();
    ally.register_component<BossUltimateTag>();
    ally.register_component<ExplosionTag>();
    ally.register_component<Song>();
    ally.register_component<Drawable>();
}

/**
 * @brief Registers various component types for an enemy entity in a registry.
 *
 * This function initializes a registry with all the necessary components
 * that an enemy entity might require in a game. It adds various components such as
 * position, velocity, and different tags that could be used to
 * characterize different types of enemy entities like regular enemies, bosses, etc.
 *
 * The function prepares the registry to handle different aspects
 * of an enemy entity's behavior and characteristics in the game world, including
 * its movement, actions, and interactions with other entities.
 *
 * Components registered include:
 * - Position: For storing the entity's position.
 * - Velocity: For handling the entity's movement.
 * - BulletTag: To tag the entity as a bullet.
 * - Timer: For time-based events or behaviors.
 * - EnemyTag: To specifically tag the entity as an enemy.
 * - BossTag: To tag the entity as a boss.
 * - BossUltimateTag: To tag the entity as a boss ultime.
 * - ExplosionTag: To tag the entity for explosion effects.
 * - Song: For associating music or sound effects.
 * - Drawable: To make the entity renderable in the game.
 *
 * @param enemy Reference to the Registry object where components are to be registered.
 */

void registerComponentEnemy(Registry &enemy)
{
    enemy.register_component<Position>();
    enemy.register_component<Velocity>();
    enemy.register_component<BulletTag>();
    enemy.register_component<Timer>();
    enemy.register_component<TimerVisible>();
    enemy.register_component<EnemyTag>();
    enemy.register_component<BossTag>();
    enemy.register_component<BossUltimateTag>();
    enemy.register_component<ExplosionTag>();
    enemy.register_component<Song>();
    enemy.register_component<Drawable>();
}