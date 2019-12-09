#include "server_game.h"
#include <iostream>

ServerGame::ServerGame(unsigned short port1)
    : gameThread(&ServerGame::game, this), communicationThread(&ServerGame::communication, this)
{
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
    //TODO: aktualizacja obiektów
    //TODO: kolizje obiektów
    if (!gameThreadActive)
    {
        std::cout << "x:" << player1Pos.x << " y:" << player1Pos.y << std::endl;
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
    int wiadomosc;
    packet >> wiadomosc;
    std::cout << "odebrano: " << wiadomosc << std::endl;
    wiadomosc = 321;
    packet.clear();
    packet << wiadomosc;
    socket.send(packet, player1Address, player1Port);
    playersNumber = 1;
    //TODO: potwierdzenie komunikacji z drugim graczem 

    while (true)
    {
        if (selector.wait(sf::seconds(20.f)))
        {
            //TODO: po otrzymaniu danych od clienta odsyła zestaw aktualnych danych z serwera
            if ( socket.receive(packet, playerAddress, playerPort) == sf::Socket::Done)
            {
                if (playerAddress == player1Address && playerPort == player1Port)
                {   // otrzymano dane od gracza nr1 
                    float p1x;
                    float p1y;
                    packet >> p1x >> p1y;
                    player1Pos.x = p1x;
                    player1Pos.y = p1y;
                }
                else if (playerAddress == player2Address && playerPort == player2Port)
                {   // otrzymano dane od gracza nr2
                    
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