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
        void setTexture(std::string imgDirectoryPlayer, std::string imgDirectoryJet);
        void moveLeft(float speed);
        void moveUp(float speed);
        void moveRight(float speed);
        void moveDown(float speed);
        int getShootDelay();
        void setShootDelay(int delay);
        sf::Vector2u getSize();
    private:
        int speed;
        sf::Texture texture;
        sf::Texture jetTexture;
        sf::Sprite sprite;
        sf::Sprite jetSprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int shootDelay = 100; //Millisecounds
};