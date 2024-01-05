/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** newStrat
*/

#include "../../includes/Client/functions.hpp"

// void Window::updateVisibility(int i, float dt)
// {
//     auto [bossUltime] = getComponent<BossUltimateTag>(enemy);

//     bossUltime[i]->visibleTimer += dt;

    
// }

void Window::changeStrat(int i, float dt)
{
    auto [bossUltime] = getComponent<BossUltimateTag>(enemy);

    isStratChanged = true;
    bossUltime[i]->isVisible = false;
    std::cout << "OK INVISIBLE" << std::endl;

    //updateVisibility(i, dt);
}