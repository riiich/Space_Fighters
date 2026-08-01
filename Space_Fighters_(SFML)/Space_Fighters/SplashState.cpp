//
// Created by horic on 12/10/2020.
//

#include "SplashState.h"
#include "Leaderboard.h"
#include "MenuSound.h"
#include "ResourcePath.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <sstream>

namespace SplashStateNameSpace
{
    SplashState::SplashState()
        : firstUsernameSetup(false), screen(Screen::Main), selectedIndex(0), volume(100), pendingAction(Action::None)
    {}

    void SplashState::initSplashState()
    {
        if(!this->titleTexture.loadFromFile(ResourcePath::resolve("Sprites/spaceFightersTitle.png")))
            std::cout << "ERROR: SPACE FIGHTERS TITLE IMAGE FILE IS NOT FOUND!\n";
        this->titleSprite.setTexture(this->titleTexture);
        this->titleSprite.setScale(sf::Vector2f{1.15f, .55f});
        this->titleSprite.setPosition(465.f, 120.f);

        if(!this->backgroundTexture.loadFromFile(ResourcePath::resolve("Sprites/splashScreenBG.jpg")))
            std::cout << "ERROR: Splash background image file is not found!\n";
        this->backgroundSprite.setTexture(this->backgroundTexture);

        this->enterTexture.loadFromFile(ResourcePath::resolve("Sprites/Enter.png"));
        this->enterSprite.setTexture(this->enterTexture);
        this->enterSprite.setScale(0.f, 0.f);

        if(!this->splashFont.loadFromFile(ResourcePath::resolve("Fonts/Laser.ttf")))
            std::cout << "ERROR: Laser font file is not found!\n";
        if(!this->titleFont.loadFromFile(ResourcePath::resolve("Fonts/Arcade.ttf")))
            std::cout << "ERROR: Arcade font file is not found!\n";

        this->selectionSoundPath = ResourcePath::resolve("bulletSounds/pepSound1.mp3");
        MenuSound::preload(this->selectionSoundPath, this->volume);

        this->dimOverlay.setSize(sf::Vector2f(1920.f, 1080.f));
        this->dimOverlay.setFillColor(sf::Color(4, 8, 20, 165));

        this->initText();
        this->loadUsername();
        this->refreshLeaderboard();
        this->updateMenuVisuals();
        this->updateVolumeVisuals();
    }

    void SplashState::initText()
    {
        this->subtitleText.setFont(this->splashFont);
        this->subtitleText.setString("Choose your mission");
        this->subtitleText.setCharacterSize(34);
        this->subtitleText.setFillColor(sf::Color(105, 245, 220, 255));
        this->subtitleText.setPosition(725.f, 330.f);

        const std::string labels[MAIN_BUTTON_COUNT] = {"START GAME", "LEADERBOARD", "SETTINGS", "EXIT"};
        for(int i = 0; i < MAIN_BUTTON_COUNT; ++i)
        {
            this->menuButtons[i].setSize(sf::Vector2f(430.f, 78.f));
            this->menuButtons[i].setPosition(745.f, 405.f + static_cast<float>(i) * 98.f);
            this->menuButtons[i].setOutlineThickness(3.f);

            this->menuText[i].setFont(this->titleFont);
            this->menuText[i].setString(labels[i]);
            this->menuText[i].setCharacterSize(25);
            this->menuText[i].setFillColor(sf::Color::White);
            sf::FloatRect bounds = this->menuText[i].getLocalBounds();
            this->menuText[i].setPosition(
                this->menuButtons[i].getPosition().x + this->menuButtons[i].getSize().x / 2.f - bounds.width / 2.f,
                this->menuButtons[i].getPosition().y + 25.f
            );
        }

        this->screenTitleText.setFont(this->titleFont);
        this->screenTitleText.setCharacterSize(34);
        this->screenTitleText.setFillColor(sf::Color(255, 234, 120, 255));

        this->backButton.setSize(sf::Vector2f(260.f, 64.f));
        this->backButton.setPosition(830.f, 820.f);
        this->backButton.setOutlineThickness(3.f);
        this->backText.setFont(this->titleFont);
        this->backText.setString("BACK");
        this->backText.setCharacterSize(22);
        this->backText.setFillColor(sf::Color::White);
        this->backText.setPosition(920.f, 840.f);

        this->volumeText.setFont(this->titleFont);
        this->volumeText.setCharacterSize(28);
        this->volumeText.setFillColor(sf::Color::White);

        this->volumeTrack.setSize(sf::Vector2f(620.f, 28.f));
        this->volumeTrack.setPosition(650.f, 585.f);
        this->volumeTrack.setFillColor(sf::Color(45, 54, 82, 230));
        this->volumeTrack.setOutlineColor(sf::Color(110, 210, 230, 255));
        this->volumeTrack.setOutlineThickness(2.f);

        this->volumeFill.setPosition(this->volumeTrack.getPosition());
        this->volumeFill.setFillColor(sf::Color(105, 245, 220, 255));

        this->usernameButton.setSize(sf::Vector2f(430.f, 64.f));
        this->usernameButton.setPosition(745.f, 675.f);
        this->usernameButton.setFillColor(sf::Color(12, 22, 48, 225));
        this->usernameButton.setOutlineColor(sf::Color(105, 245, 220, 255));
        this->usernameButton.setOutlineThickness(3.f);
        this->usernameButtonText.setFont(this->titleFont);
        this->usernameButtonText.setString("CHANGE USERNAME");
        this->usernameButtonText.setCharacterSize(21);
        this->usernameButtonText.setFillColor(sf::Color::White);
        this->usernameButtonText.setPosition(825.f, 695.f);

        this->usernameInputBox.setSize(sf::Vector2f(620.f, 82.f));
        this->usernameInputBox.setPosition(650.f, 520.f);
        this->usernameInputBox.setFillColor(sf::Color(12, 22, 48, 235));
        this->usernameInputBox.setOutlineColor(sf::Color(105, 245, 220, 255));
        this->usernameInputBox.setOutlineThickness(3.f);

        this->usernameLabelText.setFont(this->titleFont);
        this->usernameLabelText.setCharacterSize(24);
        this->usernameLabelText.setFillColor(sf::Color(255, 234, 120, 255));

        this->usernameInputText.setFont(this->titleFont);
        this->usernameInputText.setCharacterSize(31);
        this->usernameInputText.setFillColor(sf::Color::White);

        this->usernameHelpText.setFont(this->splashFont);
        this->usernameHelpText.setCharacterSize(25);
        this->usernameHelpText.setFillColor(sf::Color(170, 210, 225, 255));
        this->usernameHelpText.setString("12 characters max - letters, numbers, _ or -\nPress ENTER to save");
        this->usernameHelpText.setPosition(695.f, 635.f);

        this->usernameErrorText.setFont(this->splashFont);
        this->usernameErrorText.setCharacterSize(24);
        this->usernameErrorText.setFillColor(sf::Color(255, 115, 115, 255));
        this->usernameErrorText.setPosition(745.f, 735.f);

        for(int i = 0; i < 5; ++i)
        {
            this->leaderboardText[i].setFont(this->titleFont);
            this->leaderboardText[i].setCharacterSize(27);
            this->leaderboardText[i].setFillColor(sf::Color::White);
            this->leaderboardText[i].setPosition(780.f, 430.f + static_cast<float>(i) * 58.f);
        }
    }

    SplashState::Action SplashState::inputHandling(const sf::RenderWindow& window, const sf::Event& event)
    {
        this->pendingAction = Action::None;

        if(event.type == sf::Event::KeyPressed)
        {
            if(this->screen == Screen::Main)
            {
                if(event.key.code == sf::Keyboard::Up)
                    this->updateSelection(-1);
                else if(event.key.code == sf::Keyboard::Down)
                    this->updateSelection(1);
                else if(event.key.code == sf::Keyboard::Enter)
                    this->activateSelected();
            }
            else if(this->screen == Screen::Leaderboard)
            {
                if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::BackSpace)
                    this->screen = Screen::Main;
            }
            else if(this->screen == Screen::Settings)
            {
                if(event.key.code == sf::Keyboard::Left)
                    this->adjustVolume(-5);
                else if(event.key.code == sf::Keyboard::Right)
                    this->adjustVolume(5);
                else if(event.key.code == sf::Keyboard::U)
                    this->beginUsernameEdit(false);
                else if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::BackSpace)
                    this->screen = Screen::Main;
            }
            else if(this->screen == Screen::Username && event.key.code == sf::Keyboard::Enter)
            {
                this->saveUsername();
            }
        }
        else if(event.type == sf::Event::TextEntered && this->screen == Screen::Username)
        {
            if(event.text.unicode == 8)
            {
                if(!this->usernameDraft.empty())
                    this->usernameDraft.pop_back();
            }
            else if(event.text.unicode < 128 && this->usernameDraft.size() < 12)
            {
                const char typed = static_cast<char>(event.text.unicode);
                if(std::isalnum(static_cast<unsigned char>(typed)) || typed == '_' || typed == '-')
                    this->usernameDraft += typed;
            }
            this->usernameErrorText.setString("");
            this->updateUsernameVisuals();
        }
        else if(event.type == sf::Event::MouseMoved && this->screen == Screen::Main)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            int hovered = this->hoveredMainButton(mousePos);
            if(hovered >= 0 && hovered != this->selectedIndex)
            {
                this->selectedIndex = hovered;
                this->updateMenuVisuals();
                this->playSelectionSound();
            }
        }
        else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if(this->screen == Screen::Main)
            {
                int clicked = this->hoveredMainButton(mousePos);
                if(clicked >= 0)
                {
                    this->selectedIndex = clicked;
                    this->activateSelected();
                }
            }
            else if(this->backButton.getGlobalBounds().contains(mousePos))
            {
                this->screen = Screen::Main;
            }
            else if(this->screen == Screen::Settings && this->usernameButton.getGlobalBounds().contains(mousePos))
            {
                this->beginUsernameEdit(false);
            }
            else if(this->screen == Screen::Settings && this->volumeTrack.getGlobalBounds().contains(mousePos))
            {
                float relativeX = mousePos.x - this->volumeTrack.getPosition().x;
                this->volume = static_cast<int>((relativeX / this->volumeTrack.getSize().x) * 100.f);
                this->adjustVolume(0);
            }
        }

        return this->pendingAction;
    }

    void SplashState::update()
    {}

    void SplashState::updateSelection(int direction)
    {
        this->selectedIndex += direction;
        if(this->selectedIndex < 0)
            this->selectedIndex = MAIN_BUTTON_COUNT - 1;
        else if(this->selectedIndex >= MAIN_BUTTON_COUNT)
            this->selectedIndex = 0;

        this->updateMenuVisuals();
        this->playSelectionSound();
    }

    void SplashState::activateSelected()
    {
        if(this->selectedIndex == 0)
            this->pendingAction = Action::StartGame;
        else if(this->selectedIndex == 1)
        {
            this->refreshLeaderboard();
            this->screen = Screen::Leaderboard;
        }
        else if(this->selectedIndex == 2)
            this->screen = Screen::Settings;
        else if(this->selectedIndex == 3)
            this->pendingAction = Action::ExitGame;
    }

    void SplashState::adjustVolume(int direction)
    {
        this->volume += direction;
        if(this->volume < 0)
            this->volume = 0;
        else if(this->volume > 100)
            this->volume = 100;

        this->updateVolumeVisuals();
    }

    void SplashState::updateMenuVisuals()
    {
        for(int i = 0; i < MAIN_BUTTON_COUNT; ++i)
        {
            if(i == this->selectedIndex)
            {
                this->menuButtons[i].setFillColor(sf::Color(24, 96, 124, 225));
                this->menuButtons[i].setOutlineColor(sf::Color(105, 245, 220, 255));
                this->menuText[i].setFillColor(sf::Color(255, 255, 210, 255));
            }
            else
            {
                this->menuButtons[i].setFillColor(sf::Color(12, 22, 48, 205));
                this->menuButtons[i].setOutlineColor(sf::Color(82, 109, 145, 255));
                this->menuText[i].setFillColor(sf::Color::White);
            }
        }

        this->backButton.setFillColor(sf::Color(12, 22, 48, 225));
        this->backButton.setOutlineColor(sf::Color(105, 245, 220, 255));
    }

    void SplashState::updateVolumeVisuals()
    {
        std::stringstream volumeStream;
        volumeStream << "VOLUME  " << this->volume << "%";
        this->volumeText.setString(volumeStream.str());
        sf::FloatRect bounds = this->volumeText.getLocalBounds();
        this->volumeText.setPosition(960.f - bounds.width / 2.f, 500.f);

        this->volumeFill.setSize(sf::Vector2f(this->volumeTrack.getSize().x * (this->volume / 100.f),
                                              this->volumeTrack.getSize().y));
    }

    void SplashState::playSelectionSound()
    {
        MenuSound::play(this->selectionSoundPath, this->volume);
    }

    void SplashState::refreshLeaderboard()
    {
        std::ifstream scoreFile(ResourcePath::resolve("highScoreTracker.txt"));
        std::vector<LeaderboardNamespace::LeaderboardEntry> entries =
            LeaderboardNamespace::Leaderboard::loadEntries(scoreFile);
        std::sort(entries.begin(), entries.end(),
            [](const LeaderboardNamespace::LeaderboardEntry& left,
               const LeaderboardNamespace::LeaderboardEntry& right)
            {
                return left.score > right.score;
            });

        for(int i = 0; i < 5; ++i)
        {
            std::stringstream row;
            row << (i + 1) << ".  ";
            if(i < static_cast<int>(entries.size()))
                row << entries[i].username << "  " << entries[i].score;
            else
                row << "---";
            this->leaderboardText[i].setString(row.str());
        }
    }

    int SplashState::hoveredMainButton(const sf::Vector2f& mousePos) const
    {
        for(int i = 0; i < MAIN_BUTTON_COUNT; ++i)
        {
            if(this->menuButtons[i].getGlobalBounds().contains(mousePos))
                return i;
        }

        return -1;
    }

    int SplashState::getVolume() const
    {
        return this->volume;
    }

    const std::string& SplashState::getUsername() const
    {
        return this->username;
    }

    void SplashState::draw(sf::RenderTarget& window) const
    {
        window.draw(this->backgroundSprite);
        window.draw(this->dimOverlay);
        window.draw(this->titleSprite);

        if(this->screen == Screen::Main)
            this->drawMainMenu(window);
        else if(this->screen == Screen::Leaderboard)
            this->drawLeaderboard(window);
        else if(this->screen == Screen::Settings)
            this->drawSettings(window);
        else
            this->drawUsername(window);
    }

    void SplashState::drawMainMenu(sf::RenderTarget& window) const
    {
        window.draw(this->subtitleText);
        for(int i = 0; i < MAIN_BUTTON_COUNT; ++i)
        {
            window.draw(this->menuButtons[i]);
            window.draw(this->menuText[i]);
        }
    }

    void SplashState::drawLeaderboard(sf::RenderTarget& window) const
    {
        sf::Text title = this->screenTitleText;
        title.setString("LEADERBOARD");
        sf::FloatRect bounds = title.getLocalBounds();
        title.setPosition(960.f - bounds.width / 2.f, 350.f);
        window.draw(title);

        for(int i = 0; i < 5; ++i)
        {
            window.draw(this->leaderboardText[i]);
        }
        window.draw(this->backButton);
        window.draw(this->backText);
    }

    void SplashState::drawSettings(sf::RenderTarget& window) const
    {
        sf::Text title = this->screenTitleText;
        title.setString("SETTINGS");
        sf::FloatRect bounds = title.getLocalBounds();
        title.setPosition(960.f - bounds.width / 2.f, 350.f);
        window.draw(title);

        window.draw(this->volumeText);
        window.draw(this->volumeTrack);
        window.draw(this->volumeFill);
        sf::Text currentUser = this->usernameLabelText;
        currentUser.setString("PILOT: " + this->username);
        sf::FloatRect userBounds = currentUser.getLocalBounds();
        currentUser.setPosition(960.f - userBounds.width / 2.f, 635.f);
        window.draw(currentUser);
        window.draw(this->usernameButton);
        window.draw(this->usernameButtonText);
        window.draw(this->backButton);
        window.draw(this->backText);
    }

    void SplashState::loadUsername()
    {
        const std::string scorePath = ResourcePath::resolve("highScoreTracker.txt");
        const std::size_t separator = scorePath.find_last_of("/\\");
        this->profilePath = separator == std::string::npos
            ? "playerProfile.txt"
            : scorePath.substr(0, separator + 1) + "playerProfile.txt";

        std::ifstream profileFile(this->profilePath);
        std::getline(profileFile, this->username);
        if(this->username.empty())
            this->beginUsernameEdit(true);
    }

    void SplashState::beginUsernameEdit(bool firstTime)
    {
        this->firstUsernameSetup = firstTime;
        this->usernameDraft = firstTime ? "" : this->username;
        this->usernameErrorText.setString("");
        this->screen = Screen::Username;
        this->updateUsernameVisuals();
    }

    void SplashState::saveUsername()
    {
        if(this->usernameDraft.empty())
        {
            this->usernameErrorText.setString("Username cannot be empty");
            return;
        }

        std::ofstream profileFile(this->profilePath, std::ios::trunc);
        if(!profileFile)
        {
            this->usernameErrorText.setString("Could not save username");
            return;
        }

        profileFile << this->usernameDraft << '\n';
        this->username = this->usernameDraft;
        this->screen = this->firstUsernameSetup ? Screen::Main : Screen::Settings;
        this->firstUsernameSetup = false;
    }

    void SplashState::updateUsernameVisuals()
    {
        this->usernameLabelText.setString(this->firstUsernameSetup ? "CREATE YOUR PILOT NAME" : "CHANGE PILOT NAME");
        sf::FloatRect labelBounds = this->usernameLabelText.getLocalBounds();
        this->usernameLabelText.setPosition(960.f - labelBounds.width / 2.f, 450.f);

        this->usernameInputText.setString(this->usernameDraft + "_");
        sf::FloatRect inputBounds = this->usernameInputText.getLocalBounds();
        this->usernameInputText.setPosition(960.f - inputBounds.width / 2.f, 542.f);
    }

    void SplashState::drawUsername(sf::RenderTarget& window) const
    {
        window.draw(this->usernameLabelText);
        window.draw(this->usernameInputBox);
        window.draw(this->usernameInputText);
        window.draw(this->usernameHelpText);
        window.draw(this->usernameErrorText);
    }
}
