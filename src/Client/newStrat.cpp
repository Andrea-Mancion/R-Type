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