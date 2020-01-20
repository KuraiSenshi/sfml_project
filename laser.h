#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>

class Laser : public sf::Drawable, public sf::Transformable
{
    public:
        Laser(sf::Vector2f pos, int angle);
        Laser(sf::Vector2f pos, int angle, sf::Texture &tex);
        ~Laser();
        void setTexture(sf::Texture &tex);
        bool update();
        void destroy();
        bool isDestroyed();
    private:
        float speed = 20;
        float speed_x;
        float speed_y;
        float texScale = 1.f;
        sf::Sprite sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool destruction = false;
};