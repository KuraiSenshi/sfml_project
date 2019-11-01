#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "server_game.h"
#include <vector>
#include <iostream>
#include <string.h>
#include "server.h"

Server::Server()
    : receiveOrderThread(&Server::receiveOrder, this)
{
    if(socket.bind(serverPort) != sf::Socket::Done)
    {
        std::cout << "Błąd bindowania gniazda plik server.cpp" << std::endl;
    }
    //socket.setBlocking(false);

    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    std::cout << "Adres lokalny: " << serverIp << std::endl;

    serverIp = sf::IpAddress::getPublicAddress();
    std::cout << "Adres globalny: " << serverIp << std::endl;

    threadIsActive = false;

    window.setFramerateLimit(60);
    window.create(sf::VideoMode(200, 200), "SERVER works!");

}

Server::~Server()
{

}

void Server::receiveOrder()
{
    threadIsActive = true;
    sf::Packet packet;  // pakiet przyjmowany od klienta
    sf::Packet roomData;    //pakiet wysyłany do klienta
    int order; // 1 = otwórz pokój; 2 = dodaj do istniejącego pokoju; 3 = podaj aktualną listę pokojów;
    unsigned short roomPort;

    if(socket.receive(packet, clientIp, clientPort) != sf::Socket::Done)
    {
        //obsługa błędu
        std::cout << "Problem z odbiorem danych plik server.cpp" << std::endl;
    }
    else
    {
        packet >> order;
        switch (order)
        {
            case 1: // utworzenie nowego pokoju i wysłanie do klienta numeru nowego pokoju
                roomPort = 54000+1+room.size();
                room.push_back(ServerGame(roomPort));
                roomData << roomPort;
                if (socket.send(roomData, clientIp, clientPort) != sf::Socket::Done)
                {
                    //obsługa błędu
                }    
            break;
                
            case 2: // odesłanie do klienta informacji o numerze portu pokoju o który pyta
                packet >> order >> roomNumber;
                roomPort = room[roomNumber].getPort();
                roomData << roomPort;
                if (socket.send(roomData, clientIp, clientPort) != sf::Socket::Done)
                {
                    //obsługa błędu
                }
            break;

            default:
            break;
        } 
    }
    threadIsActive = false;
}

void Server::run()
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
    
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                receiveOrderThread.~Thread();
            }
        }
    
        if(!threadIsActive)
        {
            receiveOrderThread.launch();
        }
        
        window.clear();
        window.draw(shape);
        window.display();
    }
}
