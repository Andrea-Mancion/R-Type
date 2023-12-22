/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** functions
*/

#include "window.hpp"

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

std::streambuf *redirectCoutToFile(const std::string &filename);
void resetCout(std::streambuf *backup);
void registerComponentAlly(Registry &ally);
void registerComponentEnemy(Registry &enemy);
std::pair<Registry&, bool> addSystemAlly(Registry &ally, bool &hasSongStarted, bool &bossStarted, sf::RenderWindow &window, MusicManager &musicManager);
std::pair<Registry&, bool> addSystemEnemy(Registry &enemy, bool &hasSongStarted, bool &bossStarted, sf::RenderWindow &window, MusicManager &musicManager);
void addAllyShip(Registry &ally, int allyMusicID, sf::Sprite spriteShip);
void addEnemy(Registry &enemy, sf::Sprite spriteEnemy, std::mt19937 mt, std::uniform_int_distribution<int> dist);
void addBoss(Registry &enemy, sf::Sprite spriteBoss, std::mt19937 mt, std::uniform_int_distribution<int> dist, int bossMusicID);
void addBullet(Registry &reg, sf::Sprite spriteBullet, float x, float y, float bulletSpeed);
void addExplosion(Registry &reg, sf::Sprite spriteExplosion, float x, float y);
void killEntity(Registry &reg, std::size_t index);
template<typename... Components>
inline auto getComponent(Registry &reg) -> std::tuple<sparse_array<Components>&...> {
    return std::make_tuple(std::ref(reg.get_components<Components>())...);
}

#endif /* !FUNCTIONS_HPP_ */
