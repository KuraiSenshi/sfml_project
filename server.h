#ifndef server_h
#define server_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "server_game.h"
#include <memory>
#include <vector>

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
        sf::SocketSelector selector;
        sf::IpAddress clientIp;
        unsigned short serverPort = 54000;
        unsigned short clientPort = 55000;
        std::vector <std::unique_ptr<ServerGame>> room;
        int roomNumber;

        sf::RenderWindow window;

        std::vector<int> freeRoom;
};

#endif