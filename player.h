#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player : public sf::Drawable, public sf::Transformable
{
    public:
        Player();
        ~Player();
        void setTexture(std::string imgDirectory);
        void moveLeft(float speed);
        void moveUp(float speed);
        void moveRight(float speed);
        void moveDown(float speed);
    private:
        int speed;
        sf::Texture texture;
        sf::Sprite sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};