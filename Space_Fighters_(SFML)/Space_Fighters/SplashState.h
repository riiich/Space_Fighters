//
// Created by horic on 12/10/2020.
//

#ifndef SFML_PROJECTS_CS3A_SPLASHSTATE_H
#define SFML_PROJECTS_CS3A_SPLASHSTATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

namespace SplashStateNameSpace
{
    class SplashState
    {
    public:
        SplashState();
        void initSplashState();
        void inputHandling( sf::RenderWindow& window);
        void update();
        void draw( sf::RenderTarget& window) const;

    private:
        sf::Texture titleTexture;
        sf::Sprite titleSprite;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Texture enterTexture;
        sf::Sprite enterSprite;
        sf::Font splashFont;
        sf::Text splashText;
    };
}

#endif //SFML_PROJECTS_CS3A_SPLASHSTATE_H
