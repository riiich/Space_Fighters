//
// Created by Rich on 6/5/2020.
//

#ifndef SFML_PROJECTS_CS3A_SPACEGAME_H
#define SFML_PROJECTS_CS3A_SPACEGAME_H
#include "Player.h"
#include "Enemy.h"
#include "Meteor.h"
#include "asteroidRocks.h"
#include "../Game/Game.h"
#include <sstream>
#include "Leaderboard.h"
#include "MusicBackground.h"
#include "Sound.h"
#include "SplashState.h"

namespace SpaceGameNamespace
{
class SpaceGame :public Game
    {
    enum musicTypes{intro = 0, mainMusic};

    public:
        SpaceGame();
        ~SpaceGame();
        void playerInput(); //player is able to control player movement
        void enemyUpdate(const sf::RenderWindow& window); //enemy is able to spawn and move downwards
        void battleUpdate();    //updates the combat between the player and the enemies
        void ammoUpdate();
        void interfaceUpdate();
        void scoreUpdate();
        void pauseGame();
        void getScore();
        void checkBoundaries(const sf::RenderWindow& window); //keep the player inside the window
        void update(const sf::RenderWindow& window);  //updates the events of the game
        void Draw(sf::RenderTarget& window) const;    //draws the sprites on the screen
        void drawInterface(sf::RenderTarget& window) const;    //draw the text onto the screen

        void Setdt(const float& dt);
        float Getdt() const;

        void setTime(const float& timer);

        /////////DAVESTATION/////////////
        void start(sf::RenderWindow& window);
        void addEvents(sf::RenderWindow &window);
        void addEvents(const sf::RenderWindow &window, sf::Event& event);
        void draw(sf::RenderTarget &window, sf::RenderStates states) const;
        void exit();
        ////////////////////////////////


    private:
        //PLAYER STUFF
        PlayerNamespace::Player* player;
        sf::Texture playerText;
        void initPlayer(sf::RenderWindow& window);  //initializes a new player

        //bullets are in the first few of the vector, the enemies are after the bullet textures
        std::vector<sf::Texture*> textures;    //vector that holds textures (bullets, enemies,...)


        //ENEMY STUFF
        void initEnemy();   //initializes the enemies
        float enemySpawnTime;   //controls the amount of enemies spawning
        float enemySpawnTimeMax;
        std::vector<EnemyNamespace::Enemy*> enemies;    //vector that holds the enemies
        std::vector<MeteorNamespace::Meteor*> meteors;    //vector that holds enemies of different shapes
        std::vector<asteroidRocksNameSpace::asteroidRocks*> realAsteroids;

        //AMMO STUFF
        void initAmmo();    //initializes the bullets
        std::vector<AmmoNamespace::Ammo*> bullets;      //vector that holds the ammo for the player
        sf::Texture* ammoText;
        sf::Texture* type1BulletText;
        sf::Texture* type2BulletText;
        sf::Texture gunText;
        void initGun();

        //UI STUFF
        void initInterface(sf::RenderWindow& window); //initializes the text for the point counter
        void initSpace();   //initializes the space background
        void initPoints();  //initializes the points for the player
        void initLogo(sf::RenderWindow& window);
        void initButtons(); //SEE WHAT THIS DOES
        std::vector<StatsTextNameSpace::StatsText> stats;
        sf::Font statsFont;
        sf::Font font;
        sf::Text enemyHPText;
        sf::Text pointCountText;
        sf::Text highPointCountText;
        sf::Text health;    //indicating this is the health bar
        sf::Text healthText;
        sf::Text expText;
        sf::Text exp;   //indicating this is the exp bar
        sf::Text lvlText;
        sf::Text pauseText;
        sf::Texture spaceText;
        sf::Sprite spaceSprite;
        sf::Texture GameOverText;
        sf::Sprite GameOverSprite;
        int currPoint;
        int highestPoint;
        sf::RectangleShape currHealthBar;   //moves to indicate losing health
        sf::RectangleShape maxHealthBar;    //stays full size for health
        sf::RectangleShape currExpBar;  //moves to indicate player is gaining exp
        sf::RectangleShape maxExpBar;   //stays full size for exp
        sf::Texture gameLogoText;
        sf::Sprite gameLogoSprite;
        sf::Text splashScreenText;

        bool pause = false; //pause the game
        bool status = false;    //check status for the splash screen
        SplashStateNameSpace::SplashState splash;

        //leaderboard of scores
        LeaderboardNamespace::Leaderboard scoreboard;

        //music (intro, background)
        std::vector<MusicBackgroundNamespace::MusicBackground*> music;   //vector that holds different music
        void initMusicBackground(); //background space game music
        int typeMusic;

        //sound effects (shooting, leveling up,...)
        sf::SoundBuffer soundBuffShoot;
        SoundNameSpace::Sound soundShoot;
        sf::SoundBuffer soundBuffLvl;
        SoundNameSpace::Sound soundLvl;
        sf::SoundBuffer soundBuffOver;
        SoundNameSpace::Sound soundOver;
        void initSoundEffects();

        float gameTime;
        sf::Text gameTimeText;

        //kill count (enemies, asteroids, meteors)
        sf::RectangleShape killCountBackground;
        int enemiesKillCount;
        int meteorKillCount;
        int asteroidKillCount;
        sf::Text enemiesKilledText;
        sf::Text meteorsKilledText;
        sf::Text asteroidsKilledText;

        //control the jitter of the frames
        float dt;
        float dtMultiplier;
    };
}

#endif //SFML_PROJECTS_CS3A_SPACEGAME_H