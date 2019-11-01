#ifndef server_game_h
#define server_game_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class ServerGame
{
    public:
        ServerGame(unsigned short port1);
        ~ServerGame();
        unsigned short getPort();

    private:
        //sf::UdpSocket socket;
        unsigned short port;
        //sf::Thread roomThread;
        void game();

};

#endif