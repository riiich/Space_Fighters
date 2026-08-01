//
// Plays short menu sounds that SFML 2.5 may not decode through sf::SoundBuffer.
//

#ifndef SFML_PROJECTS_CS3A_MENUSOUND_H
#define SFML_PROJECTS_CS3A_MENUSOUND_H

#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <mmsystem.h>
#endif

namespace MenuSound
{
#ifdef _WIN32
    inline std::string normalizePath(const std::string& soundPath)
    {
        std::string normalizedPath = soundPath;
        for(char& ch : normalizedPath)
        {
            if(ch == '/')
                ch = '\\';
        }

        return normalizedPath;
    }

    inline int clampVolume(int volumePercent)
    {
        if(volumePercent < 0)
            return 0;
        else if(volumePercent > 100)
            return 100;

        return volumePercent;
    }

    inline const std::string& alias()
    {
        static const std::string menuAlias = "menu_select";
        return menuAlias;
    }

    inline std::string& openedPath()
    {
        static std::string currentPath;
        return currentPath;
    }
#endif

    inline bool preload(const std::string& soundPath, int volumePercent)
    {
#ifdef _WIN32
        if(soundPath.empty())
            return false;

        const std::string normalizedPath = normalizePath(soundPath);
        if(openedPath() != normalizedPath)
        {
            mciSendStringA(("close " + alias()).c_str(), nullptr, 0, nullptr);
            std::string openCommand = "open \"" + normalizedPath + "\" type mpegvideo alias " + alias();
            if(mciSendStringA(openCommand.c_str(), nullptr, 0, nullptr) != 0)
                return false;

            openedPath() = normalizedPath;
        }

        volumePercent = clampVolume(volumePercent);
        mciSendStringA(("setaudio " + alias() + " volume to " + std::to_string(volumePercent * 10)).c_str(),
                       nullptr, 0, nullptr);

        return true;
#else
        return false;
#endif
    }

    inline void play(const std::string& soundPath, int volumePercent)
    {
#ifdef _WIN32
        if(!preload(soundPath, volumePercent))
            return;

        mciSendStringA(("stop " + alias()).c_str(), nullptr, 0, nullptr);
        mciSendStringA(("seek " + alias() + " to start").c_str(), nullptr, 0, nullptr);
        mciSendStringA(("play " + alias()).c_str(), nullptr, 0, nullptr);
#endif
    }
}

#endif //SFML_PROJECTS_CS3A_MENUSOUND_H
