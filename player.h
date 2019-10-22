#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
    public:
        Player();
        ~Player();
        void loadTexture();
    private:
        int speed;
        sf::Texture texture;
        //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};