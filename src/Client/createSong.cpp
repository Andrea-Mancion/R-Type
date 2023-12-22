/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** song
*/

#include "../../includes/Client/window.hpp"

void Window::updateMusic()
{
    auto &allySong = ally.get_components<Song>();
    auto &enemySong = enemy.get_components<Song>();
    auto &boss = enemy.get_components<BossTag>();

    bool bossIsAlive = std::any_of(boss.begin(), boss.end(), [](const auto &boss) {
        return boss && boss->isBoss;
    });

    for (auto &song : allySong) {
        if (song && !bossIsAlive)
            song->shouldPlay = true;
        else
            song->shouldPlay = false;
    }
    for (auto &song : enemySong) {
        if (song && bossIsAlive)
                song->shouldPlay = true;
        else if (song && song->isEnemy && !bossIsAlive)
            song->shouldPlay = false;
    }
}