#include <iostream>
#include <SFML/Graphics.hpp>
#include "Space_Fighters/SpaceGame.h"
#include <ctime>

//SPACE FIGHTERS

int main()
{
    sf::Clock clock;
    float dt = 0.f;

    float timer;
    sf::Clock clock1;

    srand(time(0));
    bool GAME_STARTED = true;
    bool SPLASHSCREEN = true;

    sf::RenderWindow window(sf::VideoMode(1920,1080,32),"test");
    window.setFramerateLimit(60);

    SpaceGameNamespace::SpaceGame game;

    game.start(window);

    while(window.isOpen())
    {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

            game.addEvents(window, event);
        }

        //TIMER
        timer = clock1.getElapsedTime().asSeconds();
        game.setTime(timer);

        dt = clock.restart().asSeconds();
        game.Setdt(dt);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            GAME_STARTED = false;
            game.exit();
        }

        window.clear(sf::Color::Black);
        if(GAME_STARTED)
        {
            game.addEvents(window);
            window.draw(game);
        }

        window.display();
    }
    return 0;
}