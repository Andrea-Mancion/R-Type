/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** killEntity
*/

#include "../../../includes/Client/step.hpp"

void killEntity(Registry &reg, std::size_t index)
{
    reg.kill_entity(reg.entity_from_index(index));
}