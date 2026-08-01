//
// Created by horic on 12/10/2020.
//

#ifndef SFML_PROJECTS_CS3A_SPLASHSTATE_H
#define SFML_PROJECTS_CS3A_SPLASHSTATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace SplashStateNameSpace
{
    class SplashState
    {
    public:
        enum class Action
        {
            None,
            StartGame,
            ExitGame
        };

        SplashState();
        void initSplashState();
        Action inputHandling(const sf::RenderWindow& window, const sf::Event& event);
        void update();
        void draw( sf::RenderTarget& window) const;
        int getVolume() const;
        const std::string& getUsername() const;

    private:
        enum class Screen
        {
            Main,
            Leaderboard,
            Settings,
            Username
        };

        void initText();
        void refreshLeaderboard();
        void updateSelection(int direction);
        void activateSelected();
        void adjustVolume(int direction);
        void updateMenuVisuals();
        void updateVolumeVisuals();
        void playSelectionSound();
        void loadUsername();
        void beginUsernameEdit(bool firstTime);
        void saveUsername();
        void updateUsernameVisuals();
        void drawMainMenu(sf::RenderTarget& window) const;
        void drawLeaderboard(sf::RenderTarget& window) const;
        void drawSettings(sf::RenderTarget& window) const;
        void drawUsername(sf::RenderTarget& window) const;
        int hoveredMainButton(const sf::Vector2f& mousePos) const;
        static const int MAIN_BUTTON_COUNT = 4;

        sf::Texture titleTexture;
        sf::Sprite titleSprite;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Texture enterTexture;
        sf::Sprite enterSprite;
        sf::Font splashFont;
        sf::Font titleFont;
        std::string selectionSoundPath;
        sf::Text splashText;
        sf::Text subtitleText;
        sf::Text screenTitleText;
        sf::Text volumeText;
        sf::RectangleShape dimOverlay;
        sf::RectangleShape menuButtons[MAIN_BUTTON_COUNT];
        sf::Text menuText[MAIN_BUTTON_COUNT];
        sf::RectangleShape backButton;
        sf::Text backText;
        sf::RectangleShape volumeTrack;
        sf::RectangleShape volumeFill;
        sf::Text leaderboardText[5];
        sf::RectangleShape usernameButton;
        sf::Text usernameButtonText;
        sf::RectangleShape usernameInputBox;
        sf::Text usernameLabelText;
        sf::Text usernameInputText;
        sf::Text usernameHelpText;
        sf::Text usernameErrorText;
        std::string username;
        std::string usernameDraft;
        std::string profilePath;
        bool firstUsernameSetup;
        Screen screen;
        int selectedIndex;
        int volume;
        Action pendingAction;
    };
}

#endif //SFML_PROJECTS_CS3A_SPLASHSTATE_H
