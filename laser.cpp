#include "laser.h"

Laser::Laser(sf::Vector2f pos, int angle)
{
    speed_x = speed * cos(angle*M_PI/180);
    speed_y = speed * sin(angle*M_PI/180);

    sprite.setTextureRect(sf::IntRect(0, 0, 9, 37));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height);

    sprite.setRotation(angle+90);

    this->setPosition(pos);
}

Laser::Laser(sf::Vector2f pos, int angle, sf::Texture &tex)
{
    speed_x = speed * cos(angle*M_PI/180);
    speed_y = speed * sin(angle*M_PI/180);

    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(0, 0, 9, 37));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height);

    sprite.setRotation(angle+90);

    this->setPosition(pos);
}

Laser::~Laser()
{

}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Laser::setTexture(sf::Texture &tex)
{
    sprite.setTexture(tex);
    sprite.setOrigin(sprite.getLocalBounds().width, sprite.getLocalBounds().height/2);
}

bool Laser::update()
{
    if (!destruction)
    {
        sf::Vector2f pos = this->getPosition();
        if (pos.x > 1800 || pos.x < 0 || pos.y > 1080 || pos.y < 0)
        {
            this->destroy();
        }
        else
        {
            this->move(sf::Vector2f(speed_x, speed_y));
        }
        return true;
    }
    else
    {
        if (texScale >= 0.1)
        {
            texScale -= 0.05;
            sprite.setScale(texScale, texScale);
            sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
            return true;
        }
        else
        {
            return false;
        }
    }
    
}

void Laser::destroy()
{
    sprite.setTextureRect(sf::IntRect(10, 0, 48, 46));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    destruction = true;
}

bool Laser::isDestroyed()
{
    return destruction;
}