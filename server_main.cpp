#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "server_game.cpp"
#include <vector>
#include <iostream>
#include <string.h>

void networkHandling()
{
    //=============== setup ==============================
    sf::UdpSocket socket;
    sf::IpAddress sender;
    sf::Packet packet;
    unsigned short port = 54000;
    std::vector <serverGame> room;
    int order; // 1 = otwórz pokój;

    if(socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Blad bindowania gniazda plik server_main.cpp" << std::endl;
    }

    while(true)
    {
        //============ odbieranie danych ======================
        if(socket.receive(packet, sender, port) != sf::Socket::Done)
        {
            std::cout << "Problem z odbiorem danych plik server_main.cpp" << std::endl;
        }

        packet >> order;
        switch (order)
        {
        case 1:
            room.push_back(serverGame(54000+1+room.size()));
            order = 0;
            break;
        
        default:
            break;
        }
    }
}

int main()
{
    sf::Thread thread(&networkHandling);
    //=============== okienko ========================
    sf::RenderWindow window(sf::VideoMode(200, 200), "SERVER works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    

    return 0;
}