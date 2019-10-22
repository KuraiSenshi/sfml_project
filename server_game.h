#pragma once
#include "SFML/Network.hpp"

class serverGame
{
    public:
        serverGame(unsigned short port);
        ~serverGame();
    private:
        sf::UdpSocket socket;

};