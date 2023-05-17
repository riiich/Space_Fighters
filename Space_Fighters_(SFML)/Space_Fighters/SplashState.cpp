//
// Created by horic on 12/10/2020.
//

#include "SplashState.h"

namespace SplashStateNameSpace
{
    SplashState::SplashState()
    {}

    void SplashState::initSplashState()
    {
        //title
        if(!this->titleTexture.loadFromFile("..\\Space_Fighters/Sprites/spaceFightersTitle.png"))
            std::cout << "ERROR: SPACE FIGHTERS TITLE IMAGE FILE IS NOT FOUND!\n";
        this->titleSprite.setTexture(this->titleTexture);
        this->titleSprite.setScale(sf::Vector2f{1.5f, 1.2f});
        this->titleSprite.setPosition(400.f, 200.f);

        //background
        this->backgroundTexture.loadFromFile("..\\Space_Fighters/Sprites/splashScreenBG.jpg");
        this->backgroundSprite.setTexture(this->backgroundTexture);

        //enter to play sprite
        this->enterTexture.loadFromFile("..\\Space_Fighters/Sprites/Enter.png");
        this->enterSprite.setTexture(this->enterTexture);
        this->enterSprite.setScale(0.5f, 0.5f);
        this->enterSprite.setPosition(680.f, 450.f);

        //font and text
        this->splashFont.loadFromFile("..\\Space_Fighters/Fonts/laser.ttf");
        this->splashText.setFont(this->splashFont);
        this->splashText.setCharacterSize(40.f);
        this->splashText.setFillColor(sf::Color(57, 255, 20, 255));
        this->splashText.setString("Rich Ho\nCS 008\nCRN: 77061\nFall 2020\n");
        this->splashText.setPosition(sf::Vector2f{300.f, 650.f});
    }

    void SplashState::inputHandling( sf::RenderWindow& window)
    {
        sf::Event event;

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        {
            this->draw(window);
        }
    }

    void SplashState::update()
    {

    }

    void SplashState::draw(sf::RenderTarget& window) const
    {
        window.draw(this->backgroundSprite);
        window.draw(this->titleSprite);
        window.draw(this->enterSprite);
        window.draw(this->splashText);
    }
}