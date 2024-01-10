/*
** EPITECH PROJECT, 2024
** B-CPP-500-REN-5-2-rtype-andrea.mancion
** File description:
** spriteAnimation
*/

#include "../../includes/Client/functions.hpp"

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