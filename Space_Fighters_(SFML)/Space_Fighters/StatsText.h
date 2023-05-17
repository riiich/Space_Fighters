//
// Created by horic on 12/4/2020.
//

#ifndef SFML_PROJECTS_CS3A_STATSTEXT_H
#define SFML_PROJECTS_CS3A_STATSTEXT_H
#include <iostream>
#include <SFML/Graphics.hpp>

/*
 This class is made to create small texts of different information such as
    how much damage was dealt to the enemy from the player, how much exp
    you gained, etc...
 */

namespace StatsTextNameSpace
{
    class StatsText
    {
    public:
        StatsText();
        StatsText(sf::Font* font, std::string textString, sf::Vector2f pos, unsigned int size, const sf::Color color, sf::Vector2f direction);
        const float& getTimer() const;
        void Update(const float& dt);
        void Draw(sf::RenderTarget& target) const;

    private:
        sf::Font* font;
        sf::Text text;
        float dtMultiplier;
        float timer;    //timer for how long the text lasts
        float maxTimer;
        float speed;    //controls how fast the text floats off from the enemy or anything that provides some information
        sf::Vector2f direction; //this controls which direction the small text will go
    };
}


#endif //SFML_PROJECTS_CS3A_STATSTEXT_H
