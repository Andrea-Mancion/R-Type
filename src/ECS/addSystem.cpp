/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** addSystem
*/

#include "../../includes/Client/functions.hpp"
#include <random>

/**
 * @brief Logs the position and velocity of entities in the given registry.
 * 
 * Iterates through the provided registries of positions and velocities, logging
 * the position and velocity of each entity. Only entities that have both a position
 * and velocity component are considered for logging.
 * 
 * @param reg The registry containing the entities.
 * @param position A sparse array of positions associated with the entities.
 * @param velocity A sparse array of velocities associated with the entities.
 * 
 * @note This function is useful for debugging purposes, to track entity movement and behavior.
 */

void logging_system(Registry &reg, sparse_array<Position> const &position, sparse_array<Velocity> const &velocity)
{
    (void)reg;
    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            auto &pos = position[i].value();
            auto &vel = velocity[i].value();
            std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << " with velocity " << vel.dx << ", " << vel.dy << std::endl;
        }
    }
}

/**
 * @brief Processes player input for controlling entities in the game.
 * 
 * Iterates through entities with both velocity and controllable components in the given registry. 
 * Updates the velocity of each controllable entity based on keyboard input (Up, Down, Left, Right).
 * 
 * @param reg The registry containing the entities to be controlled.
 * 
 * @note This function directly interfaces with the SFML Keyboard module to read the current state
 *       of the keyboard and modify the entity velocities accordingly. It's part of the game's 
 *       input handling system.
 */

void control_system(Registry &reg) {
    auto [velocity, controllable] = getComponent<Velocity, Controllable>(reg);

    for (size_t i = 0; i < controllable.size() && i < velocity.size(); ++i) {
        if (controllable[i] && velocity[i]) {
            controllable[i]->up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
            controllable[i]->down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            controllable[i]->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
            controllable[i]->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            if (controllable[i]->up)
                velocity[i]->dy = -1;
            else if (controllable[i]->down)
                velocity[i]->dy = 1;
            else if (controllable[i]->left)
                velocity[i]->dx = -1;
            else if (controllable[i]->right)
                velocity[i]->dx = 1;
            else {
                velocity[i]->dx = 0;
                velocity[i]->dy = 0;
            }
        }
    }
}

/**
 * @brief Updates the position of entities based on their velocity and handles boundary conditions.
 * 
 * Iterates through entities that have both position and velocity components. Updates their positions 
 * based on their velocities. Additionally, it handles boundary conditions for bullets and enemies, 
 * destroying or repositioning them as needed when they reach the edge of the screen.
 * 
 * @param reg The registry containing the entities whose positions are to be updated.
 * 
 * @note This function is a key part of the game's physics and entity management systems. It ensures 
 *       that entities behave correctly when they reach the boundaries of the game world.
 */

void position_system(Registry &reg) {
    auto [position, velocity, bullet, enemy] = getComponent<Position, Velocity, BulletTag, EnemyTag>(reg);

    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            if ((position[i]->x <= -150 || position[i]->x >= 2081) && bullet[i]->isBullet)
                killEntity(reg, i);
            else if ((position[i]->x <= -150 || position[i]->x >= 2081) && enemy[i]->isEnemy) {
                position[i]->x = 1900;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(-16, 959);
                position[i]->y = static_cast<float>(dis(gen));
            } else if (position[i]->x <= -150 || position[i]->x >= 2081)
                position[i]->x = 500;
            position[i]->x += velocity[i]->dx;
            position[i]->y += velocity[i]->dy;
        }
    }
}

/**
 * @brief Manages the playback of music based on game state.
 * 
 * Iterates through entities with a Song component, managing the playback of music tracks.
 * It starts or stops the music based on the `shouldPlay` and `isPlaying` flags of each Song entity.
 * 
 * @param reg The registry containing entities with song components.
 * @param musicManager The manager handling the music tracks.
 * 
 * @note This system interacts with the SFML Music class to control audio playback.
 *       It's an integral part of the game's audio system, providing dynamic music control
 *       based on game events.
 */

void song_system(Registry &reg, MusicManager &musicManager) {
    auto [song, boss] = getComponent<Song, BossTag>(reg);

    for (size_t i = 0; i < song.size(); ++i) {
        if (song[i]) {
            std::cout << "SHOUL PLAY " << song[i]->shouldPlay << " IS PLAYING " << song[i]->isPlaying << std::endl;
            sf::Music *music = musicManager.getMusic(song[i]->musicID);
            if (song[i]->shouldPlay && !song[i]->isPlaying) {
                if (music) {
                    music->setVolume(50);
                    music->setLoop(true);
                    music->play();
                }
                song[i]->isPlaying = true;
            } else if (!song[i]->shouldPlay && song[i]->isPlaying) {
                if (music)
                    music->stop();
                song[i]->isPlaying = false;
            }
        }
    }
}

/**
 * @brief Renders drawable entities to the game window and manages sprite animations.
 * 
 * Iterates through entities that have both position and drawable components. Updates the texture
 * rectangle for animated sprites and sets their position before drawing them on the window. 
 * It also handles the removal of entities that have completed their animation (like explosions).
 * 
 * @param reg The registry containing drawable entities.
 * @param window The SFML render window where entities are drawn.
 * 
 * @note This function is a crucial part of the game's rendering system. It not only handles
 *       the drawing of sprites but also the progression of sprite animations and removal of
 *       entities after animation completion.
 */

void draw_system(Registry &reg, sf::RenderWindow &window, int &bossTimer) {
    auto [position, drawable, bossUltime] = getComponent<Position, Drawable, BossUltimateTag>(reg);
    
    for (size_t i = 0; i < position.size() && i < drawable.size(); ++i) {
        if (position[i] && drawable[i]) {
            drawable[i]->sprites.setPosition(position[i]->x, position[i]->y);
            if (bossUltime[i]->isBoss == true && bossUltime[i]->isVisible == true) {
                window.draw(drawable[i]->sprites);
            } else if (!bossUltime[i]->isBoss)
                window.draw(drawable[i]->sprites);
        }
    }
}

void drawText_system(Registry &reg, sf::RenderWindow &window)
{
    auto [position, drawable] = getComponent<Position, DrawableText>(reg);

    for (size_t i = 0; i < position.size() && i < drawable.size(); ++i) {
        if (position[i] && drawable[i]) {
            drawable[i]->text.setPosition(position[i]->x, position[i]->y);
            window.draw(drawable[i]->text);
        }
    }
}

/**
 * @brief Adds systems to the ally registry for various game functionalities.
 * 
 * Registers several systems for the ally entities, including logging, position updates, control handling,
 * music management, and drawing. These systems are responsible for the core functionalities related to
 * ally entities in the game.
 * 
 * @param ally The ally entity registry.
 * @param hasSongStarted Reference to a flag indicating if the song has started.
 * @param bossStarted Reference to a flag indicating if the boss battle has started.
 * @param musicManager The music manager for handling game music.
 * 
 * @return Returns a pair containing a reference to the ally registry and the hasSongStarted flag.
 * 
 * @note This function is crucial for initializing the gameplay mechanics related to allies.
 */

std::pair<Registry&, bool> SFML::addSystemAlly(Registry &ally, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager, int &bossTimer)
{
    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        position_system(r);
    });

    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        control_system(r);
    });

    ally.add_system<Position, Velocity>([&hasSongStarted, &bossStarted, &musicManager](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        if (!hasSongStarted && !bossStarted) {
            song_system(r, musicManager);
            hasSongStarted = true;
        }
    });

    ally.add_system<Position, Velocity>([this, &bossTimer](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        draw_system(r, _window, bossTimer);
    });

    return {ally, hasSongStarted};
}

/**
 * @brief Adds systems to the enemy registry for various game functionalities.
 * 
 * Registers several systems for the enemy entities, including logging, position updates, 
 * music management, and drawing. These systems are responsible for the core functionalities 
 * related to enemy entities in the game.
 * 
 * @param enemy The enemy entity registry.
 * @param hasSongStarted Reference to a flag indicating if the song has started.
 * @param bossStarted Reference to a flag indicating if the boss battle has started.
 * @param musicManager The music manager for handling game music.
 * 
 * @return Returns a pair containing a reference to the enemy registry and the hasSongStarted flag.
 * 
 * @note This function is crucial for initializing the gameplay mechanics related to enemies.
 */

std::pair<Registry&, bool> SFML::addSystemEnemy(Registry &enemy, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager, int &bossTimer)
{
    enemy.add_system<Position, Velocity>([&enemy](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    enemy.add_system<Position, Velocity>([&enemy](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        position_system(r);
    });

    enemy.add_system<Position, Velocity>([&hasSongStarted, &bossStarted, &musicManager](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        if (!hasSongStarted && bossStarted) {
            song_system(r, musicManager);
            hasSongStarted = true;
        }
    });

    enemy.add_system<Position, Velocity>([this, &bossTimer](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        draw_system(r, _window, bossTimer);
    });

    return {enemy, hasSongStarted};
}

Registry &SFML::addSystemText(Registry &textEditor) 
{
    textEditor.add_system<Position, Velocity>([&textEditor](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    textEditor.add_system<Position, Velocity>([&textEditor](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        position_system(r);
    });

    textEditor.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        (void)position;
        (void)velocity;
        drawText_system(r, _window);
    });
    return textEditor;
}