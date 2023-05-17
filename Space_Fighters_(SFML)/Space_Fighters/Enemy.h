//
// Created by Rich on 5/29/2020.
//

#ifndef SFML_PROJECTS_CS3A_ENEMY_H
#define SFML_PROJECTS_CS3A_ENEMY_H
#include <SFML/Graphics.hpp>
#include "Ammo.h"
#include <cstdlib>
#include <cmath>
#include <vector>

namespace EnemyNamespace
{
    enum enemyType{normal = 0, follow, shootnFollow};

    class Enemy
    {
    public:
        Enemy();
        Enemy(sf::Texture* textEnemy, float x, float y, sf::Vector2f scaleSize, sf::Vector2f direction, int type,
              int points, float speed, int maxHP, int minDMG, int maxDMG);
        ~Enemy();
        void initEnemySprite(sf::Texture* enemyTexture); //initialize enemy sprite
        void initEnemyVar(int type, float speed, int maxHP, int points, int minDMG, int maxDMG);    //initialize enemy variables
        const sf::FloatRect getGBounds() const;
        const sf::Vector2f& getEnemyPos() const;
        std::vector<AmmoNamespace::Ammo*>& getAmmo();
        float vecLength(sf::Vector2f vec);
        sf::Vector2f normalLine(sf::Vector2f vec, float length);    //normalize to get direction
        int getHP() const;
        int getMaxHP() const;
        bool isDead() const;    //check if the enemy is dead
        void damaged(int dmgAmt);   //enemy takes damage
        int getPoint() const;
        int getDmg() const;
        void update(const float& dt, sf::Vector2f playerPos);
        void Draw(sf::RenderTarget& target) const;

    private:
        sf::Sprite enemySprite;
        sf::Texture enemyBulletText;
        std::vector<AmmoNamespace::Ammo*> bullets;
        float shootCooldown;
        float maxShootCooldown;
        int health;
        int maxHealth;
        int minDmg;
        int maxDmg;
        int points;
        float enemySpeed;
        sf::Vector2f centerEnemy;
        sf::Vector2f direction;
        int type;
        float damagedTime;
        float maxDamagedTimer;
        float dtMultiplier;
    };
}

#endif //SFML_PROJECTS_CS3A_ENEMY_H