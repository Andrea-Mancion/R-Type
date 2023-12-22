/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** nextRound
*/

#include "../../includes/Client/window.hpp"

void Window::startNextRound()
{
    currentRound++;
    maxEnnemyKilled = 0;
    if (currentRound % 2 != 0)
        spawn_entity_foe();
    else {
        bossHP[0] *= 2;
        bossHP[1] = bossHP[0];
        bossStarted = true;
        spawn_entity_boss();
    }
}