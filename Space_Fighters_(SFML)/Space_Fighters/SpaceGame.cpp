//
// Created by Rich on 6/5/2020.
//

#include "SpaceGame.h"

namespace SpaceGameNamespace
{
    void SpaceGame::start(sf::RenderWindow& window)
    {
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
//            this->status = true;
        //these functions initialize all the interface and variables in the game
        this->initMusicBackground();
        this->initSoundEffects();
        this->initPoints();
        this->initSpace();
        this->initInterface(window);
        this->initAmmo();
        this->initEnemy();
        this->initGun();
        this->initPlayer(window);
        this->pauseGame();
        this->getScore();
        this->scoreUpdate();
    }

    void SpaceGame::addEvents(sf::RenderWindow& window)
    {
        if(!pause)  //continues the game as long as the game is not paused
        {
            if(this->player->getHealth() > 0)
            {
                this->update(window);
            }
        }
        if(!status)
        {
            this->splash.draw(window);
        }
    }

    void SpaceGame::addEvents(const sf::RenderWindow &window, sf::Event& event)
    {
        //pause the game by pressing enter
        if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter))
        {
            if(this->pause)
            {
                this->pause = false;
                this->music[mainMusic]->playMusic();
            }
            else
            {
                this->pause = true;
                this->music[mainMusic]->stopMusic();
            }
            if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter))
            {
                this->status = false;
            }
            else
            {
                this->status = true;
            }
        }
    }

    void SpaceGame::draw(sf::RenderTarget &window, sf::RenderStates states) const
    {
        if(pause)
            splash.draw(window);
        else
        {
            Draw(window);
        }
    }

    void SpaceGame::exit()
    {

    }

    //constructor
    SpaceGame::SpaceGame()
    {
        splash.initSplashState();
        image_path = "..\\Space_Fighters/Sprites/game_logo.png";
        title = "Space Fighters";
        this->dtMultiplier = 62.5f;
    }

    void SpaceGame::Setdt(const float& dt)
    {
        this->dt = dt;
    }

    float SpaceGame::Getdt() const
    {
        return this->dt;
    }

    void SpaceGame::setTime(const float& timer)
    {
        this->gameTime = timer;
    }

    //destructor
    SpaceGame::~SpaceGame()
    {
        //delete this->window;
        delete this->player;    //delete player

        for(sf::Texture* text : this->textures)
        {
            delete text;
        }

        //delete the bullets
        for(AmmoNamespace::Ammo* ammo : this->bullets)
        {
            delete ammo;
        }

        //delete the enemy ships
        for(EnemyNamespace::Enemy* enemy : this->enemies)
        {
            delete enemy;
        }

        //delete the enemy shapes
        for(MeteorNamespace::Meteor* meteor : this->meteors)
        {
            delete meteor;
        }

        //delete the actual asteroids
        for(asteroidRocksNameSpace::asteroidRocks* asteroidRocks : this->realAsteroids)
        {
            delete asteroidRocks;
        }

        //delete the music
        for(MusicBackgroundNamespace::MusicBackground* music: this->music)
        {
            delete music;
        }

        std::cout << "DESTRUCTOR\n";
    }

    void SpaceGame::initPlayer(sf::RenderWindow& window)
    {
        //loading the image into a texture
        if(!this->playerText.loadFromFile("..\\Space_Fighters/Sprites/SpaceShip3.png"))
        {
            std::cout << "ERROR: Player spaceship file is not found.\n";
        }

        this->player = new PlayerNamespace::Player(&playerText, &gunText, sf::Vector2f(.1f, .1f));   //creating player dynamically

        this->player->setPosition(sf::Vector2f(window.getSize().x/2 - this->player->getGBounds().width/2.1,
                                               window.getSize().y/2 - this->player->getPlayerPos().y/2 + 150));
    }

    void SpaceGame::initEnemy()
    {
        int enemyIndex = PlayerNamespace::WEAPONS::type2Bullet + 1;
        this->textures.push_back(new sf::Texture());
        this->textures[enemyIndex++]->loadFromFile("..\\Space_Fighters/Sprites/enemyShip1.png");   //enemy texture after the ammo textures

        this->textures.push_back(new sf::Texture());
        this->textures[enemyIndex++]->loadFromFile("..\\Space_Fighters/Sprites/enemyShip2.png");

        this->textures.push_back(new sf::Texture());
        this->textures[enemyIndex++]->loadFromFile("..\\Space_Fighters/Sprites/enemyShip3.png");

        this->enemySpawnTimeMax = 35.f;     //the speed of enemy spawn
        this->enemySpawnTime = this->enemySpawnTimeMax;
        this->enemiesKillCount = 0;
        this->meteorKillCount = 0;
        this->asteroidKillCount = 0;
    }

    void SpaceGame::initAmmo()
    {
        this->textures.push_back(new sf::Texture());
        this->textures[PlayerNamespace::WEAPONS::defaultBullet]->loadFromFile("..\\Space_Fighters/Sprites/green_bullet.png");

        this->textures.push_back(new sf::Texture());
        this->textures[PlayerNamespace::WEAPONS::type1Bullet]->loadFromFile("..\\Space_Fighters/Sprites/blueLaserBeam.png");

        this->textures.push_back(new sf::Texture());
        this->textures[PlayerNamespace::WEAPONS::type2Bullet]->loadFromFile("..\\Space_Fighters/Sprites/fireBullet.png");
    }

    //initializes the font, health, and game over screen
    void SpaceGame::initInterface(sf::RenderWindow& window)
    {
        //ARCADE FONT
        if(!this->font.loadFromFile("..\\Space_Fighters/Fonts/Arcade.ttf"))
            std::cout << "ERROR: Arcade font file is not found!\n";

        if(!this->statsFont.loadFromFile("..\\Space_Fighters/Fonts/Laser.ttf"))
            std::cout << "ERROR: Laser font file is not found!\n";

        //ENEMY HP TEXT
        this->enemyHPText.setFont(this->font);
        this->enemyHPText.setCharacterSize(17);
        this->enemyHPText.setFillColor(sf::Color::Red);

        //load it into a text
        this->pointCountText.setFont(this->font);
        this->pointCountText.setCharacterSize(30);  //set the size of the characters
        this->pointCountText.setFillColor(sf::Color::White);

        this->highPointCountText.setFont(this->font);
        this->highPointCountText.setCharacterSize(30);
        this->highPointCountText.setFillColor(sf::Color(68,227,137,255));
        this->highPointCountText.setPosition(sf::Vector2f(0.f, 30.f));

        //HEALTH BAR INTERFACE
        this->maxHealthBar.setSize(sf::Vector2f(300.f, 30.f));
        this->maxHealthBar.setFillColor(sf::Color(74, 68, 77, 255));
        this->maxHealthBar.setPosition(sf::Vector2f(window.getSize().x/2 - 150.f, window.getSize().y - 40.f));
        this->currHealthBar = this->maxHealthBar;
        this->currHealthBar.setFillColor(sf::Color::Red);

        //HEALTH INDICATOR
        this->healthText.setFont(this->font);
        this->healthText.setCharacterSize(15);
        this->healthText.setFillColor(sf::Color::White);
        this->healthText.setPosition(sf::Vector2f(this->currHealthBar.getPosition().x + 130.f, this->currHealthBar.getPosition().y + 5.f));
        this->health.setFont(this->font);
        this->health.setCharacterSize(15);
        this->health.setFillColor(sf::Color::White);
        this->health.setPosition(sf::Vector2f(this->healthText.getPosition().x + 10.f, this->healthText.getPosition().y - 25.f));

        //EXP BAR INTERFACE
        this->maxExpBar.setSize(sf::Vector2f(300.f, 30.f));
        this->maxExpBar.setFillColor(sf::Color(178, 164, 150, 255));
        this->maxExpBar.setPosition(sf::Vector2f(window.getSize().x/2 + 250.f, window.getSize().y - 40.f));
        this->currExpBar.setSize(sf::Vector2f(this->maxExpBar.getSize().x, 30.f));
        this->currExpBar.setPosition(sf::Vector2f(window.getSize().x/2 + 250.f, window.getSize().y - 40.f));
        this->currExpBar.setFillColor(sf::Color(213, 175, 85));

        //EXP INDICATOR
        this->expText.setFont(this->font);
        this->expText.setCharacterSize(15);
        this->expText.setFillColor(sf::Color::Black);
        this->expText.setPosition(sf::Vector2f(this->currExpBar.getPosition().x + 130.f, this->currExpBar.getPosition().y + 5.f));
        this->exp.setFont(this->font);
        this->exp.setCharacterSize(15);
        this->exp.setFillColor(sf::Color::White);
        this->exp.setPosition(sf::Vector2f(this->expText.getPosition().x, this->expText.getPosition().y - 25.f));

        //LEVEL INDICATOR
        this->lvlText.setFont(this->font);
        this->lvlText.setCharacterSize(15);
        this->expText.setFillColor(sf::Color::White);

        //PAUSE
        this->pauseText.setFont(this->font);
        this->pauseText.setCharacterSize(35);
        this->pauseText.setFillColor(sf::Color::Yellow);
        this->pauseText.setPosition(sf::Vector2f(window.getSize().x - 410, 0.f));

        //TIMER
        this->gameTimeText.setFont(this->statsFont);
        this->gameTimeText.setCharacterSize(25);
        this->gameTimeText.setFillColor(sf::Color::White);
        this->gameTimeText.setPosition(sf::Vector2f(window.getSize().x - 275.f, 35.f));

        //ENEMIES KILLED TEXT
        this->enemiesKilledText.setFont(this->statsFont);
        this->enemiesKilledText.setCharacterSize(20.f);
        this->enemiesKilledText.setFillColor(sf::Color(255,69,0, 255));
        this->enemiesKilledText.setPosition(sf::Vector2f(0.f, 80.f));

        //METEORS KILLED TEXT
        this->meteorsKilledText.setFont(this->statsFont);
        this->meteorsKilledText.setCharacterSize(20.f);
        this->meteorsKilledText.setFillColor(sf::Color(255,69,0, 255));
        this->meteorsKilledText.setPosition(sf::Vector2f(0.f, 110.f));

        //ASTEROIDS KILLED TEXT
        this->asteroidsKilledText.setFont(this->statsFont);
        this->asteroidsKilledText.setCharacterSize(20.f);
        this->asteroidsKilledText.setFillColor(sf::Color(255,69,0, 255));
        this->asteroidsKilledText.setPosition(sf::Vector2f(0.f, 145.f));

        this->killCountBackground.setSize(sf::Vector2f(260.f, 100.f));
        this->killCountBackground.setFillColor(sf::Color(128,128,128,155));
        this->killCountBackground.setPosition(0.f, 75.f);

        this->splashScreenText.setFont(this->statsFont);
        this->splashScreenText.setCharacterSize(15.f);
        this->splashScreenText.scale(1.4f, 1.f);
        this->splashScreenText.setFillColor(sf::Color::Red);
        this->splashScreenText.setPosition(window.getSize().x/3, 5.f);

        //GAME OVER
        if(!this->GameOverText.loadFromFile("..\\Space_Fighters/Sprites/Game_Over.png"))
        {
            std::cout << "ERROR: Game Over file is not found.\n";
        }
        this->GameOverSprite.setTexture(this->GameOverText);
        this->GameOverSprite.setPosition(window.getSize().x/2 - this->GameOverSprite.getGlobalBounds().width/2,
                                         window.getSize().y/2 - this->GameOverSprite.getGlobalBounds().height/2);
    }

    void SpaceGame::initSpace()
    {
        //loading the space image for the background
        if(!this->spaceText.loadFromFile("..\\Space_Fighters/Sprites/spaceBackgroundImage.jpg"))
        {
            std::cout << "ERROR: Space background file is not found.\n";
        }

        //set the texture of the background into a sprite
        this->spaceSprite.setTexture(this->spaceText);
    }

    void SpaceGame::initPoints()
    {
        this->currPoint = 0;   //set the initial points to 0
    }

    void SpaceGame::initGun()
    {
        if(!this->gunText.loadFromFile("..\\Space_Fighters/Sprites/gun.png"))
        {
            std::cout << "ERROR: Gun file is not found!.\n";
        }
    }

    void SpaceGame::initLogo(sf::RenderWindow& window)
    {
        //loading texture for the game logo
        if(!this->gameLogoText.loadFromFile("..\\Space_Fighters/Sprites/spaceFightersTitle.png"))
            std::cout << "ERROR: Game Logo file is not found.\n";

        this->gameLogoSprite.setTexture(this->gameLogoText);
        this->gameLogoSprite.setScale(.83, .3f);

        //set the game logo to the center top of the screen
        this->gameLogoSprite.setPosition(sf::Vector2f(window.getSize().x/2 - this->gameLogoSprite.getGlobalBounds().width/2,
                                                      window.getSize().y/2 - this->gameLogoSprite.getGlobalBounds().width));
    }

    void SpaceGame::initMusicBackground()
    {
        this->music.push_back(new MusicBackgroundNamespace::MusicBackground("..\\Space_Fighters/Music/introMusic.wav", 25.f));
        this->music.push_back(new MusicBackgroundNamespace::MusicBackground("..\\Space_Fighters/Music/gameBackgroundMusic1.ogg", 25.f));
        this->music[mainMusic]->playMusic();    //play music
    }

    void SpaceGame::initSoundEffects()
    {
        this->soundBuffShoot.loadFromFile("..\\Space_Fighters/Sounds/laserShootSound.wav");
        this->soundShoot.openSound(this->soundBuffShoot, 7.f);

        this->soundBuffLvl.loadFromFile("..\\Space_Fighters/Sounds/lvlUp.wav");
        this->soundLvl.openSound(this->soundBuffLvl, 20.f);

        this->soundBuffOver.loadFromFile("..\\Space_Fighters/Sounds/gameOver.wav");
        this->soundOver.openSound(this->soundBuffOver, 25.f);
    }

    //updates player when keys are pressed
    void SpaceGame::playerInput()
    {
        //shooting the ammo out of the player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (this->player->playerAtk()))
        {
            this->soundShoot.play();

            if(this->player->getLvl() >= 2)
                this->player->setPrimaryWeaponLvl(1);
            if(this->player->getLvl() >= 4)
                this->player->setPrimaryWeaponLvl(2);
            if(this->player->getLvl() >= 5)
            {
                this->player->setCurrWeapon(PlayerNamespace::WEAPONS::type1Bullet);
                this->player->setUpgradedBullet1(true);
            }
            if(this->player->getLvl() >= 6)
            {
                this->player->setPrimaryWeaponLvl(PlayerNamespace::WEAPONS::type2Bullet);
                this->player->setUpgradedBullet1(true);

                if(this->enemiesKillCount >=  225)
                    this->player->setUpgradedBullet2(true);
            }

            if (this->player->getCurrWeapon() == PlayerNamespace::WEAPONS::defaultBullet)
            {
                if(this->player->getPrimaryWeaponLvl() == 0)    //one bullet
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 15.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                }
                if(this->player->getPrimaryWeaponLvl() == 1)   //2 bullets
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x + 32.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 63.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                }
                if(this->player->getPrimaryWeaponLvl() == 2)   //3 bullets
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 15.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x + 32.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                    this->bullets.push_back(new AmmoNamespace::Ammo(*this->textures.data(),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 63.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    sf::Vector2f{.25f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                }

                this->player->moveGun();
            }
            else if (this->player->getCurrWeapon() == PlayerNamespace::WEAPONS::type1Bullet)
            {
                this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 1),
                                                                sf::Vector2f(this->player->getPlayerCenter().x + 15.f,
                                                                             this->player->getPlayerCenter().y - 35.f),
                                                                {.2f, .2f}, 20.f,15.f,
                                                                sf::Vector2f(0.f, -1.f), 2.f));

                //shoot 2 bullets if the upgrade for dual missiles is true
                if(this->player->getUpgradedBullet1())
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 1),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 75.f,
                                                                                 this->player->getPlayerCenter().y - 35.f),
                                                                    {.2f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                }
                if(this->player->getUpgradedBullet2())
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 1),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 45.f,
                                                                                 this->player->getPlayerCenter().y - 35.f),
                                                                    {.2f, .2f}, 20.f,15.f,
                                                                    sf::Vector2f(0.f, -1.f), 2.f));
                }
            }
            else if (this->player->getCurrWeapon() == PlayerNamespace::WEAPONS::type2Bullet)
            {
                this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 2),
                                                                sf::Vector2f(this->player->getPlayerCenter().x - 15.f,
                                                                             this->player->getPlayerCenter().y),
                                                                {.25f, .2f}, 20.f, 15.f,
                                                                sf::Vector2f(0.f, -1.f), 1.f));
                if(this->player->getUpgradedBullet1())
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 2),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 75.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    {.25f, .2f}, 20.f, 15.f,
                                                                    sf::Vector2f(0.f, -1.f), 1.f));
                }
                if(this->player->getUpgradedBullet2())
                {
                    this->bullets.push_back(new AmmoNamespace::Ammo(*(this->textures.data() + 2),
                                                                    sf::Vector2f(this->player->getPlayerCenter().x - 130.f,
                                                                                 this->player->getPlayerCenter().y),
                                                                    {.25f, .2f}, 20.f, 15.f,
                                                                    sf::Vector2f(0.f, -1.f), 1.f));
                }
            }
        }
    }

    //updates the enemy and its combat 
    void SpaceGame::enemyUpdate(const sf::RenderWindow& window)
    {
        float randAsteroids = rand() % window.getSize().x;
        float randEnemies = rand() % window.getSize().x;
        float randMeteors = rand() % window.getSize().x;
        //spawn enemies
        if(this->enemySpawnTime < this->enemySpawnTimeMax)
            this->enemySpawnTime += 0.5f * this->dt * this->dtMultiplier;

        if(this->enemySpawnTime >= this->enemySpawnTimeMax)
        {
            //spawn the enemies at random areas
            this->enemies.push_back(new EnemyNamespace::Enemy(*(this->textures.data() + PlayerNamespace::WEAPONS::type2Bullet+1), randEnemies - 100.f,
                                                              window.getPosition().y - 150.f, {.5f, .5f}, this->player->getPlayerPos(), EnemyNamespace::enemyType::normal,
                                                              rand()%5 + 1, 5.f, rand()%2 + 8, 1, 2));

            if(this->player->getLvl() >= 4 && this->enemiesKillCount >= 40) //next phase of enemies come in
            {
                this->enemies.push_back(new EnemyNamespace::Enemy(*(this->textures.data() + PlayerNamespace::WEAPONS::type2Bullet+2), randEnemies - 100.f,
                                                                  window.getPosition().y - 150.f, {.075f, .075f}, this->player->getPlayerPos(), EnemyNamespace::enemyType::follow,
                                                                  rand()%6 + 3, 3.f, rand()%3 + 20, 3, 7));
                this->realAsteroids.push_back(new asteroidRocksNameSpace::asteroidRocks(randAsteroids, -50.f));
            }

            if(this->player->getLvl() >= 7 && this->enemiesKillCount >= 90)    //next phase of enemies come in
            {
                this->enemies.push_back(new EnemyNamespace::Enemy(*(this->textures.data() + PlayerNamespace::WEAPONS::type2Bullet+3), randEnemies - 100.f,
                                                                  window.getPosition().y - 150.f, {.075f, .075f}, this->player->getPlayerPos(), EnemyNamespace::enemyType::shootnFollow,
                                                                  rand()%6 + 5, 7.f, rand()%3 + 30, 7, 14));
            }

            this->meteors.push_back(new MeteorNamespace::Meteor(randMeteors, -50.f));


            this->enemySpawnTime = -.1f;     //reset the spawn time
        }

        unsigned int count = 0;
        for(int i = 0; i < this->enemies.size(); i++)
        {
            this->enemies[i]->update(this->dt, this->player->getPlayerPos());

            for(int j = 0; j < this->enemies[i]->getAmmo().size(); j++)
            {
                this->enemies[i]->getAmmo()[j]->update(dt);
                //checks if the enemy bullet touches the player
                if(this->enemies[i]->getAmmo()[j]->getBounds().intersects(this->player->getGBounds()))
                {
                    int lostHealth = this->enemies.at(count)->getDmg();
                    this->player->loseHealth(lostHealth);
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(lostHealth) + " hp", this->player->getPlayerPos()
                            , 10.f, sf::Color::Red, {-1.f, 0.f}));
                    this->enemies[i]->getAmmo().erase(this->enemies[i]->getAmmo().begin() + j);
                }
            }

            //checking and erasing the enemy as it goes out of the window
            if(this->enemies[i]->getGBounds().top > window.getSize().y)
            {
                int lostHealth = rand() %1 + 1;//this->enemies.at(count)->getDmg();
                this->player->loseHealth(lostHealth);    //player loses health
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(lostHealth) + " hp", this->player->getPlayerPos()
                        , 10.f, sf::Color::Red, {-1.f, 0.f}));

                //erasing the enemy out of the vector
                delete this->enemies.at(count);   //have to delete since the enemy are dynamic
                this->enemies.erase(this->enemies.begin() + count);
            }

                //checks if the enemy touches the player
            else if(this->enemies[i]->getGBounds().intersects(this->player->getGBounds()))
            {
                this->enemiesKillCount++;
                int lostHealth = this->enemies.at(count)->getDmg();
                this->player->loseHealth(lostHealth);
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(lostHealth) + " hp", this->player->getPlayerPos()
                        , 10.f, sf::Color::Red, {-1.f, 0.f}));

                int xp = 2;
                if(this->player->gainExp(xp)) //player gains 1 experience point whenever gets hit/hurt by the enemy
                {
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                            , 25.f, sf::Color(250, 128, 114, 255), {0.f, -1.f}));
                    this->soundLvl.play();  //play leveling sound
                }
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->enemies[i]->getEnemyPos()
                        , 10.f, sf::Color::Yellow, {-1.f, 0.f}));

                delete this->enemies.at(count);
                this->enemies.erase(this->enemies.begin() + count);
            }

            ++count;
        }
        unsigned int diffCount = 0;
        //different shaped enemies
        for(int i = 0; i < this->meteors.size(); i++)
        {
            this->meteors[i]->update(this->dt);

            //checking and erasing the enemy as it goes out of the window
            if(meteors[i]->getGBounds().top > window.getSize().y)
            {
                //erasing the enemy out of the vector
                delete this->meteors.at(diffCount);   //have to delete since the enemy are dynamic
                this->meteors.erase(this->meteors.begin() + diffCount);
            }
                //checks if the enemy touches the player
            else if(meteors[i]->getGBounds().intersects(this->player->getGBounds()))
            {
                this->meteorKillCount++;
                int lostHealth = this->meteors.at(diffCount)->getDmg();
                this->player->loseHealth(lostHealth);    //player loses health every time an asteroid hits player
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(lostHealth) + " hp", this->player->getPlayerPos()
                        , 10.f, sf::Color::Red, {-1.f, 0.f}));

                int xp = 1;
                if(this->player->gainExp(xp))
                {
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                            , 25.f, sf::Color(250, 128, 114, 255), {0.f, -1.f}));
                    this->soundLvl.play();  //play leveling sound
                }
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->meteors[i]->getEnemyPos()
                        , 10.f, sf::Color::Yellow, {-1.f, 0.f}));

                delete this->meteors.at(diffCount);
                this->meteors.erase(this->meteors.begin() + diffCount);
            }

            ++diffCount;
        }

        unsigned int astCount = 0;
        //asteroid rocks
        for(int i = 0; i < this->realAsteroids.size(); i++)
        {
            this->realAsteroids[i]->update(this->dt);

            //checking and erasing the enemy as it goes out of the window
            if(realAsteroids[i]->getGBounds().top > window.getSize().y)
            {
                //erasing the enemy out of the vector
                delete this->realAsteroids.at(astCount);
                this->realAsteroids.erase(this->realAsteroids.begin() + astCount);
            }
                //checks if the enemy touches the player
            else if(realAsteroids[i]->getGBounds().intersects(this->player->getGBounds()))
            {
                this->asteroidKillCount++;
                int health = this->realAsteroids.at(astCount)->getDmg();
                this->player->loseHealth(health);    //player loses health every time an asteroid hits player
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(health) + " hp", this->player[i].getPlayerPos()
                        , 10.f, sf::Color::Red, {-1.f, 0.f}));

                int xp = rand() %1 + 1;
                if(this->player->gainExp(xp))   //random experience points for the asteroid rocks being destroyed
                {
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                            , 25.f, sf::Color(250, 128, 114, 255), {0.f, -1.f}));
                    this->soundLvl.play();  //play leveling sound
                }
                this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->realAsteroids[i]->getEnemyPos()
                        , 10.f, sf::Color::Yellow, {-1.f, 0.f}));

                delete this->realAsteroids.at(astCount);
                this->realAsteroids.erase(this->realAsteroids.begin() + astCount);
            }

            ++astCount;
        }
    }

    void SpaceGame::battleUpdate()
    {
        //enemy ship
        for(unsigned int i = 0; i < this->enemies.size(); ++i)
        {
            bool EnDeleted = false;

            for(unsigned int j = 0; j < this->bullets.size() && !EnDeleted; j++)
            {
                //checks if the enemy and the bullet touches
                if(this->enemies[i]->getGBounds().intersects(this->bullets[j]->getBounds()))
                {
                    this->enemiesKillCount++;
                    if(this->currPoint > this->highestPoint)
                    {
                        this->highestPoint = this->currPoint;
                        this->scoreUpdate();
                    }

                    delete this->bullets[j];
                    this->bullets.erase(this->bullets.begin() + j);

                    if(this->enemies[i]->getHP() > 0)
                    {
                        int dmg = this->player->getDmg();
                        this->enemies[i]->damaged(dmg);
                        this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "-" + std::to_string(dmg) + " hp", {this->enemies[i]->getEnemyPos().x,
                                                                                                                                  this->enemies[i]->getEnemyPos().y - 20.f}, 8.f, sf::Color::Red, {0.f, -1.f}));
                    }
                    if(this->enemies[i]->getHP() <= 0)
                    {
                        //delete the bullet and enemy when they touch
                        int points = this->enemies[i]->getPoint();
                        this->currPoint += points;     //increment the point every time enemy is killed
                        this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(points) + " points", this->enemies[i]->getEnemyPos()
                                , 10.f, sf::Color::Green, {1.f, 0.f}));

                        int xp = rand()%4 + 4;
                        if(this->player->gainExp(xp)) //gain random experience between 4-8
                        {
                            this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                                    , 25.f, sf::Color(250, 128, 114, 255), {0.f, -1.f}));
                            this->soundLvl.play();
                        }
                        this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->enemies[i]->getEnemyPos()
                                , 10.f, sf::Color::Yellow, {-1.f, 0.f}));

                        delete this->enemies[i];
                        this->enemies.erase(this->enemies.begin() + i);
                    }

                    EnDeleted = true;
                }
            }
        }

        //meteors
        for(int i = 0; i < this->meteors.size(); ++i)
        {
            bool astDeleted = false;

            for(unsigned int j = 0; j < this->bullets.size() && !astDeleted; j++)
            {
                //checks if the enemy and the bullet touches
                if(this->meteors[i]->getGBounds().intersects(this->bullets[j]->getBounds()))
                {
                    this->meteorKillCount++;
                    int points = this->meteors[i]->getPoint();
                    this->currPoint += points;
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(points) + " points", this->meteors[i]->getEnemyPos()
                            , 10.f, sf::Color::Green, {1.f, 0.f}));

                    int xp = rand()%1 + 4;
                    if(this->player->gainExp(xp))
                    {
                        this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                                , 25.f, sf::Color(250, 128, 114, 255), {0.f, -1.f}));
                        this->soundLvl.play();  //play leveling sound
                    }
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->meteors[i]->getEnemyPos()
                            , 10.f, sf::Color::Yellow, {-1.f, 0.f}));

                    if(this->currPoint > this->highestPoint)
                    {
                        this->highestPoint = this->currPoint;
                        this->scoreUpdate();
                    }

                    //delete the bullet and enemy when they touch
                    delete this->meteors[i];
                    this->meteors.erase(this->meteors.begin() + i);

                    delete this->bullets[j];
                    this->bullets.erase(this->bullets.begin() + j);

                    astDeleted = true;
                }
            }
        }

        //asteroid rocks
        for(int i = 0; i < this->realAsteroids.size(); ++i)
        {
            bool astRockDeleted = false;

            for(unsigned int j = 0; j < this->bullets.size() && !astRockDeleted; j++)
            {
                //checks if the enemy and the bullet touches
                if(this->realAsteroids[i]->getGBounds().intersects(this->bullets[j]->getBounds()))
                {
                    this->asteroidKillCount++;
                    int points = this->realAsteroids[i]->getPoint();
                    this->currPoint += points;
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(points) + " points", this->realAsteroids[i]->getEnemyPos()
                            , 10.f, sf::Color::Green, {1.f, 0.f}));

                    int xp = rand()%2 + 4;
                    if(this->player->gainExp(xp))
                    {
                        this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "LEVEL UP!", this->player->getPlayerPos()
                                , 25.f, sf::Color(250, 128, 114, 255), {-1.f, 0.f}));
                        this->soundLvl.play();  //play leveling sound
                    }
                    this->stats.push_back(StatsTextNameSpace::StatsText(&this->statsFont, "+" + std::to_string(xp) + " exp", this->realAsteroids[i]->getEnemyPos()
                            , 10.f, sf::Color::Yellow, {0.f, -1.f}));

                    if(this->currPoint > this->highestPoint)
                    {
                        this->highestPoint = this->currPoint;
                        this->scoreUpdate();
                    }

                    //delete the bullet and enemy when they touch
                    delete this->realAsteroids[i];
                    this->realAsteroids.erase(this->realAsteroids.begin() + i);

                    delete this->bullets[j];
                    this->bullets.erase(this->bullets.begin() + j);

                    astRockDeleted = true;
                }
            }
        }
    }

    //NEED TO FIX WHEN SHOOTING DUAL BULLETS
    void SpaceGame::ammoUpdate()
    {
        for (int i = 0; i < this->bullets.size(); i++)
        {
            this->bullets[i]->update(this->dt);
            //checking and erasing the bullets as it goes out of the window
            if(this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 25)
            {
                //erasing the bullet out of the vector
                delete this->bullets.at(i);   //have to delete since the bullets are dynamic
                this->bullets.erase(this->bullets.begin() + i);
            }
        }
    }

    void SpaceGame::interfaceUpdate()
    {
        this->health.setString("HP");

        //HEALTH INDICATOR
        std::stringstream ssHealth;
        ssHealth << this->player->getHealth() << "/" << this->player->getHealthMax();
        this->healthText.setString(ssHealth.str());

        //HEALTH UPDATE
        float healthRatio = static_cast<float>(this->player->getHealth()) / this->player->getHealthMax();
        this->currHealthBar.setSize(sf::Vector2f(300.f*healthRatio, this->currHealthBar.getSize().y));

        //GAME TIMER
        this->gameTimeText.setString("TIME: \n" + std::to_string(this->gameTime) + " s") ;

        //ENEMIES HP TEXT UPDATE
        for(int i = 0; i < this->enemies.size(); i++)
        {
            this->enemyHPText.setString(std::to_string(this->enemies[i]->getHP()) + "/" +
                                        std::to_string(this->enemies[i]->getMaxHP()));
            this->enemyHPText.setPosition(this->enemies[i]->getEnemyPos());
        }

        //the level indicator follows wherever the player goes
        this->lvlText.setString("LEVEL " + std::to_string(this->player->getLvl()));
        this->lvlText.setPosition(this->player->getPlayerPos());

        this->exp.setString("EXP");
        //EXP INDICATOR
        std::stringstream ssExp;
        ssExp << this->player->getExp() << "/" << this->player->getNextExp();
        this->expText.setString(ssExp.str());

        //KILL COUNTS
        this->enemiesKilledText.setString("ENEMIES KILLED: " + std::to_string(this->enemiesKillCount));
        this->meteorsKilledText.setString("METEORS KILLED: " + std::to_string(this->meteorKillCount));
        this->asteroidsKilledText.setString("ASTEROIDS KILLED: " + std::to_string(this->asteroidKillCount));

        //EXP UPDATE
        this->currExpBar.setScale(static_cast<float>(this->player->getExp())/this->player->getNextExp(), 1.f);

        //SPLASH SCREEN NOTIFY
        //this->splashScreenText.setString("(PRESS ENTER TO GO TO THE SPLASH SCREEN)");

        //UPDATE THE TEXTS FOR THE STATS
        for(int i = 0; i < this->stats.size(); i++)
        {
            this->stats[i].Update(this->dt);

            if(this->stats[i].getTimer() <= 0.f)
            {
                this->stats.erase(this->stats.begin() + i);
                break;
            }
        }
    }

    void SpaceGame::getScore()
    {
        ////////HIGHEST SCORE////////
        //READ FROM FILE
        std::ifstream inFile("..\\Space_Fighters/highScoreTracker.txt");
        this->scoreboard.loadFromFile(inFile);
    }

    void SpaceGame::scoreUpdate()
    {
        this->highestPoint = this->scoreboard.getHighestScore();
        std::string highSSPoints;
        highSSPoints = "Highest Score: " + std::to_string(this->highestPoint);
        this->highPointCountText.setString(highSSPoints);

        //POINTS INTERFACE
        std::stringstream ssPoints; //string stream variable to convert int to string for points
        ssPoints << "Points: " << this->currPoint;
        this->pointCountText.setString(ssPoints.str()); //converts points(int) to string

        //WRITE TO FILE
        std::ofstream outFile("..\\Space_Fighters/highScoreTracker.txt", std::ios::app);

        if(!this->player->isAlive())
        {
            if(outFile.is_open())
            {
                if(this->currPoint > this->highestPoint)    //compare current point to highest point
                {
                    this->highestPoint = this->currPoint;   //replaces the current point with the highest point
                    outFile << std::endl << this->highestPoint;     //write the score into the file
                }
                else
                {
                    return;
                }
            }
        }
        outFile.close();
    }

    void SpaceGame::pauseGame()
    {
        this->pauseText.setString("PAUSE/UNPAUSE('ENTER')");
    }

    void SpaceGame::checkBoundaries(const sf::RenderWindow& window)
    {
        if(this->player->getGBounds().left <= 0)    //left
        {
            this->player->setPosition(sf::Vector2f(0.f, this->player->getPlayerPos().y));
        }
        if(this->player->getPlayerPos().x >= window.getSize().x - this->player->getGBounds().width)  //right
        {
            this->player->setPosition(sf::Vector2f(window.getSize().x - this->player->getGBounds().width,
                                                   this->player->getPlayerPos().y));
        }
        if(this->player->getGBounds().top <= 0)  //top
        {
            this->player->setPosition(sf::Vector2f(this->player->getPlayerPos().x, 0.f));
        }
        if(this->player->getPlayerPos().y >= window.getSize().y - this->player->getGBounds().height)   //bottom
        {
            this->player->setPosition(sf::Vector2f(this->player->getPlayerPos().x,
                                                   window.getSize().y - this->player->getGBounds().height));
        }
    }

    //updates the entire game
    void SpaceGame::update(const sf::RenderWindow& window)
    {
        this->player->update(this->dt);
        this->playerInput();
        this->checkBoundaries(window);
        this->ammoUpdate();
        this->enemyUpdate(window);
        this->battleUpdate();
        this->interfaceUpdate();
        this->scoreUpdate();

        if(this->player->getHealth() <= 0)
        {
            this->music[mainMusic]->stopMusic();
            this->soundOver.play();
        }

        std::cout << "LEVEL: " << this->player->getLvl() << std::endl;
        std::cout << "CURRENT XP: " << this->player->getExp() << "/" << this->player->getNextExp() << std::endl;
        std::cout << "CURRENT POINTS: " << this->currPoint << std::endl;
        std::cout << "CURRENT TIME: " << this->gameTime << std::endl;
    }

    //draw out the points and health bar
    void SpaceGame::drawInterface(sf::RenderTarget& window) const
    {
        window.draw(this->pointCountText);
        window.draw(this->highPointCountText);
        window.draw(this->maxHealthBar);
        window.draw(this->currHealthBar);
        window.draw(this->healthText);
        window.draw(this->health);
        window.draw(this->maxExpBar);
        window.draw(this->currExpBar);
        window.draw(this->expText);
        window.draw(this->exp);
        window.draw(this->lvlText);
        window.draw(this->pauseText);
        window.draw(this->enemyHPText);
        window.draw(this->gameTimeText);
        window.draw(this->killCountBackground);
        window.draw(this->enemiesKilledText);
        window.draw(this->meteorsKilledText);
        window.draw(this->asteroidsKilledText);
        window.draw(this->splashScreenText);

        //draw the texts of the stats
        for(int i = 0; i < this->stats.size(); i++)
        {
            this->stats[i].Draw(window);
        }

        if(this->player->getHealth() <= 0)  //game over screen appears when health is diminished
        {
            window.draw(this->GameOverSprite);
        }
    }

    //DRAW
    void SpaceGame::Draw(sf::RenderTarget& window) const
    {
        window.draw(this->spaceSprite);  //draw the space background

        window.draw(this->gameLogoSprite);  //draw the game logo

        this->player->Draw(window);    //draw player

        //draw the ammo
        for(int i = 0; i < bullets.size(); i++)
        {
            this->bullets[i]->Draw(window);
        }

        //draw the enemies
        for(int i = 0; i < enemies.size(); i++)
        {
            this->enemies[i]->Draw(window);
        }

        //draw the asteroids
        for(int i = 0; i < meteors.size(); i++)
        {
            this->meteors[i]->Draw(window);
        }

        //draw the asteroid rocks
        for(int i = 0; i < realAsteroids.size(); i++)
        {
            this->realAsteroids[i]->Draw(window);
        }

        this->drawInterface(window);

    }
}