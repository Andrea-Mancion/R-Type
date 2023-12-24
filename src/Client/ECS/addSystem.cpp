/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** addSystem
*/

#include "../../../includes/Client/functions.hpp"
#include <random>

void logging_system(Registry &reg, sparse_array<Position> const &position, sparse_array<Velocity> const &velocity)
{
    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            auto &pos = position[i].value();
            auto &vel = velocity[i].value();
            std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << " with velocity " << vel.dx << ", " << vel.dy << std::endl;
        }
    }
}

void control_system(Registry &reg) {
    auto [velocity, controllable] = getComponent<Velocity, Controllable>(reg);

    for (size_t i = 0; i < controllable.size() && i < velocity.size(); ++i) {
        if (controllable[i] && velocity[i]) {
            controllable[i]->up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            controllable[i]->down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            controllable[i]->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            controllable[i]->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

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

void draw_system(Registry &reg, sf::RenderWindow &window) {
    auto [position, drawable, bullet, enemy, boss, explosion] = getComponent<Position, Drawable, BulletTag, EnemyTag, BossTag, ExplosionTag>(reg);
    std::vector<entity> toDelete;
    
    for (size_t i = 0; i < position.size() && i < drawable.size(); ++i) {
        if (position[i] && drawable[i]) {
            if (bullet[i]->isBullet) {
                auto rect = drawable[i]->sprites.getTextureRect();
                if (rect.left >= 204)
                    rect.left = 0;
                else
                    rect.left += 17;
                drawable[i]->sprites.setTextureRect(rect);
            } else if (explosion[i] && explosion[i]->isExplosion) {
                auto rectExplosion = drawable[i]->sprites.getTextureRect();
                if (rectExplosion.left >= 440) {
                    toDelete.push_back(reg.entity_from_index(i));
                } else {
                    rectExplosion.left += 40;
                    drawable[i]->sprites.setTextureRect(rectExplosion);
                }
            } else if (enemy[i]->isEnemy && boss[i]->isBoss) {
                auto rectBoss = drawable[i]->sprites.getTextureRect();
                if (rectBoss.left >= 105)
                    rectBoss.left = 15;
                else
                    rectBoss.left += 35;
                drawable[i]->sprites.setTextureRect(rectBoss);
            } else if (enemy[i]->isEnemy && !boss[i]->isBoss) {
                auto rectEnemy = drawable[i]->sprites.getTextureRect();
                if (rectEnemy.left >= 200)
                    rectEnemy.left = 0;
                else
                    rectEnemy.left += 50;
                drawable[i]->sprites.setTextureRect(rectEnemy);
            }
            drawable[i]->sprites.setPosition(position[i]->x, position[i]->y);
            window.draw(drawable[i]->sprites);
        }
    }

    for (auto &i : toDelete)
        killEntity(reg, i);
}

std::pair<Registry&, bool> SFML::addSystemAlly(Registry &ally, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager)
{
    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        position_system(r);
    });

    ally.add_system<Position, Velocity>([&ally](Registry &r, auto const &position, auto const &velocity) {
        control_system(r);
    });

    ally.add_system<Position, Velocity>([&hasSongStarted, &bossStarted, &musicManager](Registry &r, auto const &position, auto const &velocity) {
        if (!hasSongStarted && !bossStarted) {
            song_system(r, musicManager);
            hasSongStarted = true;
        }
    });

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        draw_system(r, _window);
    });

    return {ally, hasSongStarted};
}

std::pair<Registry&, bool> SFML::addSystemEnemy(Registry &enemy, bool &hasSongStarted, bool &bossStarted, MusicManager &musicManager)
{
    enemy.add_system<Position, Velocity>([&enemy](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    enemy.add_system<Position, Velocity>([&enemy](Registry &r, auto const &position, auto const &velocity) {
        position_system(r);
    });

    enemy.add_system<Position, Velocity>([&hasSongStarted, &bossStarted, &musicManager](Registry &r, auto const &position, auto const &velocity) {
        if (!hasSongStarted && bossStarted) {
            song_system(r, musicManager);
            hasSongStarted = true;
        }
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        draw_system(r, _window);
    });

    return {enemy, hasSongStarted};
}