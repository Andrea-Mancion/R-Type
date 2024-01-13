/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** newStrat
*/

#include "../../includes/Client/functions.hpp"

void Window::changeStrat(int i)
{
    auto [bossUltime] = getComponent<BossUltimateTag>(enemy);

    isStratChanged = true;
    if (isXPressed == false)
        bossUltime[i]->isVisible = false;
    std::cout << "OK INVISIBLE" << std::endl;
}

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