/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** collision
*/

#include "../../includes/Client/window.hpp"

static sf::FloatRect getBoundingBox(const sf::Sprite &sprite)
{
    return sprite.getGlobalBounds();
}

static bool collisions(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    return getBoundingBox(sprite1).intersects(getBoundingBox(sprite2));
}

void checkCollision(Registry &ally, Registry &ennemy) 
{
    auto &allyPosition = ally.get_components<Position>();
    auto &allyDrawable = ally.get_components<Drawanle>();
    auto &ennemyPosition = ennemy.get_components<Position>();
    auto &ennemyDrawable = ennemy.get_components<Drawanle>();

    for (std::size_t i = 0; i < allyPosition.size(); i++) {
        if (allyPosition[i] && allyDrawable[i]) {
            for (std::size_t j = 0; j < ennemyPosition.size(); j++) {
                if (ennemyPosition[j] && ennemyDrawable[j]) {
                    if (collisions(allyDrawable[i]->sprites, ennemyDrawable[j]->sprites)) {
                        ally.kill_entity(ally.entity_from_index(i));
                        ennemy.kill_entity(ennemy.entity_from_index(j));
                        return;
                    }
                }
            }
        }
    }
}