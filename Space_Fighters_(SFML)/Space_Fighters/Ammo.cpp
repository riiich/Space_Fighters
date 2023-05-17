//
// Created by Rich on 5/29/2020.
//

#include "Ammo.h"

namespace AmmoNamespace
{
    Ammo::Ammo()
    {}

    Ammo::Ammo(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f scaleSize, float initialSpeed, float maxVelocity, sf::Vector2f direction, float acceleration)
    {
        this->ammoText = texture;
        this->ammoSprite.setTexture(*this->ammoText);
        ammoSprite.setScale(scaleSize);
        this->ammoSprite.setPosition(pos);
        this->direction = direction;
        this->currVelocity = sf::Vector2f(initialSpeed * this->direction.x, this->direction.y);
        this->acceleration = acceleration;
        this->maxVelocity = maxVelocity;
        this->dtMultiplier = 62.5f;
    }

    sf::FloatRect Ammo::getBounds() const
    {
        return this->ammoSprite.getGlobalBounds();
    }

    void Ammo::move(const float& dt)
    {
        if(this->acceleration > 0.f)
        {
            if(this->currVelocity.x < this->maxVelocity)
            {
                this->currVelocity.x += this->acceleration * this->direction.x * dt * this->dtMultiplier;
            }
            if(this->currVelocity.y < this->maxVelocity)
            {
                this->currVelocity.y += this->acceleration * this->direction.y * dt * this->dtMultiplier;
            }
        }
        else
        {
            this->currVelocity = sf::Vector2f(this->maxVelocity * this->direction.x, this->maxVelocity * this->direction.y);
        }

        this->ammoSprite.move(this->currVelocity * dt * this->dtMultiplier);
     }

    void Ammo::update(const float& dt)
    {
        this->move(dt);    //bullet moves at this speed
    }

    void Ammo::Draw(sf::RenderTarget& window)
    {
        window.draw(this->ammoSprite);
    }
}