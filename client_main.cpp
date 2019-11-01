#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>

int main()
{
    sf::UdpSocket socket;
    unsigned short clientPort = 55000;
    unsigned short server_port = 54000;
    if(socket.bind(clientPort) != sf::Socket::Done)
    {
        // Obsługa błędu
    }

    std::cout << "Podaj adres serwera" << std::endl;
    std::string adress;
    std::cin >> adress;
    //TODO: sprawdzenie poprawności podanych danych
    sf::IpAddress server_adress = adress;
    int order = 1;
    sf::Packet packet;
    packet << order;

    //wysłanie prośby o nowy pokój gry
    if(socket.send(packet, server_adress, server_port) != sf::Socket::Done)
    {
        std::cout << "błąd wysłania zapytania" << std::endl;
    }

    //oczekiwanie na odesłanie przez serwer numeru portu nowego pokoju
    if(socket.receive(packet, server_adress, server_port))
    {
        std::cout << "błąd odbioru danych" << std::endl;
    }
    else
    {
        std::cout << "dostałem odpowiedź" << std::endl;
        unsigned short odpowiedz;
        packet >> odpowiedz;
        std::cout << odpowiedz << std::endl;   
    }

    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
    */

    return 0;
}

