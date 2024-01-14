/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** nextRound
*/

#include "../../includes/Client/window.hpp"

/**
 * @brief Advances the game to the next round and spawns enemies or a boss.
 * 
 * Increments the round counter and resets the count of killed enemies. Depending on the round number,
 * it either spawns regular enemies or a boss. Every fifth round, a boss is spawned with increased health.
 * 
 * @note The function determines whether to spawn regular enemies or a boss based on the current round.
 *       It also manages the health scaling and state for boss rounds.
 */

void Window::startNextRound()
{
    if (bossTimer[1] != bossTimer[0])
        currentRound = 0;
    bossTimer[1] = bossTimer[0];
    currentRound++;
    maxEnnemyKilled = 0;
    if (currentRound % numberPerRound != 0)
        spawn_entity_foe();
    else {
        bossHP[0] *= 2;
        bossHP[1] = bossHP[0];
        bossStarted = true;
        if (bossTimer[1] == 2) {
            if (normalDifficulty == true) {
                if (troll == 10)
                    bossHP[1] = 200;
                else
                    bossHP[1] = 20;
                spawn_entity_boss_ultimate();
            } else if (hardDifficulty == true) {
                if (troll == 10)
                    bossHP[1] = 400;
                else
                    bossHP[1] = 100;
                spawn_entity_boss_ultimate();
                spawn_entity_foe(10);
            }
        } else
            if (normalDifficulty == true)
                spawn_entity_boss();
            else if (hardDifficulty == true) {
                spawn_entity_boss();
                spawn_entity_foe(5);
            }
    }
}