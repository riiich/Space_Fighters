//
// Created by Rich on 5/29/2020.
//

#include "Player.h"

namespace PlayerNamespace
{
    Player::Player(sf::Texture* playerText, sf::Texture* gunTexture, sf::Vector2f scaleSize)
    {
        initPlayerSprite(playerText, scaleSize);
        initAllVar(gunTexture);
    }

    Player::~Player()
    {}

    sf::FloatRect Player::getGBounds() const
    {
        return this->playerSprite.getGlobalBounds();
    }

    void Player::setPosition(const sf::Vector2f pos)
    {
        this->playerSprite.setPosition(pos);
    }

    void Player::initPlayerSprite(sf::Texture* playerText, sf::Vector2f scaleSize)
    {
        //setting the texture into a sprite
        this->playerSprite.setTexture(*playerText);
        this->playerSprite.setScale(scaleSize);//.35f, .35f
    }

    void Player::initAllVar(sf::Texture* gunTexture)
    {
        this->healthMax = 50;
        this->health = this->healthMax;
        this->playerSpeed = 10.f;   //player's initial speed
        this->maxCooldown = 10.f;    //max cooldown for the player's attacks(controls spraying)
        this->cooldown = this->maxCooldown;
        this->maxVelocity = 20.f;
        this->acceleration = 1.f;
        this->stabilize = 0.4f;
        this->level = 1;
        this->exp = 0;
        this->nextExp = 25 + static_cast<int>((50/3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12)); //leveling formula taken from a game(tibia)
        this->skillPoint = 0;
        this->dmg = 3;
        this->maxDmg = 5;
        this->maxDamageTimer = 5.f;
        this->damageTime = this->maxDamageTimer;
        this->gunText = gunTexture;
        this->gunSprite.setTexture(*this->gunText);
        this->gunSprite.setOrigin(this->gunSprite.getGlobalBounds().width/2,
                                    this->gunSprite.getGlobalBounds().height/2);

        this->currentWeaponType = defaultBullet;

        this->primaryWeaponLvl = 0;
        this->upgradedBullet1 = false;
        this->upgradedBullet2 = false;

        this->dtMultiplier = 62.5f;
    }

    void Player::movePlayer(float x, float y)
    {
        //the player is able to move according to x and y
        playerSprite.move(playerSpeed*x, playerSpeed*y);
    }

    void Player::allMove(const float& dt)
    {
        //move the player around
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            this->direction.x = -1.f;
            this->direction.y = 0.f;

            if(this->currVelocity.x > -this->maxVelocity && this->direction.x < 0)
            {
                this->currVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
            }

            //speed up the player when shift is pressed
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
               && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                this->movePlayer(-1.4f * dt * this->dtMultiplier, 0.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            this->direction.x = 1.f;
            this->direction.y = 0.f;

            if(this->currVelocity.x < this->maxVelocity && this->direction.x > 0)
            {
                this->currVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
               && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                this->movePlayer(1.4f * dt * this->dtMultiplier, 0.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            this->direction.x = 0.f;
            this->direction.y = -1.f;

            if(this->currVelocity.y > -this->maxVelocity && this->direction.y < 0)
            {
                this->currVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
               && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                this->movePlayer(0.f, -1.4f * dt * this->dtMultiplier);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            this->direction.x = 0.f;
            this->direction.y = 1.f;

            if(this->currVelocity.y < this->maxVelocity && this->direction.y > 0)
            {
                this->currVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
               && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                this->movePlayer(0.f, 1.4f * dt * this->dtMultiplier);
            }
        }

        if(this->currVelocity.x > 0)
        {
            this->currVelocity.x -= this->stabilize * dt * this->dtMultiplier;

            if(this->currVelocity.x < 0)
            {
                this->currVelocity.x = 0;
            }
        }
        else if(this->currVelocity.x < 0)
        {
            this->currVelocity.x += this->stabilize * dt * this->dtMultiplier;

            if(this->currVelocity.x > 0)
            {
                this->currVelocity.x = 0;
            }
        }

        if(this->currVelocity.y > 0)
        {
            this->currVelocity.y -= this->stabilize * dt * this->dtMultiplier;

            if(this->currVelocity.y < 0)
            {
                this->currVelocity.y = 0;
            }
        }
        else if(this->currVelocity.y < 0)
        {
            this->currVelocity.y += this->stabilize * dt * this->dtMultiplier;

            if(this->currVelocity.y > 0)
            {
                this->currVelocity.y = 0;
            }
        }

        //This controls the moving after all the calculations are done above
        this->playerSprite.move(this->currVelocity.x * dt * this->dtMultiplier, this->currVelocity.y * dt * this->dtMultiplier);

        //USE THIS AS A REFERENCE TO MAKE A POTION FOR HEALTH OR SOMETHING
        //MAYBE USE AS REWARD FOR A QUEST TO GET A POTION OR MORE HEALTH
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            this->health += 1;
            if(this->health < 0)
            {
                this->health = 0;
            }
            else if(this->health > this->healthMax)
            {
                this->health = this->healthMax;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            this->moveGun();
    }

    void Player::moveGun()
    {
        this->gunSprite.move(0.f, 30.f);
    }

    sf::Sprite Player::getPlayerSprite() const
    {
        return this->playerSprite;
    }

    const sf::Vector2f& Player::getPlayerPos() const
    {
        return this->playerSprite.getPosition();
    }

    const int& Player::getHealth() const
    {
        return this->health;
    }

    const int& Player::getHealthMax() const
    {
        return this->healthMax;
    }

    const int& Player::getLvl() const
    {
        return this->level;
    }

    bool Player::updateLvl()
    {
        //level the player up if the player gains enough xp
        if(this->exp >= this->nextExp)
        {
            this->level++;  //level up the player
            this->exp -= this->nextExp; //resets the the exp back to 0 once the player reaches the exp cap or the
            this->nextExp = static_cast<int>((50/15) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));
            this->skillPoint++;

            //when player levels up, player gains more max health and current health
            this->health *= 2;
            this->healthMax *= 1.4;
            if(this->health >= this->healthMax)
            {
                this->health = this->healthMax;
            }

            return true;
        }
        else
            return false;
    }

    const int& Player::getExp() const
    {
        return this->exp;
    }

    const int& Player::getNextExp() const
    {
        return this->nextExp;
    }

    bool Player::gainExp(int exp)
    {
        this->exp += exp;

        if(this->updateLvl())
            return true;
        else
            return false;
    }

    int Player::getDmg() const
    {
        int newDamage = this->dmg;

        switch(this->currentWeaponType)
        {
            case defaultBullet:
                newDamage = rand()%this->dmg + this->maxDmg;    //default damage
                break;

            case type1Bullet:
                newDamage = rand()%this->dmg + this->maxDmg;
                newDamage *= 2; //upgraded ammo does double the default damage
                break;

            case type2Bullet:
                newDamage = rand()%this->dmg + this->maxDmg;
                newDamage *= 4; //next upgraded ammo does quadruple the default damage
                break;

            default:
                newDamage = rand()%this->dmg + this->maxDmg;    //default damage
                break;
        }

        return newDamage;
    }

    int Player::getMaxDmg() const
    {
        return this->maxDmg;
    }

    void Player::setHealth(int health)
    {
        this->health = health;
    }

    void Player::loseHealth(int health)
    {
        this->health -= health;    //subtracting the current health from the health lost parameter

        this->damageTime = this->maxDamageTimer;

        if(this->health <= 0)
        {
            this->health = 0;
        }
    }

    bool Player::isAlive() const
    {
        if(this->health > 0)
            return true;
        else
            return false;
    }

    int Player::getCurrWeapon() const
    {
        return this->currentWeaponType;
    }

    void Player::setCurrWeapon(int setWeapon)
    {
        this->currentWeaponType = setWeapon;
    }

    int Player::getPrimaryWeaponLvl() const
    {
        return this->primaryWeaponLvl;
    }

    bool Player::getUpgradedBullet1() const
    {
        return this->upgradedBullet1;
    }

    bool Player::getUpgradedBullet2() const
    {
        return this->upgradedBullet2;
    }

    void Player::setPrimaryWeaponLvl(int mainGun)
    {
        this->primaryWeaponLvl = mainGun;
    }

    void Player::setUpgradedBullet1(bool upgrade)
    {
        this->upgradedBullet1 = upgrade;
    }

    void Player::setUpgradedBullet2(bool upgrade)
    {
        this->upgradedBullet2 = upgrade;
    }

    void Player::cdAtkUpdate()
    {
        if(this->cooldown <= this->maxCooldown)
        {
            this->cooldown += 0.7f;
        }
    }

    const bool Player::playerAtk()
    {
        //checks if the cooldown on the shooting is lower than the max
        if(this->cooldown >= this->maxCooldown)
        {
            this->cooldown = 0.f;   //reset the cooldown timer
            return true;
        }

            return false;
    }

    sf::Vector2f Player::getPlayerCenter() const
    {
        return this->centerPlayer;
    }

    void Player::updateGun(const float& dt)
    {
        this->gunSprite.setPosition(this->centerPlayer.x, this->gunSprite.getPosition().y + this->centerPlayer.y);

        if(this->gunSprite.getPosition().y < this->centerPlayer.y)
        {
            this->gunSprite.move(0.f, 1.f + this->currVelocity.y);
        }
        else if(this->gunSprite.getPosition().y > this->centerPlayer.y)
        {
            this->gunSprite.setPosition(this->centerPlayer.x, this->centerPlayer.y);
        }
    }

    void Player::update(const float& dt)
    {
        //the center of the player
        this->centerPlayer.x = this->playerSprite.getPosition().x + this->playerSprite.getGlobalBounds().width/2;
        this->centerPlayer.y = this->playerSprite.getPosition().y + this->playerSprite.getGlobalBounds().height/2;

        this->cdAtkUpdate();
        this->updateGun(dt);
        this->allMove(dt);

        if(this->damageTime > 0.f)
        {
            this->damageTime -= 1.f * dt * this->dtMultiplier;
            this->playerSprite.setColor(sf::Color::Red);
            this->playerSprite.move(0.f, 2.f);
        }
        else
            this->playerSprite.setColor(sf::Color::White);
     }

    void Player::Draw(sf::RenderTarget& target) const
    {
        target.draw(this->gunSprite);

        target.draw(this->playerSprite);
    }
}