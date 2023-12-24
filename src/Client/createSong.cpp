/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** song
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Updates the music playback status based on game entities.
 *
 * This method determines which songs should be played based on the current state
 * of game entities. It checks the presence and state of allies and enemies, specifically
 * focusing on whether a boss enemy is alive. Based on these conditions, it toggles
 * the music playback status (`shouldPlay`) for ally and enemy songs.
 *
 * The method retrieves songs associated with ally and enemy entities and assesses
 * whether a boss entity is alive. If a boss is alive, enemy songs are played;
 * otherwise, ally songs are played. Songs associated with non-boss enemies are
 * stopped when no boss is alive.
 *
 * The song components are expected to have a `shouldPlay` flag to indicate if they
 * should be currently playing, and a `isBoss` or `isEnemy` flag to distinguish
 * between boss and regular enemy songs.
 */

void Window::updateMusic()
{
    auto [allySong] = getComponent<Song>(ally);
    auto [enemySong, boss] = getComponent<Song, BossTag>(enemy);

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