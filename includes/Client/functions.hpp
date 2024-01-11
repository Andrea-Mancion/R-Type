/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** functions
*/

/**
 * @file functions.hpp
 * @brief Utility functions for a game engine.
 *
 * This file contains declarations of utility functions that are used throughout the game engine.
 * These functions include operations such as printing help to the console, redirecting console
 * output to a file, resetting the console output, registering components for allies and enemies,
 * killing entities, and retrieving components from a registry.
 *
 * @version 1.0
 * @date 2023-12-24
 * @author Andrea Mancion
 * 
 * @note This file is part of the Epitech Project, B-CPP-500-REN-5-2-rtype-andrea.mancion.
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
void registerComponentText(Registry &textEditor);
void killEntity(Registry &reg, std::size_t index);

#endif /* !FUNCTIONS_HPP_ */
