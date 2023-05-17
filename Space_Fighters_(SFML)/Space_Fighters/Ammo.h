//
// Created by Rich on 5/29/2020.
//

#ifndef SFML_PROJECTS_CS3A_AMMO_H
#define SFML_PROJECTS_CS3A_AMMO_H
#include "StatsText.h"

namespace AmmoNamespace
{
    class Ammo
    {
    public:
        Ammo();
        Ammo(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f scaleSize, float initialSpeed,
             float maxVelocity, sf::Vector2f direction, float acceleration); //sf::Vector2f maxSpeed = sf::Vector2f(0.f, 15.f)
        sf::FloatRect getBounds() const;
        void move(const float& dt);
        void update(const float& dt);
        void Draw(sf::RenderTarget & window);

    private:
        sf::Texture* ammoText;
        sf::Sprite ammoSprite;
        sf::Vector2f position;
        sf::Vector2f ammoSpeed;
        sf::Vector2f currVelocity;
        float maxVelocity;
        float acceleration;
        sf::Vector2f direction;
        float dtMultiplier;
    };
}

#endif //SFML_PROJECTS_CS3A_AMMO_H