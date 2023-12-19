#include <iostream>
#include "../../includes/Client/window.hpp"

Window::Window()
{
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
}

void logging_system(Registry &reg, sparse_array<Position> const &position, sparse_array<Velocity> const &velocity)
{
    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            auto &pos = position[i].value();
            auto &vel = velocity[i].value();
            //std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << " with velocity " << vel.dx << ", " << vel.dy << std::endl;
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

    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            if (position[i]->x <= -150 || position[i]->x >= 2081)
                reg.kill_entity(reg.entity_from_index(i));
            position[i]->x += velocity[i]->dx;
            position[i]->y += velocity[i]->dy;
        }
    }
}

void draw_system(Registry &reg, sf::RenderWindow &window) {
    auto &position = reg.get_components<Position>();
    auto &drawable = reg.get_components<Drawanle>();
    auto &bullet = reg.get_components<BulletTag>();
    
    for (size_t i = 0; i < position.size() && i < drawable.size(); ++i) {
        if (position[i] && drawable[i]) {
            if (bullet[i]->isBullet) {
                auto rect = drawable[i]->sprites.getTextureRect();
                if (rect.left >= 204)
                    rect.left = 0;
                else
                    rect.left += 17;
                drawable[i]->sprites.setTextureRect(rect);
            }
            drawable[i]->sprites.setPosition(position[i]->x, position[i]->y);
            window.draw(drawable[i]->sprites);
        }
    }
}

void Window::loadSprites() 
{
    if (!background.loadFromFile("includes/assets/Space.png"))
        std::cout << "Error" << std::endl;
    sprite[0].setTexture(background);
    sprite[0].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[0].setPosition(sf::Vector2f(0, 0));
    sprite[1].setTexture(background);
    sprite[1].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[1].setPosition(sf::Vector2f(1920, 0));
    sprite[2].setTexture(background);
    sprite[2].setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    sprite[2].setPosition(sf::Vector2f(-1920, 0));

    if (!textSprite.loadFromFile("includes/assets/sprites/r-typesheet27.gif"))
        std::cout << "Error" << std::endl;
    spriteShip.setTexture(textSprite);
    spriteShip.setTextureRect(sf::IntRect(33, 0, 33, 17));
    spriteShip.setScale(sf::Vector2f(3, 3));

    if (!textEnemy.loadFromFile("includes/assets/sprites/r-typesheet14.gif"))
        std::cout << "Error" << std::endl;
    spriteEnemy.setTexture(textEnemy);
    spriteEnemy.setTextureRect(sf::IntRect(0, 0, 50, 50));
    spriteEnemy.setScale(sf::Vector2f(3, 3));
}

void Window::startProject()
{
    loadSprites();
    ally.register_component<Position>();
    ally.register_component<Velocity>();
    ally.register_component<Controllable>();
    ally.register_component<BulletTag>();
    ally.register_component<Drawanle>();

    enemy.register_component<Position>();
    enemy.register_component<Velocity>();
    enemy.register_component<BulletTag>();
    enemy.register_component<Drawanle>();

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
        draw_system(r, _window);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        logging_system(r, position, velocity);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        position_system(r);
    });

    enemy.add_system<Position, Velocity>([this](Registry &r, auto const &position, auto const &velocity) {
        draw_system(r, _window);
    });

    auto entityAlly = ally.spawn_entity();

    ally.add_component(entityAlly, Position{500, 500});
    ally.add_component(entityAlly, Velocity{0, 0});
    ally.add_component(entityAlly, Controllable{});
    ally.add_component(entityAlly, BulletTag{false});
    ally.add_component(entityAlly, Drawanle{spriteShip});

    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(-16, 959);

    auto entityEnemy = enemy.spawn_entity();

    enemy.add_component(entityEnemy, Position{1900, static_cast<float>(dist(mt))});
    enemy.add_component(entityEnemy, Velocity{-0.6, 0});
    enemy.add_component(entityEnemy, BulletTag{false});
    enemy.add_component(entityEnemy, Drawanle{spriteEnemy});

    while (_window.isOpen()) {
        eventHandler();
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
        ally.run_systems();
        enemy.run_systems();
        checkCollision(ally, enemy);
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