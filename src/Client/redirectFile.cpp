/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** redirectFile
*/

#include "../../includes/Client/window.hpp"

/**
 * @brief Redirects the standard output (cout) stream to a file.
 *
 * This function redirects the output of the standard C++ output stream `std::cout`
 * to a specified file. This is useful for logging or capturing console output
 * in a file for later analysis. The function takes the name of the file to which
 * the output should be redirected.
 *
 * The function creates a static `std::ofstream` object for the file output. If the
 * file cannot be opened, it outputs an error message to `std::cerr` and returns `nullptr`.
 * Otherwise, it redirects the `std::cout` buffer to the file's buffer and returns
 * the original `std::cout` buffer so it can be restored later if needed.
 *
 * @param filename A `std::string` representing the name of the file to which `std::cout` will be redirected.
 * @return A pointer to the original `std::streambuf` of `std::cout`. Returns `nullptr` if the file fails to open.
 */

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

/**
 * @brief Restores the standard output (cout) stream to its original state.
 *
 * This function resets the buffer of the standard C++ output stream `std::cout` to its original state.
 * It is typically used in conjunction with `redirectCoutToFile` function. After redirecting the output
 * to a file, this function can be used to restore the output back to the standard console output.
 *
 * The function takes a pointer to a `std::streambuf` object, which is expected to be the original buffer
 * of `std::cout` before it was redirected. It sets the `std::cout`'s buffer back to this original buffer.
 *
 * @param backup A pointer to the original `std::streambuf` of `std::cout`, to restore it to its initial state.
 */

void resetCout(std::streambuf *backup)
{
    std::cout.rdbuf(backup);
}