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

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}


void Player::moveLeft(float speed)
{
    this->move(-speed, 0);
    sprite.move(-speed, 0);
}

void Player::moveUp(float speed)
{
    this->move(0, -speed);
    sprite.move(0, -speed);
}

void Player::moveRight(float speed)
{
    this->move(speed, 0);
    sprite.move(speed, 0);
}

void Player::moveDown(float speed)
{
    this->move(0, speed);
    sprite.move(0, speed);
}
