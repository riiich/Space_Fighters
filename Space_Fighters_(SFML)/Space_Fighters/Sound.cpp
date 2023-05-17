//
// Created by horic on 12/9/2020.
//

#include "Sound.h"
#include <iostream>

namespace SoundNameSpace
{
    Sound::Sound()
    {}

    Sound::Sound(std::string soundFile, float vol)
    {
        this->soundBuff.loadFromFile(soundFile);
        this->sound.setBuffer(soundBuff);
        this->sound.setVolume(vol);
    }

    void Sound::openSound(sf::SoundBuffer soundBuff, float vol)
    {
        this->soundBuff = soundBuff;
        this->sound.setBuffer(this->soundBuff);
        this->sound.setVolume(vol);
    }

    bool Sound::getStatus() const
    {
        return this->status;
    }

    void Sound::setStatus(const bool& status)
    {
        this->status = status;
    }

    void Sound::play()
    {
        this->sound.play();
    }
}