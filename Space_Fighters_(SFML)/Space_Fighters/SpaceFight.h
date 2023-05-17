//
// Created by Rich on 6/4/2020.
//

#ifndef SFML_PROJECTS_CS3A_SPACEFIGHT_H
#define SFML_PROJECTS_CS3A_SPACEFIGHT_H
#include "../Game/Game.h"

class SpaceFight :public Game
{
public:
    SpaceFight();
    virtual void start(sf::RenderWindow& window);
    virtual void addEvents(sf::RenderWindow &window);
    virtual void addEvents(const sf::RenderWindow &window, sf::Event& event);
    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;
    virtual void exit();

private:

};


#endif //SFML_PROJECTS_CS3A_SPACEFIGHT_H
