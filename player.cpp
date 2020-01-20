#include "player.h"

Player::Player()
{
    sprite.setRotation(90);
}

Player::~Player()
{
}

void Player::setTexture(std::string imgDirectory)
{
    if (!texture.loadFromFile(imgDirectory))
    {
        std::cout << "Error - wczytanie grafiki gracza nie powiodlo sie" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

void Player::setTexture(std::string imgDirectoryPlayer, std::string imgDirectoryJet)
{
    if (!texture.loadFromFile(imgDirectoryPlayer))
    {
        std::cout << "Error - wczytanie grafiki gracza nie powiodlo sie" << std::endl;
    }
    if (!jetTexture.loadFromFile(imgDirectoryJet))
    {
        std::cout << "Error - wczytanie grafiki gracza nie powiodlo sie" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    jetSprite.setTexture(jetTexture);
    jetSprite.setOrigin(jetSprite.getLocalBounds().width/2, 0);
    jetSprite.setRotation(90);
    jetSprite.move(-sprite.getLocalBounds().height/2, 0);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(jetSprite, states);
}

void Player::moveLeft(float speed)
{
    this->move(-speed, 0);
}

void Player::moveUp(float speed)
{
    this->move(0, -speed);
}

void Player::moveRight(float speed)
{
    this->move(speed, 0);
}

void Player::moveDown(float speed)
{
    this->move(0, speed);
}

int Player::getShootDelay()
{
    return this->shootDelay;
}

void Player::setShootDelay(int delay)
{
    this->shootDelay = delay;
}

sf::Vector2u Player::getSize()
{
    return texture.getSize();
}