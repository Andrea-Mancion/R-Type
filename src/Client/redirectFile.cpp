/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** redirectFile
*/

#include "../../includes/Client/window.hpp"

std::streambuf *redirectCoutToFile(const std::string &filename) 
{
    static std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return nullptr;
    }
    std::streambuf *backup = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());
    return backup;
}

void resetCout(std::streambuf *backup)
{
    std::cout.rdbuf(backup);
}