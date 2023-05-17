//
// Created by horic on 12/9/2020.
//

#ifndef SFML_PROJECTS_CS3A_SOUND_H
#define SFML_PROJECTS_CS3A_SOUND_H
#include <SFML/Audio.hpp>

namespace SoundNameSpace
{
    class Sound
    {
    public:
        Sound();
        Sound(std::string soundFile, float vol);
        void openSound(sf::SoundBuffer soundBuff, float vol);
        bool getStatus() const;
        void setStatus(const bool& status);
        void play();

    private:
        sf::SoundBuffer soundBuff;
        sf::Sound sound;
        bool status;
    };
}

#endif //SFML_PROJECTS_CS3A_SOUND_H
