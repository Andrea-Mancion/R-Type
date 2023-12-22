#include <iostream>
#include "../../includes/Client/window.hpp"

Window::Window()
{
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    redirectCoutToFile("log.txt");
}

Window::~Window()
{
    resetCout(redirectCoutToFile("log.txt"));
}

bool Window::isAnyAllyShipLeft() const
{
    auto &position = ally.get_components<Position>();
    auto &bullet = ally.get_components<BulletTag>();
    int count = 0;

    for (std::size_t i = 0; i < position.size(); i++) {
        if (position[i] && !bullet[i]->isBullet)
            count++;
    }

    return count > 0;
}

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
    auto &velocity = reg.get_components<Velocity>();
    auto &controllable = reg.get_components<Controllable>();

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
    auto &position = reg.get_components<Position>();
    auto &velocity = reg.get_components<Velocity>();
    auto &bullet = reg.get_components<BulletTag>();
    auto &enemy = reg.get_components<EnemyTag>();

    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            if ((position[i]->x <= -150 || position[i]->x >= 2081) && bullet[i]->isBullet)
                reg.kill_entity(reg.entity_from_index(i));
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
    auto &song = reg.get_components<Song>();
    auto &boss = reg.get_components<BossTag>();

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
    auto &position = reg.get_components<Position>();
    auto &drawable = reg.get_components<Drawable>();
    auto &bullet = reg.get_components<BulletTag>();
    auto &enemy = reg.get_components<EnemyTag>();
    auto &boss = reg.get_components<BossTag>();
    auto &explosion = reg.get_components<ExplosionTag>();
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
        reg.kill_entity(i);
}

void Window::startProject()
{
    allyMusicID = musicManager.loadMusic("includes/assets/SpaceMusic.ogg");
    bossMusicID = musicManager.loadMusic("includes/assets/BossTheme.ogg");

    loadSprites();
    ally = registerComponentAlly(ally);
    enemy = registerComponentEnemy(enemy);

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        position_system(r);
    });

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        control_system(r);
    });

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        if (!this->hasSongStarted && !this->bossStarted) {
            song_system(r, musicManager);
            this->hasSongStarted = true;
        }
    });

    ally.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        draw_system(r, _window);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        position_system(r);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        if (!this->hasSongStarted && this->bossStarted) {
            song_system(r, musicManager);
            this->hasSongStarted = true;
        }
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        draw_system(r, _window);
    });

    auto entityAlly = ally.spawn_entity();

    ally.add_component(entityAlly, Position{500, 500});
    ally.add_component(entityAlly, Velocity{0, 0});
    ally.add_component(entityAlly, Controllable{});
    ally.add_component(entityAlly, BulletTag{false});
    ally.add_component(entityAlly, Timer{0.0f});
    ally.add_component(entityAlly, EnemyTag{false});
    ally.add_component(entityAlly, BossTag{false});
    ally.add_component(entityAlly, ExplosionTag{false});
    ally.add_component(entityAlly, Song{allyMusicID, false, true, false});
    ally.add_component(entityAlly, Drawable{spriteShip});

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    auto entityEnemy = enemy.spawn_entity();

    enemy.add_component(entityEnemy, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(entityEnemy, Velocity{-0.4, 0});
    enemy.add_component(entityEnemy, BulletTag{false});
    enemy.add_component(entityEnemy, Timer{0.0f});
    enemy.add_component(entityEnemy, EnemyTag{true});
    enemy.add_component(entityEnemy, BossTag{false});
    enemy.add_component(entityEnemy, ExplosionTag{false});
    enemy.add_component(entityEnemy, Drawable{spriteEnemy});

    while (_window.isOpen()) {
        float time = clock.restart().asSeconds();
        eventHandler();
        if (!isAnyAllyShipLeft()) {
            std::cout << "Oh no you're dead Game Over" << std::endl;
            _window.close();
        }
        sprite[0].move(-0.1, 0);
        sprite[1].move(-0.1, 0);
        sprite[2].move(-0.1, 0);
        if (sprite[0].getPosition().x <= -1920)
            sprite[0].setPosition(sf::Vector2f(0, 0));
        if (sprite[1].getPosition().x <= -1920)
            sprite[1].setPosition(sf::Vector2f(1920, 0));
        if (sprite[2].getPosition().x <= -1920)
            sprite[2].setPosition(sf::Vector2f(3840, 0));

        _window.clear();
        _window.draw(sprite[0]);
        _window.draw(sprite[1]);
        _window.draw(sprite[2]);
        updateMusic();
        ally.run_systems();
        enemy.run_systems();
        enemy_shooting(time);
        checkCollision();
        _window.display();
    }
}

int main(int ac, char** av)
{
    Window window;

    try {
        window.startProject();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}