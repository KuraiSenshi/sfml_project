#ifndef server_game_h
#define server_game_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "laser.h"
#include "meteor.h"

class ServerGame
{
    public:
        ServerGame(unsigned short port1);
        ~ServerGame();
        unsigned short getPort();

        int getPlayersNumber();
        void gameUpdate();
        std::string getName();
    private:
        sf::UdpSocket socket;
        sf::SocketSelector selector;
        unsigned short port;
        sf::Thread gameThread;  // wątek obsługujący grę 
        bool gameThreadActive = false;
        sf::Thread communicationThread;  // wątek obsługujący komunikację z klientami
        void game();
        void communication();

        enum gameState {WAIT, PLAY, SCORES};

        int playersNumber;

        sf::Packet data;
        sf::IpAddress playerAddress;
        sf::IpAddress player1Address;
        sf::IpAddress player2Address;
        unsigned short playerPort;
        unsigned short player1Port;
        unsigned short player2Port;

        sf::Vector2f player1Pos;
        sf::Vector2f player2Pos;

        std::vector <Laser> bullets;
        bool player1Shooted = false;
        bool player2Shooted = false;

        std::string firstPlayerName = "Brak";

        std::vector <Meteor> meteors;
        sf::Clock clock;
        sf::Clock meteorSpawnClock;
        int meteorsQuantity = 1;
};

#endif