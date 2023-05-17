//
// Created by horic on 11/23/2020.
//

#include "MusicBackground.h"

namespace MusicBackgroundNamespace
{
    MusicBackground::MusicBackground()
    {}

    MusicBackground::MusicBackground(std::string musicFile, float vol)
    {
        if(!spaceMusic.openFromFile(musicFile))
        {
            std::cout << "ERROR: Music file is not found!\n";
        }

        this->status = true;   //true if the game is not over yet
        spaceMusic.setVolume(vol);
        spaceMusic.setLoop(this->status);   //loops in the beginning until the game is over
    }

    void MusicBackground::playMusic()
    {
        this->spaceMusic.play();
    }

    bool MusicBackground::statusOfGame()
    {
        return this->status;
    }

    void MusicBackground::stopMusic()
    {
        this->spaceMusic.stop();
    }
}