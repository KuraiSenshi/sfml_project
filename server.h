#ifndef server_h
#define server_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "server_game.h"

class Server
{
    public:
        Server();
        ~Server();
        void run();
    private:
        void receiveOrder();
        sf::Thread receiveOrderThread;
        bool threadIsActive;


        sf::UdpSocket socket;
        sf::IpAddress clientIp;
        unsigned short serverPort = 54000;
        unsigned short clientPort = 55000;
        std::vector <ServerGame> room;
        int roomNumber;

        sf::RenderWindow window;
};

#endif