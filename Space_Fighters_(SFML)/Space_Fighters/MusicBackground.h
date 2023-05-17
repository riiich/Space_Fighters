//
// Created by horic on 11/23/2020.
//

#ifndef SFML_PROJECTS_CS3A_MUSICBACKGROUND_H
#define SFML_PROJECTS_CS3A_MUSICBACKGROUND_H
#include "SFML/Audio.hpp"
#include <iostream>

namespace MusicBackgroundNamespace
{
    class MusicBackground {
    public:
        MusicBackground();
        MusicBackground(std::string musicFile, float vol);
        void playMusic();   //play the music
        bool statusOfGame();    //keeps looping as long as the
        void stopMusic();    //set to true or false depending on whether the game is over or not

    private:
        sf::Music spaceMusic;
        bool status;
    };
}



#endif //SFML_PROJECTS_CS3A_MUSICBACKGROUND_H
