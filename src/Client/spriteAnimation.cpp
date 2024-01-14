/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** spriteAnimation
*/

#include "../../includes/Client/functions.hpp"

/**
 * @brief Changes the texture rectangle for animated sprites.
 *
 * This function iterates through the drawable entities in the game registry and updates
 * the texture rectangle for animated sprites based on their type and the current boss timer.
 *
 * For bullets, it cycles through different frames of the bullet sprite.
 * For explosions, it advances the animation frame, and entities with completed explosions are marked for deletion.
 * For enemies and bosses, it adjusts the texture rectangle based on the boss timer and entity type.
 *   - For regular enemies, it changes the frame based on the boss timer.
 *   - For the boss, it changes frames differently depending on whether it's the ultimate boss.
 *
 * @param bossTimer The current boss timer value.
 * @param reg The game registry containing entities and components.
 */

void SFML::changeRect(int &bossTimer, Registry &reg)
{
    auto [drawable, bullet, enemy, boss, explosion, bossUltime] = getComponent<Drawable, BulletTag, EnemyTag, BossTag, ExplosionTag, BossUltimateTag>(reg);
    std::vector<entity> toDelete;

    for (size_t i = 0; i < drawable.size(); ++i) {
        if (drawable[i]) {
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
            } else if (enemy[i]->isEnemy && boss[i]->isBoss && !bossUltime[i]->isBoss) {
                auto rectBoss = drawable[i]->sprites.getTextureRect();
                if (bossTimer == 0) {
                    if (rectBoss.left >= 105)
                        rectBoss.left = 15;
                    else
                        rectBoss.left += 35;
                } else if (bossTimer == 1) {
                    if (rectBoss.left >= 350)
                        rectBoss.left = 0;
                    else
                        rectBoss.left += 70;
                    rectBoss.left += 70;
                }
                drawable[i]->sprites.setTextureRect(rectBoss);
            } else if (enemy[i]->isEnemy && bossUltime[i]->isBoss && !boss[i]->isBoss) {
                auto rectBoss = drawable[i]->sprites.getTextureRect();
                if (rectBoss.left >= 515) {
                    rectBoss.left = 0;
                    rectBoss.top += 145;
                } else
                    rectBoss.left += 260;
                if (rectBoss.top >= 570) {
                    rectBoss.top = 0;
                    rectBoss.left = 0;
                }
                drawable[i]->sprites.setTextureRect(rectBoss);
            } else if (enemy[i]->isEnemy && !boss[i]->isBoss && !bossUltime[i]->isBoss) {
                auto rectEnemy = drawable[i]->sprites.getTextureRect();
                if (bossTimer == 0) {
                    if (rectEnemy.left >= 200)
                        rectEnemy.left = 0;
                    else
                        rectEnemy.left += 50;
                } else if (bossTimer == 1) {
                    if (rectEnemy.left >= 112)
                        rectEnemy.left = 0;
                    else
                        rectEnemy.left += 56;
                } else if (bossTimer == 2) {
                    if (rectEnemy.left >= 262)
                        rectEnemy.left = 0;
                    else
                        rectEnemy.left += 33;
                }
                drawable[i]->sprites.setTextureRect(rectEnemy);
            }
        }
    }

    for (auto &i : toDelete)
        killEntity(reg, i);
}