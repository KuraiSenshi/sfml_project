#include "server_game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

ServerGame::ServerGame(unsigned short port1)
    : gameThread(&ServerGame::game, this), communicationThread(&ServerGame::communication, this)
{
    srand(time(NULL));
    std::cout << "konstruktor nowego pokoju" << std::endl;
    port = port1;
    if(socket.bind(port) != sf::Socket::Done)
    {
         // obsługa błędu połączenia
    }
    selector.add(socket);

    communicationThread.launch();

}

ServerGame::~ServerGame()
{

}

unsigned short ServerGame::getPort()
{
    return port;
}

void ServerGame::game()
{
    // aktualizacja obiektów
    // kolizje obiektów
    if (clock.getElapsedTime().asSeconds() > 30)
    {
        meteorsQuantity += 1;
        clock.restart();
    }
    

    if (!bullets.empty())
    {
        for (size_t i = 0; i < bullets.size(); i++) // updatowanie laserow i usuwanie gdy poza ekranem
        {
            if(!bullets[i].update())    // jeżeli pocisk jest poza ekranem updete zwraca false
            {
                bullets.erase(bullets.begin()+i);
            }
        }
    }
    
    if (!meteors.empty()) // updatowanie meteorow i usuwanie gdy poza ekranem
    {
        for (size_t i = 0; i < meteors.size(); i++)
        {
            if (!meteors[i].update()) // jeżeli meteor jest daleko poza ekranem update zwraca false
            {
                meteors.erase(meteors.begin()+i);
            }
        }
    }

    //spawnowanie meteorow
    if (meteors.size() < meteorsQuantity && playersNumber == 2 && meteorSpawnClock.getElapsedTime().asSeconds() > 1)
    {
        meteors.push_back(Meteor(sf::Vector2f(2020, rand() % 1081), rand() % 20 + 170, rand() % 5 + 5));
        //meteors.push_back(Meteor(sf::Vector2f(1000, 500), 0, 0));
        meteorSpawnClock.restart();
        std::cout << "Meteor spawn" << std::endl;
    }
    
    //std::cout << "Meteors: " << meteors.size() << "\tBullets: " << bullets.size() << std::endl;

    // kolizje ===========================================================
    // TODO: kolizja z graczami
    for (size_t i = 0; i < meteors.size(); i++)
    {
        sf::Vector2f meteorPos = meteors[i].getPosition();
        for (size_t j = 0; j < bullets.size(); j++)
        {
            sf::Vector2f bulletPos = bullets[j].getPosition();
            if (pow(bulletPos.x - meteorPos.x, 2) + pow(bulletPos.y - meteorPos.y, 2) <= 1600)
            {
                // TODO: hp meteorytów
                meteors[i].destroy();
                bullets[j].destroy();
                std::cout << "Kolizja" << std::endl;
            }
        }
    }    
}

void ServerGame::gameUpdate()
{
    gameThread.launch();
}

void ServerGame::communication()
{   
    sf::Packet packet;
    //potwierdzenie komunikacji z pierwszym graczem
    socket.receive(packet, player1Address, player1Port);
    std::string wiadomosc1;
    packet >> wiadomosc1;
    std::cout << "odebrano: " << wiadomosc1 << " od " << player1Port << " " << player1Address << std::endl;
    playersNumber = 1;
    firstPlayerName = wiadomosc1;

    //potwierdzenie komunikacji z drugim graczem
    int wiadomosc; 
    socket.receive(packet, player2Address, player2Port);
    packet >> wiadomosc;
    std::cout << "odebrano: " << wiadomosc << " od " << player2Port << " " << player2Address << std::endl;
    playersNumber = 2;

    //odesłanie info do do pierwszeo gracza że można zacząć  
    wiadomosc = 321;
    packet.clear();
    packet << wiadomosc;
    socket.send(packet, player1Address, player1Port);
    //socket.send(packet, player2Address, player2Port);
    
    clock.restart();

    while (true)
    {
        if (selector.wait(sf::seconds(5.f)))
        {
            // po otrzymaniu danych od clienta odsyła zestaw aktualnych danych z serwera
            if ( socket.receive(packet, playerAddress, playerPort) == sf::Socket::Done)
            {
                if (playerAddress == player1Address && playerPort == player1Port)
                {   // otrzymano dane od gracza nr1 
                    float p1x;
                    float p1y;
                    bool shooted;
                    packet >> p1x >> p1y >> shooted;
                    if (!player1Shooted)
                    {
                        player1Shooted = shooted;
                    }
                    
                    player1Pos.x = p1x;
                    player1Pos.y = p1y;
                    if (player1Shooted)
                    {
                        bullets.push_back(Laser(sf::Vector2f(p1x, p1y), 0));
                    }
                    

                    //odesłanie do klienta danych 
                    packet.clear();
                    packet << player2Pos.x << player2Pos.y << player2Shooted;
                    if (meteors.size() > 0)
                    {
                        packet << static_cast<int>(meteors.size());
                        for (size_t i = 0; i < meteors.size(); i++)
                        {
                            packet << meteors[i].getPosition().x << meteors[i].getPosition().y << meteors[i].isDestroyed();
                        }
                        
                    }
                    player2Shooted = false;
                    socket.send(packet, playerAddress, playerPort);
                }
                else if (playerAddress == player2Address && playerPort == player2Port)
                {   // otrzymano dane od gracza nr2
                    float p2x;
                    float p2y;
                    bool shooted;
                    packet >> p2x >> p2y >> shooted;
                    if (!player2Shooted)
                    {
                        player2Shooted = shooted;
                    }

                    player2Pos.x = p2x;
                    player2Pos.y = p2y;
                    if (player2Shooted)
                    {
                        bullets.push_back(Laser(sf::Vector2f(p2x, p2y), 0));
                    }

                    //odesłanie do klienta danych
                    packet.clear();
                    packet << player1Pos.x << player1Pos.y << player1Shooted;
                    if (meteors.size() > 0)
                    {
                        packet << static_cast<int>(meteors.size());
                        for (size_t i = 0; i < meteors.size(); i++)
                        {
                            packet << meteors[i].getPosition().x << meteors[i].getPosition().y << meteors[i].isDestroyed();
                        }
                        
                    }
                    player1Shooted = false;
                    socket.send(packet, playerAddress, playerPort);
                }
            }
        }
        else
        {
            break;
        }
        
    }
}

int ServerGame::getPlayersNumber()
{
    return playersNumber;
}

std::string ServerGame::getName()
{
    return firstPlayerName;
}