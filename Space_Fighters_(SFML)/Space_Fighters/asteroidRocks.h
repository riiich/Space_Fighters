//
// Created by horic on 12/1/2020.
//

#ifndef SFML_PROJECTS_CS3A_ASTEROIDROCKS_H
#define SFML_PROJECTS_CS3A_ASTEROIDROCKS_H
#include <SFML/Graphics.hpp>
#include <iostream>

namespace asteroidRocksNameSpace
{
    class asteroidRocks
    {
    public:
        asteroidRocks ();
        asteroidRocks (float x, float y);
        const sf::FloatRect getGBounds() const;
        const sf::Vector2f& getEnemyPos() const;
        void initActualAsteroidText();
        void initActualAsteroidsSprite();
        void initActualAsteroidsVar();
        const int& getPoint() const;
        const int& getDmg() const;
        void update(const float& dt);
        void Draw(sf::RenderTarget& target) const;

    private:
        sf::Texture astText;
        sf::Sprite astSprite;
        int health;
        int maxHealth;
        int dmg;
        int points;
        float asteroidSpeed;
        unsigned int diffPoints;
        float dtMultiplier;
    };
}



#endif //SFML_PROJECTS_CS3A_ASTEROIDROCKS_H
