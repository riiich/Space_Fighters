//
// Created by Rich on 5/29/2020.
//

#ifndef SFML_PROJECTS_CS3A_PLAYER_H
#define SFML_PROJECTS_CS3A_PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

namespace PlayerNamespace
{
    enum WEAPONS{defaultBullet = 0/*green bullet*/, type1Bullet/*blue laser*/, type2Bullet};

    class Player
    {
    public:
        Player(sf::Texture* playerText, sf::Texture* gunTexture, sf::Vector2f scaleSize);
        ~Player();
        sf::FloatRect getGBounds() const;
        void setPosition(const sf::Vector2f pos);
        void initPlayerSprite(sf::Texture* playerText, sf::Vector2f scaleSize);
        void initAllVar(sf::Texture* gunTexture);
        void movePlayer(float x, float y);
        void allMove(const float& dt);
        void moveGun();
        sf::Sprite getPlayerSprite() const;
        const sf::Vector2f& getPlayerPos() const;
        const int& getHealth() const;
        const int& getHealthMax() const;
        bool updateLvl();
        const int& getLvl() const;
        const int& getExp() const;
        const int& getNextExp() const;
        bool gainExp(int exp);
        int getDmg() const;
        int getMaxDmg() const;
        void setHealth(int health);
        void loseHealth(int health);
        bool isAlive() const;

        //UPGRADING WEAPONS
        void updateWeapons();   //player's weapon gets upgraded when it hits a certain level
        int getCurrWeapon() const;
        void setCurrWeapon(int setWeapon);
        int getPrimaryWeaponLvl() const;
        bool getUpgradedBullet1() const;
        bool getUpgradedBullet2() const;
        void setPrimaryWeaponLvl(int mainGun);
        void setUpgradedBullet1(bool upgrade);
        void setUpgradedBullet2(bool upgrade);

        void cdAtkUpdate();  //initialize the cooldown for the player's attacks
        const bool playerAtk();
        sf::Vector2f getPlayerCenter() const;
        void updateGun(const float& dt);
        void update(const float& dt);
        void Draw(sf::RenderTarget& target) const;


    private:
        sf::Sprite playerSprite;
        sf::Texture* gunText;
        sf::Sprite gunSprite;

        int health;
        int healthMax;
        int dmg;
        int maxDmg;
        int level;
        int exp;
        int nextExp;
        float damageTime;
        float maxDamageTimer;
        float playerSpeed;    //will control how fast it moves
        float cooldown;
        float maxCooldown;
        sf::Vector2f centerPlayer;  //center of the player
        sf::Vector2f currVelocity;
        float maxVelocity;
        float acceleration;
        sf::Vector2f direction;
        float stabilize;    //drag force

        float dtMultiplier;

        int currentWeaponType;

        //upgrades
        int primaryWeaponLvl;
        bool upgradedBullet1;   //2 bullets
        bool upgradedBullet2;

        int skillPoint;

    };
}

#endif //SFML_PROJECTS_CS3A_PLAYER_H