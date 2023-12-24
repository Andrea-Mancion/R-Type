/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** functions
*/

#include "window.hpp"
#include <cstring>

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

void printHelp();
std::streambuf *redirectCoutToFile(const std::string &filename);
void resetCout(std::streambuf *backup);
void registerComponentAlly(Registry &ally);
void registerComponentEnemy(Registry &enemy);
void killEntity(Registry &reg, std::size_t index);
template<typename... Components>
inline auto getComponent(Registry &reg) -> std::tuple<sparse_array<Components>&...> {
    return std::make_tuple(std::ref(reg.get_components<Components>())...);
}

#endif /* !FUNCTIONS_HPP_ */
