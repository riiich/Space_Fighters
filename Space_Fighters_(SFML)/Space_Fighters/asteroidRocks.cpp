//
// Created by horic on 12/1/2020.
//

#include "asteroidRocks.h"

namespace asteroidRocksNameSpace
{
    asteroidRocks::asteroidRocks()
    {
        this->initActualAsteroidText();
        this->initActualAsteroidsVar();
        this->initActualAsteroidsSprite();
        this->astSprite.setPosition(0.f, 0.f);
    }

    asteroidRocks::asteroidRocks(float x, float y)
    {
        this->initActualAsteroidText();
        this->initActualAsteroidsVar();
        this->initActualAsteroidsSprite();
        this->astSprite.setPosition(x, y);
    }

    const sf::FloatRect asteroidRocks::getGBounds() const
    {
        return this->astSprite.getGlobalBounds();
    }

    const sf::Vector2f& asteroidRocks::getEnemyPos() const
    {
        return this->astSprite.getPosition();
    }

    void asteroidRocks::initActualAsteroidText()
    {
        if(!this->astText.loadFromFile("..\\Space_Fighters/Sprites/asteroid.png"))
        {
            std::cout << "ERROR: Asteroid file is not found!\n";
        }
    }

    void asteroidRocks::initActualAsteroidsSprite()
    {
        this->astSprite.setTexture(this->astText);
        this->astSprite.setScale(.1f, .1f);
    }

    void asteroidRocks::initActualAsteroidsVar()
    {
        this->diffPoints = (rand() % 9) + 2;    //minimum points = 2, max points = 10
        this->maxHealth = static_cast<int>(this->diffPoints);
        this->health = this->maxHealth;
        this->dmg = rand()%10 + 1;
        this->points = this->diffPoints;
        this->asteroidSpeed = static_cast<float>(rand()%10 + 15);
        this->dtMultiplier = 62.5f;
    }
    const int& asteroidRocks::getPoint() const
    {
        return this->points;
    }

    const int& asteroidRocks::getDmg() const
    {
        return this->dmg;
    }

    void asteroidRocks::update(const float& dt)
    {
        this->astSprite.move(rand() % 6 * dt * this->dtMultiplier, this->asteroidSpeed * dt * this->dtMultiplier);
    }

    void asteroidRocks::Draw(sf::RenderTarget& target) const
    {
        target.draw(this->astSprite);
    }
}