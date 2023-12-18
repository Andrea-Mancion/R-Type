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

    for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
        if (position[i] && velocity[i]) {
            position[i]->x += velocity[i]->dx;
            position[i]->y += velocity[i]->dy;
        }
    }
}

void draw_system(Registry &reg, sf::RenderWindow &window) {
    auto &position = reg.get_components<Position>();
    auto &drawable = reg.get_components<Drawanle>();

    for (size_t i = 0; i < position.size() && i < drawable.size(); ++i) {
        if (position[i] && drawable[i]) {
            drawable[i]->shape.setPosition(position[i]->x, position[i]->y);
            window.draw(drawable[i]->shape);
        }
    }
}

void Window::startProject()
{
    ally.register_component<Position>();
    ally.register_component<Velocity>();
    ally.register_component<Controllable>();
    ally.register_component<Drawanle>();

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

    auto entityAlly = ally.spawn_entity();

    ally.add_component(entityAlly, Position{500, 500});
    ally.add_component(entityAlly, Velocity{0, 0});
    ally.add_component(entityAlly, Controllable{});
    ally.add_component(entityAlly, Drawanle{sf::RectangleShape(sf::Vector2f(100, 100))});

    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();
        draw_system(ally, _window);
        ally.run_systems();
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