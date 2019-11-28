#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "server_game.h"
#include <vector>
#include <iostream>
#include <string.h>
#include "server.h"
#include <memory>

Server::Server()
    : receiveOrderThread(&Server::receiveOrder, this)
{
    if(socket.bind(serverPort) != sf::Socket::Done)
    {
        std::cout << "Błąd bindowania gniazda plik server.cpp" << std::endl;
    }
    //socket.setBlocking(false);
    selector.add(socket);

    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    std::cout << "Adres lokalny: " << serverIp << std::endl;

    serverIp = sf::IpAddress::getPublicAddress();
    std::cout << "Adres globalny: " << serverIp << std::endl;

    threadIsActive = false;

    window.setFramerateLimit(60);
    window.create(sf::VideoMode(200, 200), "FarSpace server");

    ServerGame test(1234);
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

    if (selector.wait(sf::seconds(1.f)))
        if(socket.receive(packet, clientIp, clientPort) != sf::Socket::Done)
        {
            //obsługa błędu
            //std::cout << "Problem z odbiorem danych plik server.cpp" << std::endl;
        }
        else
        {
            packet >> order;
            if (order == 1)
            {   // utworzenie nowego pokoju i wysłanie do klienta numeru nowego pokoju
                    roomPort = 54000+1+room.size();
                    
                    std::unique_ptr<ServerGame> room_ptr(new ServerGame(roomPort));
                    room.push_back(std::move(room_ptr));

                    roomData << roomPort;
                    if (socket.send(roomData, clientIp, clientPort) != sf::Socket::Done)
                    {
                        //obsługa błędu
                    }    
            }    
            else if (order == 2)
            {   // odesłanie do klienta informacji o numerze portu pokoju o który pyta
                    packet >> order >> roomNumber;
                    roomPort = room[roomNumber]->getPort();
                    roomData << roomPort;
                    if (socket.send(roomData, clientIp, clientPort) != sf::Socket::Done)
                    {
                        //obsługa błędu
                    }
            }
            else if (order == 3)
            {   // odpowiedź na łączenie z serwerem
                /*sf::Packet packet;
                std::string text = "xd";
                packet << text;
                if (socket.send(packet, clientIp, clientPort) != sf::Socket::Done)
                {
                    //obsługa błędu
                }*/
            }
              
                //case 3: // odesłanei do klienta informacji o aktualnie wolnych pokojach 

                //break;

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
