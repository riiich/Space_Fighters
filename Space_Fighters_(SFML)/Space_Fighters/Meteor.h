//
// Created by Rich on 6/8/2020.
//

#ifndef SFML_PROJECTS_CS3A_METEOR_H
#define SFML_PROJECTS_CS3A_METEOR_H
#include <SFML/Graphics.hpp>
#include <iostream>

namespace MeteorNamespace
{
    class Meteor
    {
    public:
        Meteor();
        Meteor(float x, float y);
        ~Meteor();
        void initMeteorVar();
        void initMeteorText();
        void initMeteorSprite();
        const sf::FloatRect getGBounds() const;
        const sf::Vector2f& getEnemyPos() const;
        const int& getPoint() const;
        const int& getDmg() const;
        void update(const float& dt);
        void Draw(sf::RenderTarget & target) const;

    private:
        sf::Texture meteorText;
        sf::Sprite meteorSprite;
        int health;
        int maxHealth;
        int dmg;
        int points;
        float enemySpeed;
        float asteroidSpeed;
        unsigned int diffPoints;
        float damagedTime;
        float maxDamagedTimer;
        float dtMultiplier;
    };
}



#endif //SFML_PROJECTS_CS3A_METEOR_H
