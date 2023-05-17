//
// Created by Rich on 5/29/2020.
//
#include <iostream>
#include "Enemy.h"

namespace EnemyNamespace
{
    Enemy::Enemy()
    {}

    Enemy::Enemy(sf::Texture* textEnemy, float x, float y, sf::Vector2f scaleSize, sf::Vector2f direction, int type,
                 int points, float speed, int maxHP, int minDMG, int maxDMG)
    {
        this->initEnemySprite(textEnemy);
        this->initEnemyVar(type, speed, maxHP, points, minDMG, maxDMG);
        this->enemySprite.setPosition(x, y);
        this->enemySprite.setScale(scaleSize);
        this->direction = direction;
    }

    Enemy::~Enemy()
    {
        for(int i = 0; i < this->bullets.size(); i++)
        {
            delete this->bullets[i];
        }
    }

    void Enemy::initEnemyVar(int type, float speed, int maxHP, int points, int minDMG, int maxDMG)
    {
        this->maxHealth = maxHP;
        this->health = this->maxHealth;
        this->maxDmg = maxDMG;
        this->minDmg = minDMG;
        this->points = points;
        this->enemySpeed = speed;
        this->type = type;
        this->dtMultiplier = 62.5f;
        this->maxDamagedTimer = 5.0f;
        this->damagedTime = this->maxDamagedTimer;
        this->maxShootCooldown = 60.f;
        this->shootCooldown = 0.f;
        this->enemyBulletText.loadFromFile("..\\Space_Fighters/Sprites/purpleEnergyOrb.png");
    }

    void Enemy::initEnemySprite(sf::Texture* enemyTexture)
    {
        this->enemySprite.setTexture(*enemyTexture);
    }

    const sf::FloatRect Enemy::getGBounds() const
    {
        return this->enemySprite.getGlobalBounds();
    }

    const sf::Vector2f& Enemy::getEnemyPos() const
    {
        return this->enemySprite.getPosition();
    }

    std::vector<AmmoNamespace::Ammo*>& Enemy::getAmmo()
    {
        return this->bullets;
    }

    float Enemy::vecLength(sf::Vector2f vec)
    {
        return sqrt(pow(vec.x, 2) + pow(vec.y,2));  //sqrt(a^2 + b^2)
    }

    sf::Vector2f Enemy::normalLine(sf::Vector2f vec, float length)
    {
        return vec/length;      // x/|x| (|x| = length(norm))
    }

    int Enemy::getHP() const
    {
        return this->health;
    }

    int Enemy::getMaxHP() const
    {
        return this->maxHealth;
    }

    bool Enemy::isDead() const
    {
        return (this->health <= 0);
    }

    void Enemy::damaged(int dmgAmt)
    {
        this->health -= dmgAmt;

        this->damagedTime = this->maxDamagedTimer;

        if(this->health <= 0)
            this->health = 0;
    }

    int Enemy::getPoint() const
    {
        return this->points;    //return how the point of the enemies
    }

    int Enemy::getDmg() const
    {
        return (rand() % this->maxDmg + this->minDmg);
    }

    void Enemy::update(const float& dt, sf::Vector2f playerPos)
    {
        this->centerEnemy.x = this->enemySprite.getPosition().x + this->enemySprite.getGlobalBounds().width/2;
        this->centerEnemy.y = this->enemySprite.getPosition().y + this->enemySprite.getGlobalBounds().height/2;

        sf::Vector2f normalVector;
        double pi = 3.1415926;

        switch(this->type)
        {
            case 0:
                this->enemySprite.move(0.f * dt * this->dtMultiplier, enemySpeed * dt * this->dtMultiplier);

                break;

            case follow:
                this->maxHealth *= 3;
                this->direction.x = playerPos.x - this->enemySprite.getPosition().x;
                this->direction.y = playerPos.y - this->enemySprite.getPosition().y;

                normalVector = normalLine(this->direction, vecLength(this->direction));

                //make it so that when the player goes past the following enemies, it doesn't follow them,
                //  it continues moving down
                if(normalVector.x > 0.5)
                    normalVector.x = 0.5;
                else if(normalVector.x < -0.5)
                    normalVector.x = -0.5;
                if(normalVector.y < 1)
                    normalVector.y = 1;

                this->enemySprite.setRotation(atan2(normalVector.y, normalVector.x) * 180/pi - 90);
                this->enemySprite.move(normalVector.x * this->enemySpeed * dt * this->dtMultiplier,
                                       normalVector.y * this->enemySpeed * dt * this->dtMultiplier);

                break;

            case shootnFollow:
                this->maxHealth *= 5;
                if(this->shootCooldown < this->maxShootCooldown)
                {
                    this->shootCooldown += 1.f * dt * this->dtMultiplier;
                }

                this->direction.x = playerPos.x - this->enemySprite.getPosition().x;
                this->direction.y = playerPos.y - this->enemySprite.getPosition().y;

                normalVector = normalLine(this->direction, vecLength(this->direction));

                //make it so that when the player goes past the following enemies, it doesn't follow them,
                //  it continues moving down
                if(normalVector.x > 0.5)
                    normalVector.x = 0.5;
                else if(normalVector.x < -0.5)
                    normalVector.x = -0.5;
                if(normalVector.y < 1)
                    normalVector.y = 1;

                this->enemySprite.setRotation(atan2(normalVector.y, normalVector.x) * 180/pi - 90);
                this->enemySprite.move(normalVector.x * this->enemySpeed * dt * this->dtMultiplier,
                                       normalVector.y * this->enemySpeed * dt * this->dtMultiplier);

                if(this->shootCooldown >= this->maxShootCooldown)
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(&this->enemyBulletText,
                                                                    this->enemySprite.getPosition(),
                                                                    sf::Vector2f{.08f, .08f}, 3.f, 7.f,
                                                                    normalVector, 1.f));

                    this->shootCooldown = 0.f;
                }

                break;


            default:

                break;
        }

        if(this->damagedTime > 0.f)
        {
            this->damagedTime -= 1.f * dt * this->dtMultiplier;
            this->enemySprite.setColor(sf::Color::Red);
            this->enemySprite.move(0.f, -10.f);
        }
        else
        {
            this->enemySprite.setColor(sf::Color::White);
        }
    }

    void Enemy::Draw(sf::RenderTarget& target) const
    {
        target.draw(this->enemySprite);

        for(int i = 0; i < this->bullets.size(); i++)
        {
            this->bullets[i]->Draw(target);
        }
    }
}