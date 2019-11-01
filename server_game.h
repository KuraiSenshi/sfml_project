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

        int getPlayerNumber();

    private:
        sf::UdpSocket socket;
        unsigned short port;
        sf::Thread gameThread;  // wątek obsługujący grę 
        sf::Thread communicationThread;  // wątek obsługujący komunikację z klientami
        void game();
        void communication();

        enum gameState {WAIT, PLAY, SCORES};

        int playerNumber;

};

#endif