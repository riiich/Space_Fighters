//
// Created by Rich on 6/8/2020.
//

#include "Meteor.h"

namespace MeteorNamespace
{
    Meteor::Meteor()
    {
        this->initMeteorVar();
        this->initMeteorText();
        this->initMeteorSprite();
        this->meteorSprite.setPosition(0.f, 0.f);
    }

    Meteor::Meteor(float x, float y)
    {
        this->initMeteorVar();
        this->initMeteorText();
        this->initMeteorSprite();
        this->meteorSprite.setPosition(x, y);
    }

    Meteor::~Meteor()
    {}

    void Meteor::initMeteorText()
    {
        if(!this->meteorText.loadFromFile("..\\Space_Fighters/Sprites/meteor.png"))
            std::cout << "ERROR: Meteor file is not found!\n";
    }

    void Meteor::initMeteorSprite()
    {
        this->meteorSprite.setTexture(this->meteorText);
        this->meteorSprite.setScale(.3f, .3f);
    }

    void Meteor::initMeteorVar()
    {
        this->diffPoints = (rand() % 9) + 2;    //minimum points = 2, max points = 10
        this->maxHealth = 50;//static_cast<int>(this->diffPoints);
        this->health = this->maxHealth;
        this->dmg = rand()%10 + 1;
        this->points = this->diffPoints;
        this->enemySpeed = static_cast<float>(rand()%10 + 15);
        this->dtMultiplier = 62.5f;
        this->maxDamagedTimer = 5.f;
        this->damagedTime = this->maxDamagedTimer;
    }

    const sf::FloatRect Meteor::getGBounds() const
    {
        return this->meteorSprite.getGlobalBounds();
    }

    const sf::Vector2f& Meteor::getEnemyPos() const
    {
        return this->meteorSprite.getPosition();
    }

    const int& Meteor::getPoint() const
    {
        return this->points;
    }

    const int& Meteor::getDmg() const
    {
        return this->dmg;
    }

    void Meteor::update(const float& dt)
    {
        this->meteorSprite.move(rand() % 6 * dt * this->dtMultiplier, this->enemySpeed * dt * this->dtMultiplier);
    }

    void Meteor::Draw(sf::RenderTarget& target) const
    {
        target.draw(this->meteorSprite);
    }
}