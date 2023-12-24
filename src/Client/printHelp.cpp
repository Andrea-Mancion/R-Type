/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** printHelp
*/

#include <iostream>

/**
 * @brief Prints the help message for the game.
 * 
 * This function outputs the usage instructions and a brief description of the game.
 * It details the game's objective and basic premise to the user.
 * 
 * @note This function is typically called when the '-h' argument is passed to the program.
 */

void printHelp()
{
    std::cout << "USAGE: ./r-type_client" << std::endl;
    std::cout << "DESCRIPTION: " << std::endl;
    std::cout << "Welcome to my R-type game, you play as a ship lost in the space and you meet some... Things." << std::endl;
    std::cout << "Your goal is to survive as long as possible and kill as many enemies as you can." << std::endl;
}