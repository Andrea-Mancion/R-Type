/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** newStrat
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Changes the strategy for a specific boss entity.
 *
 * This function updates the strategy for the boss entity at the specified index.
 * It sets a flag indicating that the strategy has been changed and may hide the
 * boss entity based on certain conditions.
 *
 * @param i Index of the boss entity for which the strategy needs to be changed.
 */

void Window::changeStrat(int i)
{
    auto [bossUltime] = getComponent<BossUltimateTag>(enemy);

    isStratChanged = true;
    if (isXPressed == false)
        bossUltime[i]->isVisible = false;
    std::cout << "OK INVISIBLE" << std::endl;
}

/**
 * @brief Checks conditions for changing the strategy of boss entities.
 *
 * This function iterates through the boss entities, checks specific conditions,
 * and triggers a change in strategy if the conditions are met. The conditions include
 * the boss entity being a special type (bossUltime), not being an ally (isBoss=false),
 * having positive health points within a certain range, and a specific timer value.
 * If the conditions are satisfied, the strategy is changed for the first eligible boss entity.
 */

void Window::ifStratChanged()
{
    auto [ennemyPosition, bossUltime, boss] = getComponent<Position, BossUltimateTag, BossTag>(enemy);

    for (std::size_t i = 0; i < ennemyPosition.size(); i++) {
        if (bossUltime[i]->isBoss == true && boss[i]->isBoss == false && bossHP[1] > 0 && bossHP[1] <= 10 && bossTimer[1] == 2) {
            std::cout << "change strat" << " bossUtltime " << bossUltime[i]->isBoss << " boss " << boss[i]->isBoss << " bossHP " << bossHP[1] << std::endl;
            changeStrat(i);
            break;
        }
    }
}