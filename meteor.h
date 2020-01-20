#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>

class Meteor : public sf::Drawable, public sf::Transformable
{
    public:
        Meteor(sf::Vector2f pos, sf::Texture &tex);
        Meteor(sf::Vector2f pos, int angle, float speed);
        Meteor(sf::Vector2f pos, int angle, sf::Texture &tex, float speed);
        ~Meteor();
        void setTexture(sf::Texture &tex);
        bool update();
        void destroy();
        float getSpeed();
        int getAngle();
        bool isDestroyed();
    private:
        float speed_x;
        float speed_y;
        float speed;
        int angle;
        int texAlpha = 255;
        sf::Sprite sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool destruction = false;

        sf::CircleShape collisionCircle;
};