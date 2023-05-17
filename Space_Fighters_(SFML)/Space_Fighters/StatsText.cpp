//
// Created by horic on 12/4/2020.
//

#include "StatsText.h"

namespace StatsTextNameSpace
{
    StatsText::StatsText()
    {}

    StatsText::StatsText(sf::Font* font, std::string textString, sf::Vector2f pos, unsigned int size, const sf::Color color, sf::Vector2f direction)
    {
        this->text.setFont(*font);
        this->text.setCharacterSize(size);
        this->text.setString(textString);
        this->text.setPosition(pos);
        this->text.setFillColor(color);
        this->dtMultiplier = 62.5f;
        this->maxTimer = 50.f;
        this->timer = this->maxTimer;
        this->direction = direction;    //text information will go towards a certain direction
        this->speed = 2.f;
    }

    const float& StatsText::getTimer() const
    {
        return this->timer;
    }

    void StatsText::Update(const float &dt)
    {
        if(this->timer > 0.f)
        {
            this->timer -= 1.f * dt * dtMultiplier;
            this->text.move(this->speed * this->direction.x * dt * dtMultiplier,
                            this->speed * this->direction.y * dt * dtMultiplier);
        }
        else
        {
            this->text.setFillColor(sf::Color(0, 0, 0, 0)); //make the text invisible
        }
    }

    void StatsText::Draw(sf::RenderTarget& target) const
    {
        target.draw(this->text);
    }
}