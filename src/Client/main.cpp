#include <iostream>
#include "../../includes/Client/functions.hpp"

/**
 * @brief Constructor for the Window class.
 * 
 * This constructor initializes the game window using SFML. It sets the video mode to 1920x1080
 * and names the window "R-Type". It also redirects standard output to a log file.
 * 
 * @note The redirection of output to "log.txt" is for logging purposes and aids in debugging.
 *       Ensure that the SFML library is properly set up before creating a Window instance.
 */

Window::Window()
{
    _sfml.getWindow().create(sf::VideoMode(1920, 1080), "R-Type");
    redirectCoutToFile("log.txt");
}

/**
 * @brief Destructor for the Window class.
 * 
 * This destructor resets standard output, reversing the redirection established
 * in the constructor. The redirection is reset to standard output, typically the console.
 * 
 * @note It's important to reset the output stream to avoid issues or unexpected behavior
 *       in other parts of the program after the Window object is destroyed.
 */

Window::~Window()
{
    resetCout(redirectCoutToFile("log.txt"));
}

/**
 * @brief Checks if any ally ships are left in the game.
 * 
 * This function iterates over all entities in the ally registry and counts those
 * that are ships (not bullets). It returns true if there's at least one ship remaining.
 * 
 * @return Returns true if there is at least one ally ship left, otherwise false.
 * 
 * @note This function is used to determine the game's state, particularly to check
 *       whether the player has lost all ships and the game should end.
 */

bool Window::isAnyAllyShipLeft()
{
    auto [position, bullet] = getComponent<Position, BulletTag>(ally);
    int count = 0;

    for (std::size_t i = 0; i < position.size(); i++) {
        if (position[i] && !bullet[i]->isBullet)
            count++;
    }

    return count > 0;
}

/**
 * @brief Initializes and runs the main game loop.
 * 
 * This function sets up the game by loading music, initializing sprites, and setting up
 * game components and systems for both allies and enemies. It then enters the main game loop,
 * where it handles events, updates music, processes game systems, and renders sprites. 
 * The loop continues until the game window is closed.
 * 
 * @note This function manages the game's lifecycle and should be called after creating a Window instance.
 * 
 * Inside the game loop:
 * - The function checks if any ally ships are left.
 * - Moves background sprites to create a scrolling effect.
 * - Clears and redraws the window each frame.
 * - Manages enemy shooting and collision detection.
 */

void Window::startProject()
{
    allyMusicID = musicManager.loadMusic("includes/assets/SpaceMusic.ogg");
    bossMusicID = musicManager.loadMusic("includes/assets/BossTheme.ogg");

    loadSprites();
    registerComponentAlly(ally);
    registerComponentEnemy(enemy);

    _sfml.addSystemAlly(ally, hasSongStarted, bossStarted, musicManager);
    _sfml.addSystemEnemy(enemy, hasSongStarted, bossStarted, musicManager);

    _sfml.addAllyShip(ally, allyMusicID);

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);
    
    _sfml.addEnemy(enemy, mt, dist);
    
    while (_sfml.getWindow().isOpen()) {
        float time = _sfml.getClock().restart().asSeconds();
        eventHandler();
        if (!isAnyAllyShipLeft()) {
            std::cout << "Oh no you're dead Game Over" << std::endl;
            _sfml.getWindow().close();
        }
        _sfml.getSprite(0).move(-0.1, 0);
        _sfml.getSprite(1).move(-0.1, 0);
        _sfml.getSprite(2).move(-0.1, 0);
        if (_sfml.getSprite(0).getPosition().x <= -1920)
            _sfml.getSprite(0).setPosition(sf::Vector2f(0, 0));
        if (_sfml.getSprite(1).getPosition().x <= -1920)
            _sfml.getSprite(1).setPosition(sf::Vector2f(1920, 0));
        if (_sfml.getSprite(2).getPosition().x <= -1920)
            _sfml.getSprite(2).setPosition(sf::Vector2f(3840, 0));

        _sfml.getWindow().clear();
        _sfml.getWindow().draw(_sfml.getSprite(0));
        _sfml.getWindow().draw(_sfml.getSprite(1));
        _sfml.getWindow().draw(_sfml.getSprite(2));
        updateMusic();
        ally.run_systems();
        enemy.run_systems();
        enemy_shooting(time);
        checkCollision(time);
        checkLevel();
        _sfml.getWindow().display();
    }
}

/**
 * @brief Entry point for the game application.
 * 
 * This function serves as the entry point for the game. It checks for command-line arguments
 * and either prints the help message or starts the game depending on the arguments provided.
 * 
 * @param ac Argument count.
 * @param av Argument vector, a list of command-line arguments.
 * 
 * @return Returns 0 on successful execution, and 84 if an exception is caught.
 * 
 * @exception std::exception Captures and logs any standard exceptions thrown during execution.
 * 
 * @note The '-h' command-line argument is used to print the help message.
 *       If no arguments or different arguments are provided, the game starts normally.
 */

int main(int ac, char** av)
{
    try {
        if (ac == 2 && strcmp(av[1], "-h") == 0)
            printHelp();
        else if (ac == 1) {
            Window window;

            window.startProject();
        } else
            return 84;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}