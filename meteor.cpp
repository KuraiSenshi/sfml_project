#include "meteor.h"

Meteor::Meteor(sf::Vector2f pos, sf::Texture &tex)
{
    speed = 0;
    speed_x = 0;
    speed_y = 0;
    angle = 0;

    sprite.setTexture(tex);

    sprite.setTextureRect(sf::IntRect(0, 0, 101, 84));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    //sprite.setRotation();

    this->setPosition(pos);

    collisionCircle.setRadius(30);
    collisionCircle.setFillColor(sf::Color(255,255,255,0));
    collisionCircle.setOutlineColor(sf::Color::Red);
    collisionCircle.setOutlineThickness(2);
    collisionCircle.setOrigin(collisionCircle.getLocalBounds().width/2, collisionCircle.getLocalBounds().height/2);
}

Meteor::Meteor(sf::Vector2f pos, int ang, float spd)
{
    speed_x = spd * cos(angle*M_PI/180);
    speed_y = spd * sin(angle*M_PI/180);

    //sprite.setRotation(ang);

    sprite.setTextureRect(sf::IntRect(0, 0, 101, 84));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    this->setPosition(pos);
    speed = spd;
    angle = ang;
}

Meteor::Meteor(sf::Vector2f pos, int ang, sf::Texture &tex, float spd)
{
    speed_x = spd * cos(ang*M_PI/180);
    speed_y = spd * sin(ang*M_PI/180);

    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(0, 0, 101, 84));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

    sprite.setRotation(ang+90);

    this->setPosition(pos);
    speed = spd;
    angle = ang;

    collisionCircle.setRadius(30);
    collisionCircle.setFillColor(sf::Color(255,255,255,0));
    collisionCircle.setOutlineColor(sf::Color::Red);
    collisionCircle.setOutlineThickness(5);
    collisionCircle.setOrigin(collisionCircle.getLocalBounds().width/2, collisionCircle.getLocalBounds().height/2);
}

Meteor::~Meteor()
{

}

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(collisionCircle, states);
}

void Meteor::setTexture(sf::Texture &tex)
{
    sprite.setTexture(tex);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

bool Meteor::update()
{
    if (!destruction)
    {
        sf::Vector2f pos = this->getPosition();
        if (pos.x > 2070 || pos.x < 150 || pos.y > 1230 || pos.y < -150)
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
        if (texAlpha > 0)
        {
            texAlpha -= 3;
            sprite.setColor(sf::Color(255,255,255,texAlpha));
            return true;
        }
        else
        {
            return false;
        }
    }
    
}

void Meteor::destroy()
{
    sprite.setTextureRect(sf::IntRect(101, 0, 101, 84));
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    destruction = true;
}

float Meteor::getSpeed()
{
    return speed;
}

int Meteor::getAngle()
{
    return angle;
}

bool Meteor::isDestroyed()
{
    return destruction;
}