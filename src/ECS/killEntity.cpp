/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** killEntity
*/

#include "../../includes/ECS/step.hpp"

/**
 * @brief Kills an entity in the given registry.
 *
 * This function removes an entity from the registry. It first retrieves the entity
 * corresponding to the given index and then kills it, effectively removing it from
 * the registry.
 *
 * @param reg Reference to the Registry object where the entity resides.
 * @param index The index of the entity to be killed.
 */

void killEntity(Registry &reg, std::size_t index)
{
    reg.kill_entity(reg.entity_from_index(index));
}